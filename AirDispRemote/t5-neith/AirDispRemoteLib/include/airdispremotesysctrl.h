#include "AirDispRemotesession.h"

class CAirDispRemoteSysCtrl : public CAirDispRemoteSysCtrlIF 
{
	friend class CAirDispRemoteSession;
public:
	CAirDispRemoteSysCtrl(CAirDispRemoteSession &cSession);
	virtual ~CAirDispRemoteSysCtrl();
    //建立Socket连接
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort);
    //断开Socket连接
    virtual u16 CloseSocket();
    // 发送本地网络媒体码流端口
    virtual u16 SendLocalMediaPort(u32 dwLocalVidPort, u32 dwLocalAudPort);

protected:
    void BuildEventsMap();

    void OnConnected(const CMessage& cMsg);
    void OnStartViewShare(const CMessage& cMsg);

    void OnDicconnected(const CMessage& cMsg);

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    CAirDispRemoteSession    *m_pSession;
};
