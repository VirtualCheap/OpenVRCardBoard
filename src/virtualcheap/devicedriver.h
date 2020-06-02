#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#include <openvr_driver.h>

#include "logger.h"

namespace VirtualCheap {
    class DeviceDriver : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent{
    public:
        DeviceDriver();
        virtual ~DeviceDriver();

        // vr::ITrackedDeviceServerDriver
        virtual vr::EVRInitError Activate(vr::TrackedDeviceIndex_t p_ObjectId);
        virtual void Deactivate();
        virtual void EnterStandby();
        virtual void* GetComponent(const char *p_componentNameAndVersion);
        virtual void DebugRequest(const char *p_Request, char *p_ResponseBuffer, uint32_t p_ResponseBufferSize);
        virtual vr::DriverPose_t GetPose();

        // vr::IVRDisplayComponent
        virtual void GetWindowBounds(int32_t *p_X, int32_t *p_Y, uint32_t *p_Width, uint32_t *p_Height);
        virtual bool IsDisplayOnDesktop();
        virtual bool IsDisplayRealDisplay();
        virtual void GetRecommendedRenderTargetSize(uint32_t* p_Width, uint32_t* p_Height);
        virtual void GetEyeOutputViewport(vr::EVREye p_eEye, uint32_t* p_X, uint32_t* p_Y, uint32_t* p_Width, uint32_t* p_Height);
        virtual void GetProjectionRaw(vr::EVREye p_eEye, float *p_Left, float *p_Right, float *p_Top, float *p_Bottom);
        virtual vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye p_eEye, float p_fU, float p_fV);

        void RunFrame();
        std::string GetSerialNumber() const;

    private:
        vr::TrackedDeviceIndex_t m_unObjectId;
        vr::PropertyContainerHandle_t m_ulPropertyContainer;

        std::string m_sSerialNumber;
        std::string m_sModelNumber;

        int32_t m_nWindowX;
        int32_t m_nWindowY;
        int32_t m_nWindowWidth;
        int32_t m_nWindowHeight;
        int32_t m_nRenderWidth;
        int32_t m_nRenderHeight;
        float m_flSecondsFromVsyncToPhotons;
        float m_flDisplayFrequency;
        float m_flIPD;
    };
}

#endif // DEVICEDRIVER_H
