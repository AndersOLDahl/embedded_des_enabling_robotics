#ifndef ZEDBOARD_H
#define ZEDBOARD_H

// Class Definition
class WiimoteBtns {
    private:
        int fd; // File descriptor
    public:
        WiimoteBtns();  // Default constructor
        ~WiimoteBtns(); // Destructor
        void Listen();
        void ButtonEvent(int code, int value);
};

#endif
