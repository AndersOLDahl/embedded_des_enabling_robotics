#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

const int gpio_led1_offset = 0x12C;  // Offset for LED1
const int gpio_led2_offset = 0x130;  // Offset for LED2
const int gpio_led3_offset = 0x134;  // Offset for LED3
const int gpio_led4_offset = 0x138;  // Offset for LED4
const int gpio_led5_offset = 0x13C;  // Offset for LED5
const int gpio_led6_offset = 0x140;  // Offset for LED6
const int gpio_led7_offset = 0x144;  // Offset for LED7
const int gpio_led8_offset = 0x148;  // Offset for LED8

const int gpio_sw1_offset = 0x14C;  // Offset for Switch 1
const int gpio_sw2_offset = 0x150;  // Offset for Switch 2
const int gpio_sw3_offset = 0x154;  // Offset for Switch 3
const int gpio_sw4_offset = 0x158;  // Offset for Switch 4
const int gpio_sw5_offset = 0x15C;  // Offset for Switch 5
const int gpio_sw6_offset = 0x160;  // Offset for Switch 6
const int gpio_sw7_offset = 0x164;  // Offset for Switch 7
const int gpio_sw8_offset = 0x168;  // Offset for Switch 8

const int gpio_pbtnl_offset = 0x16C;  // Offset for left push button
const int gpio_pbtnr_offset = 0x170;  // Offset for right push button
const int gpio_pbtnu_offset = 0x174;  // Offset for up push button
const int gpio_pbtnd_offset = 0x178;  // Offset for down push button
const int gpio_pbtnc_offset = 0x17C;  // Offset for center push button

/**
* Class to represent the ZedBoard
*/
class ZedBoard
{
	// Member variables of ZedBoard
	char *pBase;
	int fd;

public:
	/**
	* Initialize general-purpose I/O
	*  - Opens access to physical memory /dev/mem
	*  - Maps memory at offset 'gpio_address' into virtual address space
	*/
	ZedBoard()
	{
		fd = open( "/dev/mem", O_RDWR);
		pBase = (char *) mmap(NULL, gpio_size,
				PROT_READ | PROT_WRITE, MAP_SHARED,
				fd, gpio_address);

		// Check error
		if (pBase == MAP_FAILED)
		{
			perror("Mapping I/O memory failed - Did you run with 'sudo'?\n");
			exit(0);
		}
	}

	/**
	* Close general-purpose I/O.
	*/
	~ZedBoard()
	{
		munmap(pBase, gpio_size);
		close(fd);
	}

	/**
	* Write a 4-byte value at the specified general-purpose I/O location.
	*
	* @parem offset		Offset where device is mapped.
	* @param value		Value to be written.
	*/
	void RegisterWrite(int offset, int value)
	{
		* (int *) (pBase + offset) = value;
	}

	/**
	* Read a 4-byte value from the specified general-purpose I/O location.
	*
	* @param offset		Offset where device is mapped.
	* @return			Value read.
	*/
	int RegisterRead(int offset)
	{
		return * (int *) (pBase + offset);
	}

	/**
	* Show lower 8 bits of integer value on LEDs
	*
	* @param value	Value to show on LEDs
	*/
	void SetLedNumber(int value)
	{
		RegisterWrite(gpio_led1_offset, value % 2);
		RegisterWrite(gpio_led2_offset, (value / 2) % 2);
		RegisterWrite(gpio_led3_offset, (value / 4) % 2);
		RegisterWrite(gpio_led4_offset, (value / 8) % 2);
		RegisterWrite(gpio_led5_offset, (value / 16) % 2);
		RegisterWrite(gpio_led6_offset, (value / 32) % 2);
		RegisterWrite(gpio_led7_offset, (value / 64) % 2);
		RegisterWrite(gpio_led8_offset, (value / 128) % 2);
	}

	/**
	* Represent the state of the switches as an
	* integer value. The switches are basically
	* 8 bits that we then turn into an integer.
	* Whatever the value was coming in gets reset
	* to represent the value set by the switches.
	* Next, turn on the LEDs underneath those
	* switches.
	*
	* @param value	Value representing the switches
	*/
	void SwitchStateInitialRead(int * value)
	{
		*value = 0;
		*value += 1 * RegisterRead(gpio_sw1_offset);
		*value += 2 * RegisterRead(gpio_sw2_offset);
		*value += 4 * RegisterRead(gpio_sw3_offset);
		*value += 8 * RegisterRead(gpio_sw4_offset);
		*value += 16 * RegisterRead(gpio_sw5_offset);
		*value += 32 * RegisterRead(gpio_sw6_offset);
		*value += 64 * RegisterRead(gpio_sw7_offset);
		*value += 128 * RegisterRead(gpio_sw8_offset);

		SetLedNumber(*value);
	}

	/**
	* Each number identifies a particular push button
	* pressed and acts accordingly. Up increases the rate
	* by 1 per 1 second tick. Down decreases the rate
	* by 1 per 1 second tick. Center resets the LEDs to be
	* on/off based whether its corresponding switch is on
	* or off. Left and right switches the rate to negative
	* or positive.
	*
	* @param value	Value to show on LEDs
	* @param rate Rate of increase/decrease. For example
	* 8/sec, 4/sec, -1/sec, etc
	*/
	void PushButtonGet(int * value, int * rate) {
		if(RegisterRead(gpio_pbtnc_offset) == 1) {
			SwitchStateInitialRead(value);
			usleep(500000);
		} else if(RegisterRead(gpio_pbtnl_offset) == 1) {
			if(*rate > 0)
				*rate *= -1;
			usleep(500000);
		} else if(RegisterRead(gpio_pbtnr_offset) == 1) {
			if(*rate < 0)
				*rate *= -1;
			usleep(500000);
		} else if(RegisterRead(gpio_pbtnu_offset) == 1) {
			*rate += 1;
			usleep(500000);
		} else if (RegisterRead(gpio_pbtnd_offset) == 1) {
			*rate -= 1;
			usleep(500000);
		}
	}
};

int main()
{
	ZedBoard zed; // Zedboard object

	int value = 0;
	int rate = 0;
	zed.SwitchStateInitialRead(&value); // Set the LEDs according to the switches

	while(1) {
		zed.PushButtonGet(&value, &rate); // Check and act on button presses

		sleep(1);
		value += rate; // Change the value rate/sec
		zed.SetLedNumber(value);
	}

	return 0;
}
