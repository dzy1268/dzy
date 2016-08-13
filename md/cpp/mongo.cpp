#include "mongo.h"

ObjectMongo::ObjectMongo()
{
	c = new mongo::DBClientConnection;
}

ObjectMongo::~ObjectMongo()
{
	mongo::client::shutdown();
	delete c;
}

void ObjectMongo::Conn()
{
	c->connect("127.0.0.1");
	mongo::client::initialize();
}

void ObjectMongo::Insert(string table, vector<Tick> &v)
{
	vector<mongo::BSONObj> t;
	for(int i = 0; i < v.size(); i++)
	{
		mongo::BSONObjBuilder item;
		item.append("jyr", v[i].jyr);
		item.append("hydm", v[i].hydm);
		item.append("jysdm", v[i].jysdm);
		item.append("hyszjysddm", v[i].hyszjysddm);
		item.append("zxj", v[i].zxj);
		item.append("scjsj", v[i].scjsj);
		item.append("zsp", v[i].zsp);
		item.append("zccl", v[i].zccl);
		item.append("jkp", v[i].jkp);
		item.append("zgj", v[i].zgj);
		item.append("sl", v[i].sl);
		item.append("cjje", v[i].cjje);
		item.append("ccl", v[i].ccl);
		item.append("jsp", v[i].jsp);
		item.append("bcjsj", v[i].bcjsj);
		item.append("ztbj", v[i].ztbj);
		item.append("zxsd", v[i].zxsd);
		item.append("jxsd", v[i].jxsd);
		item.append("zhxgsj", v[i].zhxgsj);
		item.append("zhxghm", v[i].zhxghm);
		item.append("smj1", v[i].smj1);
		item.append("sml1", v[i].sml1);
		item.append("ssj1", v[i].ssj1);
		item.append("ssl1", v[i].ssl1);
		item.append("smj2", v[i].smj1);
		item.append("sml2", v[i].sml1);
                item.append("ssj2", v[i].ssj1);
                item.append("ssl2", v[i].ssl1);
		item.append("smj3", v[i].smj1);
                item.append("sml3", v[i].sml1);
                item.append("ssj3", v[i].ssj1);
                item.append("ssl3", v[i].ssl1);
                item.append("smj4", v[i].smj1);
                item.append("sml4", v[i].sml1);
                item.append("ssj4", v[i].ssj1);
                item.append("ssl4", v[i].ssl1);
                item.append("smj5", v[i].smj1);
                item.append("sml5", v[i].sml1);
                item.append("ssj5", v[i].ssj1);
                item.append("ssl5", v[i].ssl1);
		t.push_back(item.obj());
	}
	c->insert(table, t, 0);
}
