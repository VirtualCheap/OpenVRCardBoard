#include "devicedriver.h"

#include <strings.h>

#include "utils.h"

// TODO remove/move/change
// keys for use with the settings API
static const char * const k_pch_Sample_Section = "driver_virtualcheap";
static const char * const k_pch_Sample_SerialNumber_String = "serialNumber";
static const char * const k_pch_Sample_ModelNumber_String = "modelNumber";
static const char * const k_pch_Sample_WindowX_Int32 = "windowX";
static const char * const k_pch_Sample_WindowY_Int32 = "windowY";
static const char * const k_pch_Sample_WindowWidth_Int32 = "windowWidth";
static const char * const k_pch_Sample_WindowHeight_Int32 = "windowHeight";
static const char * const k_pch_Sample_RenderWidth_Int32 = "renderWidth";
static const char * const k_pch_Sample_RenderHeight_Int32 = "renderHeight";
static const char * const k_pch_Sample_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
static const char * const k_pch_Sample_DisplayFrequency_Float = "displayFrequency";

using namespace VirtualCheap;

DeviceDriver::DeviceDriver(){
    m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
    m_ulPropertyContainer = vr::k_ulInvalidPropertyContainer;

    Logger::DriverLog("Using settings values\n");
    m_flIPD = vr::VRSettings()->GetFloat(vr::k_pch_SteamVR_Section, vr::k_pch_SteamVR_IPD_Float);

    char buf[1024];
    vr::VRSettings()->GetString(k_pch_Sample_Section, k_pch_Sample_SerialNumber_String, buf, sizeof(buf));
    m_sSerialNumber = buf;

    vr::VRSettings()->GetString(k_pch_Sample_Section, k_pch_Sample_ModelNumber_String, buf, sizeof(buf));
    m_sModelNumber = buf;

    m_nWindowX = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowX_Int32);
    m_nWindowY = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowY_Int32);
    m_nWindowWidth = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowWidth_Int32);
    m_nWindowHeight = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowHeight_Int32);
    m_nRenderWidth = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_RenderWidth_Int32);
    m_nRenderHeight = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_RenderHeight_Int32);
    m_flSecondsFromVsyncToPhotons = vr::VRSettings()->GetFloat(k_pch_Sample_Section, k_pch_Sample_SecondsFromVsyncToPhotons_Float);
    m_flDisplayFrequency = vr::VRSettings()->GetFloat(k_pch_Sample_Section, k_pch_Sample_DisplayFrequency_Float);

    Logger::DriverLog("driver_null: Serial Number: %s\n", m_sSerialNumber.c_str());
    Logger::DriverLog("driver_null: Model Number: %s\n", m_sModelNumber.c_str());
    Logger::DriverLog("driver_null: Window: %d %d %d %d\n", m_nWindowX, m_nWindowY, m_nWindowWidth, m_nWindowHeight);
    Logger::DriverLog("driver_null: Render Target: %d %d\n", m_nRenderWidth, m_nRenderHeight);
    Logger::DriverLog("driver_null: Seconds from Vsync to Photons: %f\n", m_flSecondsFromVsyncToPhotons);
    Logger::DriverLog("driver_null: Display Frequency: %f\n", m_flDisplayFrequency);
    Logger::DriverLog("driver_null: IPD: %f\n", m_flIPD);
}

DeviceDriver::~DeviceDriver(){}

vr::EVRInitError DeviceDriver::Activate(vr::TrackedDeviceIndex_t p_ObjectId){
    m_unObjectId = p_ObjectId;
    m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);


    vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ModelNumber_String, m_sModelNumber.c_str());
    vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_RenderModelName_String, m_sModelNumber.c_str());
    vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, vr::Prop_UserIpdMeters_Float, m_flIPD);
    vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, vr::Prop_UserHeadToEyeDepthMeters_Float, 0.f);
    vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, vr::Prop_DisplayFrequency_Float, m_flDisplayFrequency);
    vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, vr::Prop_SecondsFromVsyncToPhotons_Float, m_flSecondsFromVsyncToPhotons);

    // return a constant that's not 0 (invalid) or 1 (reserved for Oculus)
    vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, vr::Prop_CurrentUniverseId_Uint64, 2);

    // avoid "not fullscreen" warnings from vrmonitor
    vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, vr::Prop_IsOnDesktop_Bool, false);

    return vr::VRInitError_None;
}

void DeviceDriver::Deactivate(){
    m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
}

void DeviceDriver::EnterStandby(){}

void* DeviceDriver::GetComponent(const char *p_componentNameAndVersion){
    if (!strcasecmp( p_componentNameAndVersion, vr::IVRDisplayComponent_Version)){
        return static_cast<vr::IVRDisplayComponent*>(this);
    }

    // override this to add a component to a driver
    return nullptr;
}

/** debug request from a client */
void DebugRequest(const char *p_Request, char *p_ResponseBuffer, uint32_t p_ResponseBufferSize){
    if(p_ResponseBufferSize >= 1){
        p_ResponseBuffer[0] = 0;
    }
}

vr::DriverPose_t GetPose(){
    vr::DriverPose_t pose = {0};
    pose.poseIsValid = true;
    pose.result = vr::TrackingResult_Running_OK;
    pose.deviceIsConnected = true;

    pose.qWorldFromDriverRotation = VirtualCheep::Utils::HmdQuaternion_Init( 1, 0, 0, 0 );
    pose.qDriverFromHeadRotation = VirtualCheep::Utils::HmdQuaternion_Init( 1, 0, 0, 0 );


    return pose;
}

void DeviceDriver::GetWindowBounds(int32_t *p_X, int32_t *p_Y, uint32_t *p_Width, uint32_t *p_Height){
    *p_X = m_nWindowX;
    *p_Y = m_nWindowY;
    *p_Width = m_nWindowWidth;
    *p_Height = m_nWindowHeight;
}

bool DeviceDriver::IsDisplayOnDesktop(){ // TODO Will change to false later when streaming is implimented
    return true;
}

bool DeviceDriver::IsDisplayRealDisplay(){
    return false;
}

void DeviceDriver::GetRecommendedRenderTargetSize(uint32_t* p_Width, uint32_t* p_Height){
    *p_Width = m_nRenderWidth;
    *p_Height = m_nRenderHeight;
}

void DeviceDriver::GetEyeOutputViewport(vr::EVREye p_eEye, uint32_t* p_X, uint32_t* p_Y, uint32_t* p_Width, uint32_t* p_Height){
    *p_Y = 0;
    *p_Width = m_nWindowWidth / 2;
    *p_Height = m_nWindowHeight;

    if (p_eEye == vr::Eye_Left){
        *p_X = 0;
    }else{
        *p_X = m_nWindowWidth / 2;
    }
}

void DeviceDriver::GetProjectionRaw(vr::EVREye p_eEye, float *p_Left, float *p_Right, float *p_Top, float *p_Bottom){
    *p_Left = -1.0;
    *p_Right = 1.0;
    *p_Top = -1.0;
    *p_Bottom = 1.0;
}

vr::DistortionCoordinates_t DeviceDriver::ComputeDistortion(vr::EVREye p_eEye, float p_fU, float p_fV){
    vr::DistortionCoordinates_t coordinates;
    coordinates.rfBlue[0] = p_fU;
    coordinates.rfBlue[1] = p_fV;
    coordinates.rfGreen[0] = p_fU;
    coordinates.rfGreen[1] = p_fV;
    coordinates.rfRed[0] = p_fU;
    coordinates.rfRed[1] = p_fV;
    return coordinates;
}


void DeviceDriver::RunFrame(){
    // In a real driver, this should happen from some pose tracking thread.
    // The RunFrame interval is unspecified and can be very irregular if some other
    // driver blocks it for some periodic task.
    if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid){
        vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, GetPose(), sizeof(vr::DriverPose_t ));
    }
}

std::string DeviceDriver::GetSerialNumber() const{
    return m_sSerialNumber;
}
