/*
 * NatConn.h
 *
 *  Created on: 2013-7-4
 *      Author: ziteng@mogujie.com
 */

#ifndef __NATCONN_H__
#define __NATCONN_H__

#include "netlib.h"
#include "util.h"

class CNatConn : public CImConn
{
public:
	CNatConn();
	virtual ~CNatConn();

	virtual void Close();

	virtual void OnConnect(net_handle_t handle);
	virtual void OnClose();
	virtual void OnTimer(uint64_t curr_tick);

	virtual void HandlePdu(CImPdu* pPdu);

private:
	void _HandleOnlineUserInfo(CImPdu* pPdu);
	void _HandleUserStatusUpdate(CImPdu* pPdu);
	void _HandleRoleSet(CImPdu* pPdu);
	void _HandleUsersStatusRequest(CImPdu* pPdu);
	void _HandleMsgReadNotify(CImPdu* pPdu);
	void _HandleKickUser(CImPdu* pPdu);
    
	void _DispatchFriend(uint32_t friend_cnt, uint32_t* friend_id_list);

	void _BroadcastMsg(CImPdu* pPdu, CNatConn* pFromConn = NULL);
    
private:
    void _UpdateUserStatus(uint32_t user_id, uint32_t status, uint32_t client_type);
    void _SendPduToUser(uint32_t user_id, CImPdu* pPdu, bool bAll);
    
private:
	bool			m_bMaster;

protected:
	net_handle_t	m_sock_handle;
};


typedef hash_map<uint32_t, CNatConn*> NatConnMap_t;

CNatConn* FindHttpConnByHandle(uint32_t handle);


// Client��¼ʱ����������͵���Ϣ
struct stLoginMessage
{
	char userName[20]; // ������û���
	int userid;//cahr password[10];
};

// Clientע��ʱ���͵���Ϣ
struct stLogoutMessage
{
	char userName[20];
};

// Client���������������һ��Client(userName)���Լ�������UDP����Ϣ
struct stP2PTranslate
{
	char userName[20];
};

// Client����������͵���Ϣ��ʽ
struct stMessage
{
	int iMessageType;
	union _message
	{
		stLoginMessage loginmember;	// ��½
		stLogoutMessage logoutmember;	// �˳�
		stP2PTranslate translatemessage;// �����
	}message;
};

#endif /* NATCONN_H_ */
