#include <openvr_driver.h>
#include "driverlog.h"
#include <string.h>

using namespace vr;

#ifndef DEVICEDRIVER_VIRTUALCHEAP_H
#define DEVICEDRIVER_VIRTUALCHEAP_H

// keys for use with the settings API
static const char * const k_pch_Sample_Section = "driver_VirtualCheap";
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

class DeviceDriver_VirtualCheap : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
{
public:
    DeviceDriver_VirtualCheap();
    virtual ~DeviceDriver_VirtualCheap();
    virtual EVRInitError Activate( vr::TrackedDeviceIndex_t unObjectId ) ;
    virtual void Deactivate();
    virtual void EnterStandby();
    void *GetComponent( const char *pchComponentNameAndVersion );
    virtual void PowerOff();
    /** debug request from a client */
    virtual void DebugRequest( const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) ;
    virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) ;
    virtual bool IsDisplayOnDesktop();
    virtual bool IsDisplayRealDisplay();
    virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) ;
    virtual void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) ;
    virtual void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) ;
    virtual DistortionCoordinates_t ComputeDistortion( EVREye eEye, float fU, float fV ) ;
    virtual DriverPose_t GetPose() ;
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

#endif // DEVICEDRIVER_VIRTUALCHEAP_H
