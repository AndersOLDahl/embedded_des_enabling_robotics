#ifndef ZEDBOARD_H
#define ZEDBOARD_H

// Class Definition
class ZedBoard {
    private:
        char *pBase;	// virtual address where I/O was mapped
        int fd;			// file descriptor for dev memory
    public:
        ZedBoard();		// Default Constructor
        ~ZedBoard();	// Destructor
        void RegisterWrite(int offset, int value);
        int RegisterRead(int offset);
        void Set1Led(int ledNum, int state);
        void SetLedNumber(int value);
};

#endif
