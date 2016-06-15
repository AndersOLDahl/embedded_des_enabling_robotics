#ifndef WIIMOTE_ACCEL_H
#define WIIMOTE_ACCEL_H

// Class Definition
class WiimoteAccel {
	private:
        int fd; // File descriptor
	public:
		WiimoteAccel(); // Default constructor
		~WiimoteAccel(); // Destructor
		void Listen();
		virtual int AccelerationEvent(int code, int acceleration);
};

#endif
