#include <sys/mman.h>
#include <iostream>
#include <fcntl.h>
#include "ZedBoard.h"

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
 * Constructor Initialize general-purpose I/O
 *  - Opens access to physical memory /dev/mem
 *  - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param  None	Default constructor does not need arguments.
 * @return	None Default constructor does not return anything.
 */
ZedBoard::ZedBoard(){
    std::cout << "\nStarting...." << std::endl;
    fd = open( "/dev/mem", O_RDWR);
    pBase = (char *) mmap(NULL,gpio_size,PROT_READ | PROT_WRITE,
            MAP_SHARED,fd,gpio_address);
    /* Check error */
    if (pBase == MAP_FAILED)
    {
        std::cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
        exit(1); // Returns 1 to the operating system;
    }
}

/**
 * Destructor to close general-purpose I/O.
 * - Uses virtual address where I/O was mapped.
 * - Uses file descriptor previously returned by 'open'.
 *
 * @param  None	Destructor does not need arguments.
 * @return	None Destructor does not return anything.
 */
ZedBoard::~ZedBoard(){
    munmap(pBase, gpio_size);
    close(fd);
    std::cout << "\nTerminating...." << std::endl;
}

/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * - Uses base address returned by 'mmap'.
 * @parem offset	Offset where device is mapped.
 * @param value		Value to be written.
 */
void ZedBoard::RegisterWrite(int offset, int value)
{
    * (int *) (pBase + offset) = value;
}

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * - Uses base address returned by 'mmap'.
 * @param offset	Offset where device is mapped.
 * @return		Value read.
 */
int ZedBoard::RegisterRead(int offset)
{
    return * (int *) (pBase + offset);
}

/**
 * Changes the state of an LED (ON or OFF)
 *
 * - Uses base address of I/O
 * @param ledNum	LED number (0 to 7)
 * @param state	State to change to (ON or OFF)
 */
void ZedBoard::Set1Led(int ledNum, int state)
{
    std::cout << "\nWriting to LED " << ledNum << std::endl;
    RegisterWrite(gpio_led1_offset + (ledNum * 4), state);
    std::cout << "LED offset: " << std::hex << gpio_led1_offset+(ledNum*4) << "    ";
    std::cout << "LED state: " << state << std::endl;
}

/**
 * Show lower 8 bits of integer value on LEDs
 *
 * - Calls Set1Led() to set all LEDs
 * @param value	Value to show on LEDs
 */
void ZedBoard::SetLedNumber(int value)
{
    std::cout << "\nWriting to LEDs...." << std::endl;
    for(int i = 0; i < 8; i++) {// write to all LEDs
        Set1Led(i, (value / (1<<i)) % 2);
    }
}
