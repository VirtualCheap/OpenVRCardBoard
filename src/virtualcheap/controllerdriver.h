#ifndef CONTROLLERDRIVER_H
#define CONTROLLERDRIVER_H

#include <openvr_driver.h>

namespace VirtualCheap{
    class ControllerDriver: public vr::ITrackedDeviceServerDriver{
    public:
        ControllerDriver();
        virtual ~ControllerDriver();

        // vr::ITrackedDeviceServerDriver
        virtual vr::EVRInitError Activate(vr::TrackedDeviceIndex_t p_ObjectId);
        virtual void Deactivate();
        virtual void EnterStandby();
        virtual void* GetComponent(const char* pchComponentNameAndVersion);
        virtual void DebugRequest(const char* p_Request, char* p_ResponseBuffer, uint32_t p_ResponseBufferSize);
        virtual vr::DriverPose_t GetPose();

        void RunFrame();
        void ProcessEvent(const vr::VREvent_t& vrEvent);
        std::string GetSerialNumber() const;

    private:
        vr::TrackedDeviceIndex_t m_unObjectId;
        vr::PropertyContainerHandle_t m_ulPropertyContainer;

        vr::VRInputComponentHandle_t m_compA;
        vr::VRInputComponentHandle_t m_compB;
        vr::VRInputComponentHandle_t m_compC;
        vr::VRInputComponentHandle_t m_compHaptic;

        std::string m_sSerialNumber;
        std::string m_sModelNumber;


    };
}

#endif // CONTROLLERDRIVER_H
