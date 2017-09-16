#ifndef __COMUNICATIONDEVICE__
#define __COMUNICATIONDEVICE__
#include "InputDevice.h"
#include "OutputDevice.h"
#include "event.h"

class ComunicationDevice : virtual public InputDevice, virtual public OutputDevice
{
};

#endif
