#include "conf.h"

using namespace std;

void Conf(string &key, string file)
{
	ifstream conf;
        conf.open(file.c_str());
        if (!conf)
	{
                cout << "no file: " << file <<  endl;
	}
	string em;
	string str;
	size_t pos;
	string tmpkey;
	string value;
	while (getline(conf, em))
	{
		for (int i = 0; i < em.size(); ++i)
		{
			if (em[i] != ' ')
				str += em[i];
		}
		pos = str.find('=');
		tmpkey = str.substr(0, pos);
		if (key == tmpkey)
		{
			value = str.substr(pos + 1, str.size());
		}
		str = "";
	}
	key = value;
	conf.close();
}
