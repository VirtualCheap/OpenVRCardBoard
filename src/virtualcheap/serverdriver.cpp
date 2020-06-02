#include "serverdriver.h"

using namespace VirtualCheap;

ServerDriver::~ServerDriver(){}

vr::EVRInitError ServerDriver::Init(vr::IVRDriverContext *p_driverContext){
    // Init the context and log
    VR_INIT_SERVER_DRIVER_CONTEXT(p_driverContext)
    Logger::InitDriverLog(vr::VRDriverLog());

    // Setup the Hmd and controler drivers
    m_deviceDriver = new DeviceDriver();
    vr::VRServerDriverHost()->TrackedDeviceAdded(m_deviceDriver->GetSerialNumber().c_str(), vr::TrackedDeviceClass_HMD, m_deviceDriver);

    m_controllerDriver = new ControllerDriver();
    vr::VRServerDriverHost()->TrackedDeviceAdded(m_controllerDriver->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, m_controllerDriver);

    return vr::VRInitError_None;
}

void ServerDriver::Cleanup(){
    Logger::CleanupDriverLog();

    delete m_deviceDriver;
    m_deviceDriver = nullptr;
    delete m_controllerDriver;
    m_controllerDriver = nullptr;
}

const char* const* ServerDriver::GetInterfaceVersions(){
    return vr::k_InterfaceVersions;
}

void ServerDriver::RunFrame(){
    if (m_deviceDriver){
        m_deviceDriver->RunFrame();
    }

    if (m_controllerDriver){
        m_controllerDriver->RunFrame();
    }

    vr::VREvent_t vrEvent;
    while (vr::VRServerDriverHost()->PollNextEvent(&vrEvent, sizeof(vrEvent))){
        if (m_controllerDriver){
            m_controllerDriver->ProcessEvent(vrEvent);
        }
    }
}

bool ServerDriver::ShouldBlockStandbyMode(){
    return false;
}

void ServerDriver::EnterStandby(){}

void ServerDriver::LeaveStandby(){}
