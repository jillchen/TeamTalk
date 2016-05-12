/*
 * nat_server.cpp
 *
 *  Created on: 2016-5-6
 *      Author: 342418923@qq.com
 */

#include "NatConn.h"
#include "netlib.h"
#include "ConfigFileReader.h"
#include "version.h"

// this callback will be replaced by imconn_callback() in OnConnect()
void nat_serv_callback(void* callback_data, uint8_t msg, uint32_t handle, void* pParam)
{
	if (msg == SOCKET_STATE_UDP_BIND)
	{
		CNatConn* pConn = new CNatConn();   
		pConn->OnConnect(handle);			// bind callback
	}
	else
	{
		log("!!!error msg: %d ", msg);
	}
}
/*
void nat_serv_callback(SOCKET m_socket)
{
	CNatConn* pConn = new CNatConn(); 
	pConn->OnExec(m_socket);			// bind
}*/

int main(int argc, char* argv[])
{
	if ((argc == 2) && (strcmp(argv[1], "-v") == 0)) {
		printf("Server Version: NatServer/%s\n", VERSION);
		printf("Server Build: %s %s\n", __DATE__, __TIME__);
		return 0;
	}

	signal(SIGPIPE, SIG_IGN);
	srand(time(NULL));

	CConfigFileReader config_file("natserver.conf");

	// Ҫ�󶨶˿ں�IP
	char* listen_ip = config_file.GetConfigName("ListenIP");
	char* str_listen_msg_port = config_file.GetConfigName("ListenPort");

	if (!listen_ip || !str_listen_msg_port) {
		log("config item missing, exit... ");
		return -1;
	}

	uint16_t listen_msg_port = atoi(str_listen_msg_port);

	int ret = netlib_init();

	if (ret == NETLIB_ERROR)
		return ret;

	CStrExplode listen_ip_list(listen_ip, ';');// ��Ҫ�ֺŷָ�


	for (uint32_t i = 0; i < listen_ip_list.GetItemCnt(); i++) {
		// socket SOCK_DGRAM  (UDP)
		ret =  netlib_listen_udp_bind(listen_ip_list.GetItem(i), str_listen_msg_port, nat_serv_callback, NULL);
		if (ret == NETLIB_ERROR)
			return ret;

	}

	printf("server start udp bind wait on: %s:%d\n", listen_ip,  listen_msg_port);

	//init_natconn_timer_callback(); // ������û��Ҫ

	printf("now enter the event loop...\n");

    writePid(); // FILE* f = fopen("server.pid", "w"); д����id ���ļ���
	netlib_eventloop();  // ��epoll udp
	// UDP�������� �������մ����߳� 
	// nat_serv_callback(m_socket);

	return 0;
}

