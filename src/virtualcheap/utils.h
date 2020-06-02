#ifndef UTILS_H
#define UTILS_H

#include <openvr_driver.h>

namespace VirtualCheep {
    namespace Utils{
        inline vr::HmdQuaternion_t HmdQuaternion_Init(double p_w, double p_x, double p_y, double p_z){
            vr::HmdQuaternion_t quat;
            quat.w = p_w;
            quat.x = p_x;
            quat.y = p_y;
            quat.z = p_z;
            return quat;
        }

    }
}

#endif // UTILS_H
