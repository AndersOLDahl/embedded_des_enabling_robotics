#include <stdlib.h>
#include <unistd.h>
#include "WiimoteAccel.h"

int main()
{

	WiimoteAccel wiimoteAccel;
	wiimoteAccel.Listen();

    return 0;
}
