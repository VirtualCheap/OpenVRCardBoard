#include <openvr_driver.h>
#include "driver_VirtualCheap.h"
#include "driverlog.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>
#include <stddef.h>
using namespace vr;

class Tracking{
public:
        
	static DriverPose_t Pose() 
	{
		DriverPose_t pose = { 0 };
		pose.poseIsValid = true;
		pose.result = TrackingResult_Running_OK;
		pose.deviceIsConnected = true;

		pose.qWorldFromDriverRotation = HmdQuaternion_Init( 1, 0, 0, 0);
		pose.qDriverFromHeadRotation = HmdQuaternion_Init( 1, 0, 0, 0);

		return pose;
	}
    void updatepose(vr::TrackedDeviceIndex_t ID, DriverPose_t pose1, uint32_t size){ 
     vr::VRServerDriverHost()->TrackedDevicePoseUpdated(ID, pose1, size);
    }
};