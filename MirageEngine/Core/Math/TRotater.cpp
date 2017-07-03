#include "TRotater.h"

TRotater::TRotater()
{
	pitch = 0;
	yaw = 0;
	roll = 0;
}

TRotater::TRotater(float InPitch, float InYaw, float InRoll) 
{
	pitch = InPitch;
	yaw = InYaw;
	roll = InRoll;
}