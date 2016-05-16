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

class CNatConn : public CRefObject
{
public:
	CNatConn();
	virtual ~CNatConn();

	virtual void Close();

	virtual void OnConnect(net_handle_t handle);
	virtual void OnClose();

	virtual void HandlePdu(IM::Message::IMAudioReq* recvbuf);
private:	
	void OnUDPRead();
	void OnUDPWrite();

protected:
	net_handle_t	m_sock_handle;
};


typedef hash_map<uint32_t, CNatConn*> NatConnMap_t;

CNatConn* FindNatConnByHandle(uint32_t handle);

/*
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
*/
#endif /* NATCONN_H_ */
