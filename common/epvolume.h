#ifndef _EPVOLUME_H_
#define _EPVOLUME_H_

// Epvolume.h -- Implementation of IAudioEndpointVolumeCallback interface

//#include <commctrl.h>
//#include <mmdeviceapi.h>
#include <endpointvolume.h>

// Dialog handle from dialog box procedure
extern HWND g_hVolumeCtrlDlg;

// Client's proprietary event-context GUID
extern GUID g_guidMyContext;

// Maximum volume level on trackbar
#define MAX_VOL          100
#define DIVIDED_NUM      83.33

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

#define HANDLE_ERROR(hr)  \
	if (FAILED(hr)) { return; }

//-----------------------------------------------------------
// Client implementation of IAudioEndpointVolumeCallback
// interface. When a method in the IAudioEndpointVolume
// interface changes the volume level or muting state of the
// endpoint device, the change initiates a call to the
// client's IAudioEndpointVolumeCallback::OnNotify method.
//-----------------------------------------------------------
class CAudioEndpointVolumeCallback : public IAudioEndpointVolumeCallback
{
    LONG _cRef;
	BOOL m_bMute;
	int  m_nVolume;

public:
    CAudioEndpointVolumeCallback() :
        _cRef(1)
    {
		m_bMute = FALSE;
		m_nVolume = 0;
    }

    ~CAudioEndpointVolumeCallback()
    {
    }

    // IUnknown methods -- AddRef, Release, and QueryInterface

    ULONG STDMETHODCALLTYPE AddRef()
    {
        return InterlockedIncrement(&_cRef);
    }

    ULONG STDMETHODCALLTYPE Release()
    {
        ULONG ulRef = InterlockedDecrement(&_cRef);
        if (0 == ulRef)
        {
            delete this;
        }
        return ulRef;

    }

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID **ppvInterface)
    {
        if (IID_IUnknown == riid)
        {
            AddRef();
            *ppvInterface = (IUnknown*)this;
        }
        else if (__uuidof(IAudioEndpointVolumeCallback) == riid)
        {
            AddRef();
            *ppvInterface = (IAudioEndpointVolumeCallback*)this;
        }
        else
        {
            *ppvInterface = NULL;
            return E_NOINTERFACE;
        }
        return S_OK;
    }

    // Callback method for endpoint-volume-change notifications.
    HRESULT STDMETHODCALLTYPE OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify)
    {
        if (pNotify == NULL)
        {
            return E_INVALIDARG;
        }
		
		if (g_hVolumeCtrlDlg != NULL && pNotify->guidEventContext != g_guidMyContext)
		{
			BOOL bMute = pNotify->bMuted;
			int nVolume = int(MAX_VOL*pNotify->fMasterVolume + 0.5);

			if ( m_bMute != bMute || m_nVolume != nVolume )
			{
				m_bMute = bMute;
				m_nVolume = nVolume;
				PostMessage( g_hVolumeCtrlDlg, WM_VOLUMECTRL_CHANGE, (WPARAM)m_bMute, (LPARAM)m_nVolume );
			}
		}
        return S_OK;
    }
};

#endif//_EPVOLUME_H_