#include <openvr_driver.h>
#include "driver_VirtualCheap.h"
#include "driverlog.h"
#include "Tracking.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>
#include <stddef.h>
using namespace vr;

class Tracking{
public:
	DriverPose_t Pose() 
	{
		DriverPose_t pose = { 0 };
		pose.poseIsValid = true;
		pose.result = TrackingResult_Running_OK;
		pose.deviceIsConnected = true;

		pose.qWorldFromDriverRotation = HmdQuaternion_Init( 1, 50, 50, 50);
		pose.qDriverFromHeadRotation = HmdQuaternion_Init( 50, 50, 50, 50 );

		return pose;
	}
void updatepose(){ 
    IVRServerDriverHost::TrackedDevicePoseUpdated(CSampleDeviceDriver::GetID(), this->Pose(), (uint32_t) sizeof(vr::DriverPose_t) );
}
};