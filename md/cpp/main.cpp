#include "md.h"
#include "conf.h"
#include "ip.h"

int main(int argc, char* argv[])
{
	string file = "conf/server.conf";
	string key = "server";
	string s;
	Conf(key, file);
	int j = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		if(key[i] == ';')
		{
			s = key.substr(j, i - j);
			j = i + 1;
			if ( T_c(s) == '0' )
			{
				break;
			}
		}
	}
	char *server;
	const int len = s.length();
	server = new char[len + 1];
	strcpy(server, s.c_str());
	CThostFtdcMdApi* pUserApi = CThostFtdcMdApi::CreateFtdcMdApi("./flow/",false,false);
	MdSpi sh(pUserApi);
	
	sh.ins = argc - 1;
	if (sh.ins > 0)
	{
		for (int i = 0; i < sh.ins; ++i)
		{
			vec.push_back(argv[i + 1]);
		}
	}

	pUserApi->RegisterSpi(&sh);
	pUserApi->RegisterFront(server);
	pUserApi->Init();
	pUserApi->Join();
	pUserApi->Release();
}
