/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tracking.h
 * Author: alexandre
 *
 * Created on 23 de Junho de 2017, 10:59
 */

#ifndef TRACKING_H
#define TRACKING_H

#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>
#include <stddef.h>
#include <openvr_driver.h>

using namespace vr;

class Tracking{
public:
	static DriverPose_t Pose();
        static void updatepose(vr::TrackedDeviceIndex_t ID, DriverPose_t pose1, uint32_t size);
};

#endif /* TRACKING_H */

