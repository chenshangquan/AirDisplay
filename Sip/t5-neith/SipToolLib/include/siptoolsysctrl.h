#include "siptoolsession.h"

class CSipToolSysCtrl : public CSipToolSysCtrlIF 
{
	friend class CSipToolSession;
public:
	CSipToolSysCtrl(CSipToolSession &cSession);
	virtual ~CSipToolSysCtrl();
    //建立Socket连接
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort);
    //断开Socket连接
    virtual u16 CloseSocket();

protected:
    void BuildEventsMap();

    void OnRegister(const CMessage& cMsg);
    void OnStartViewShare(const CMessage& cMsg);

    void OnDicconnected(const CMessage& cMsg);

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    CSipToolSession    *m_pSession;
};
