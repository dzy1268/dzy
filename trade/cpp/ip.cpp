#include "ip.h"

int T_c(string server)
{
	int socket_fd;
	struct sockaddr_in server_addr;
	int j = 6;
	string ip;
	string port;
	for (int i = 6; i < server.size(); ++i)
	{
		if(server[i] == ':')
		{
			ip = server.substr(j, i - j);
			j = i;
		}
	}
	port = server.substr(j + 1, server.size());
	char* server_ip;
	const int len_ip = ip.length();
	server_ip = new char[len_ip + 1];
	strcpy(server_ip, ip.c_str());
	char* server_port;
	const int len_port = port.length();
	server_port = new char[len_port + 1];
        strcpy(server_port, port.c_str());
	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socket error: %s(errno:%d)\n)",strerror(errno),errno);
		return 1;
	}
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(server_port));

	if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <=0)
	{
		printf("inet_pton error for %s\n",server_ip);
		return 1;
	}

	unsigned long ul = 1;
	ioctl(socket_fd, FIONBIO, &ul);

	connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	struct timeval timeout;
	fd_set r;
	FD_ZERO(&r);
	FD_SET(socket_fd, &r);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	
	if(select(socket_fd + 1, NULL, &r, NULL, &timeout) == 0)
	{
		close(socket_fd);
		delete server_ip;
		delete server_port;
		return 1;
	}

	close(socket_fd);
	delete server_ip;
	delete server_port;
	return 0;
}
