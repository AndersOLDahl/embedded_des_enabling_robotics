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
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * @param pBase		Base address returned by 'mmap'.
 * @parem offset	Offset where device is mapped.
 * @param value		Value to be written.
 */
void RegisterWrite(char *pBase, int offset, int value)
{
	* (int *) (pBase + offset) = value;
}

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param pBase		Base address returned by 'mmap'.
 * @param offset	Offset where device is mapped.
 * @return			Value read.
 */
int RegisterRead(char *pBase, int offset)
{
	return * (int *) (pBase + offset);
}

/**
 * Initialize general-purpose I/O
 *  - Opens access to physical memory /dev/mem
 *  - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param  fd	File descriptor passed by reference, where the result
 *		of function 'open' will be stored.
 * @return	Address to virtual memory which is mapped to physical,
 *          	or MAP_FAILED on error.
 */
char *Initialize(int *fd)
{
	*fd = open( "/dev/mem", O_RDWR);
	return (char *) mmap(
			NULL,
			gpio_size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			*fd,
			gpio_address);
}

/**
 * Close general-purpose I/O.
 *
 * @param pBase	Virtual address where I/O was mapped.
 * @param fd	File descriptor previously returned by 'open'.
 */
void Finalize(char *pBase, int fd)
{
	munmap(pBase, gpio_size);
	close(fd);
}

/**
 * Show lower 8 bits of integer value on LEDs
 *
 * @param pBase	Base address of I/O
 * @param value	Value to show on LEDs
 */
void SetLedNumber(char *pBase, int value)
{
	RegisterWrite(pBase, gpio_led1_offset, value % 2);
	RegisterWrite(pBase, gpio_led2_offset, (value / 2) % 2);
	RegisterWrite(pBase, gpio_led3_offset, (value / 4) % 2);
	RegisterWrite(pBase, gpio_led4_offset, (value / 8) % 2);
	RegisterWrite(pBase, gpio_led5_offset, (value / 16) % 2);
	RegisterWrite(pBase, gpio_led6_offset, (value / 32) % 2);
	RegisterWrite(pBase, gpio_led7_offset, (value / 64) % 2);
	RegisterWrite(pBase, gpio_led8_offset, (value / 128) % 2);
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
 * @param pBase	Base address of I/O
 * @param value	Value representing the switches
 */
void SwitchStateInitialRead(char *pBase, int * value) {

	*value = 0;
	*value += 1 * RegisterRead(pBase, gpio_sw1_offset);
	*value += 2 * RegisterRead(pBase, gpio_sw2_offset);
	*value += 4 * RegisterRead(pBase, gpio_sw3_offset);
	*value += 8 * RegisterRead(pBase, gpio_sw4_offset);
	*value += 16 * RegisterRead(pBase, gpio_sw5_offset);
	*value += 32 * RegisterRead(pBase, gpio_sw6_offset);
	*value += 64 * RegisterRead(pBase, gpio_sw7_offset);
	*value += 128 * RegisterRead(pBase, gpio_sw8_offset);

	SetLedNumber(pBase, *value);
}

/**
 * Returns 0 if no push button is pressed, and a value
 * between 1 and 5 if any push button is pressed.
 * Each number identifies a particular push button
 * (1 = center, 2 = left, 3 = right, 4 = up, 5 = down).
 *
 * @param pBase	Base address of I/O
 * @return the button pressed
 */
int PushButtonGet(char *pBase) {
	if(RegisterRead(pBase, gpio_pbtnc_offset) == 1) {
		usleep(500000);
		return 1;
	} else if(RegisterRead(pBase, gpio_pbtnl_offset) == 1) {
		usleep(500000);
		return 2;
	} else if(RegisterRead(pBase, gpio_pbtnr_offset) == 1) {
		usleep(500000);
		return 3;
	} else if(RegisterRead(pBase, gpio_pbtnu_offset) == 1) {
		usleep(500000);
		return 4;
	} else if (RegisterRead(pBase, gpio_pbtnd_offset) == 1) {
		usleep(500000);
		return 5;
	} else {
		return 0;
	}
}

int main()
{
	// Initialize
	int fd;
	char *pBase = Initialize(&fd);

	// Check error
	if (pBase == MAP_FAILED)
	{
		perror("Mapping I/O memory failed - Did you run with 'sudo'?\n");
		return -1;
	}

	int value = 0;

	/** Turn on the LEDs based on the switches. If a
	* switch is on, the LED is on.
	*/
	SwitchStateInitialRead(pBase, &value);

	int sel;
	while(1) {
		sel = PushButtonGet(pBase);
		switch(sel) {
			case 1:
				/** Reset the LEDs to be that of the switches.
				* If a switch is on, the LED is on.
				*/
				SwitchStateInitialRead(pBase, &value);
				break;
			case 2:
				/**
				* Shift the value over by 1 bit to the left
				*/
				value <<= 1;
				SetLedNumber(pBase, value);
				break;
			case 3:
				/**
				* Shift the value over by 1 bit to the right
				*/
				value >>= 1;
				SetLedNumber(pBase, value);
				break;
			case 4:
				value += 1; // Add 1 to the value
				SetLedNumber(pBase, value);
				break;
			case 5:
				value -= 1; // Subtract 1 to the value
				SetLedNumber(pBase, value);
				break;
			default:
				break;
		}
	}

	// Done
	Finalize(pBase, fd);
	return 0;
}
