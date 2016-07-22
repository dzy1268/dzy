#include "redis.h"

ObjectRedis::ObjectRedis(){}

ObjectRedis::~ObjectRedis()
{
	redisFree(conn);
}

void ObjectRedis::Connect()
{
	conn = redisConnect("127.0.0.1", 6379);
}

void ObjectRedis::Insert(Tick tick)
{
	char buffer[500];
	
	gcvt(tick.zxj, 500, buffer);
	string zxj = buffer;
	gcvt(tick.scjsj, 500, buffer);
	string scjsj = buffer;
	gcvt(tick.zsp, 500, buffer);
	string zsp = buffer;
	gcvt(tick.zccl, 500, buffer);
	string zccl = buffer;
	gcvt(tick.jkp, 500, buffer);
	string jkp = buffer;
	gcvt(tick.zgj, 500, buffer);
	string zgj = buffer;
	gcvt(tick.zdj, 500, buffer);
	string zdj = buffer;
	gcvt(tick.sl, 500, buffer);
	string sl = buffer;
	gcvt(tick.cjje, 500, buffer);
	string cjje = buffer;
	gcvt(tick.ccl, 500, buffer);
	string ccl = buffer;
	gcvt(tick.jsp, 500, buffer);
	string jsp = buffer;
	gcvt(tick.bcjsj, 500, buffer);
	string bcjsj = buffer;
	gcvt(tick.ztbj, 500, buffer);
	string ztbj = buffer;
	gcvt(tick.dtbj, 500, buffer);
	string dtbj = buffer;
	gcvt(tick.zxsd, 500, buffer);
	string zxsd = buffer;
	gcvt(tick.jxsd, 500, buffer);
	string jxsd = buffer;
	gcvt(tick.zhxghm, 500, buffer);
	string zhxghm = buffer;
	gcvt(tick.smj1, 500, buffer);
	string smj1 = buffer;
	gcvt(tick.sml1, 500, buffer);
	string sml1 = buffer;
	gcvt(tick.ssj1, 500, buffer);
	string ssj1 = buffer;
	gcvt(tick.ssl1, 500, buffer);
	string ssl1 = buffer;
	gcvt(tick.smj2, 500, buffer);
        string smj2 = buffer;
        gcvt(tick.sml2, 500, buffer);
        string sml2 = buffer;
        gcvt(tick.ssj2, 500, buffer);
        string ssj2 = buffer;
        gcvt(tick.ssl2, 500, buffer);
        string ssl2 = buffer;
	gcvt(tick.smj3, 500, buffer);
        string smj3 = buffer;
        gcvt(tick.sml3, 500, buffer);
        string sml3 = buffer;
        gcvt(tick.ssj3, 500, buffer);
        string ssj3 = buffer;
        gcvt(tick.ssl3, 500, buffer);
        string ssl3 = buffer;
	gcvt(tick.smj4, 500, buffer);
        string smj4 = buffer;
        gcvt(tick.sml4, 500, buffer);
        string sml4 = buffer;
        gcvt(tick.ssj4, 500, buffer);
        string ssj4 = buffer;
        gcvt(tick.ssl4, 500, buffer);
        string ssl4 = buffer;
	gcvt(tick.smj5, 500, buffer);
        string smj5 = buffer;
        gcvt(tick.sml5, 500, buffer);
        string sml5 = buffer;
        gcvt(tick.ssj5, 500, buffer);
        string ssj5 = buffer;
        gcvt(tick.ssl5, 500, buffer);
        string ssl5 = buffer;
	
	sql = "rpush " + tick.hydm + " " + tick.jyr + "," + tick.hydm + "," + tick.jysdm + "," + tick.hyszjysddm + "," + zxj + "," + scjsj + "," + zsp + "," + zccl + "," + jkp + "," + zgj + "," + zdj + "," + sl + "," + cjje + "," + ccl + "," + jsp + "," + bcjsj + "," + ztbj + "," + dtbj + "," + zxsd + "," + jxsd + ",'" + tick.zhxgsj + "'," + zhxghm + "," + smj1 + "," + sml1 + "," + ssj1 + "," + ssl1 + "," + smj2 + "," + sml2 + "," + ssj2 + "," + ssl2 + "," + smj3 + "," + sml3 + "," + ssj3 + "," + ssl3 + "," + smj4 + "," + sml4 + "," + ssj4 + "," + ssl4 + "," + smj5 + "," + sml5 + "," + ssj5 + "," + ssl5;;
	reply = (redisReply*)redisCommand(conn, sql.c_str());
	
	freeReplyObject(reply);
}

void ObjectRedis::Select(string key, string a, string b, vector<Tick> &vr)
{
	int z;
        string value;
        vector<string> vec;
	vec.reserve(42);
        Tick tick;
        sql = "lrange " + key + " " + a + " " + b;
        reply = (redisReply*)redisCommand(conn, sql.c_str());
        for (int j = 0; j < reply->elements; ++j)
        {
                z = 0;
                vec.clear();
		vec.reserve(42);
                value.clear();
                value = reply->element[j]->str;
                for (int k = 0; k < value.size(); ++k)
                {
                        if(value[k] == ',')
                        {
                                vec.push_back(value.substr(z, k - z));
                                z = k + 1;
                        }
                }
                vec.push_back(value.substr(z, value.length()));
		tick.jyr = vec[0];
                tick.hydm = vec[1];
                tick.jysdm = vec[2];
                tick.hyszjysddm = vec[3];
                tick.zxj = atof(vec[4].c_str());
                tick.scjsj = atof(vec[5].c_str());
                tick.zsp = atof(vec[6].c_str());
                tick.zccl = atoi(vec[7].c_str());
                tick.jkp = atof(vec[8].c_str());
                tick.zgj = atof(vec[9].c_str());
                tick.zdj = atof(vec[10].c_str());
                tick.sl = atoi(vec[11].c_str());
                tick.cjje = atof(vec[12].c_str());
                tick.ccl = atoi(vec[13].c_str());
                tick.jsp = atof(vec[14].c_str());
                tick.bcjsj = atof(vec[15].c_str());
                tick.ztbj = atof(vec[16].c_str());
                tick.dtbj = atof(vec[17].c_str());
                tick.zxsd = atof(vec[18].c_str());
                tick.jxsd = atof(vec[19].c_str());
                tick.zhxgsj = vec[20];
                tick.zhxghm = atoi(vec[21].c_str());
                tick.smj1 = atof(vec[22].c_str());
                tick.sml1 = atoi(vec[23].c_str());
                tick.ssj1 = atof(vec[24].c_str());
                tick.ssl1 = atoi(vec[25].c_str());
                tick.smj2 = atof(vec[26].c_str());
                tick.sml2 = atoi(vec[27].c_str());
                tick.ssj2 = atof(vec[28].c_str());
                tick.ssl2 = atoi(vec[29].c_str());
                tick.smj3 = atof(vec[30].c_str());
                tick.sml3 = atoi(vec[31].c_str());
                tick.ssj3 = atof(vec[32].c_str());
                tick.ssl3 = atoi(vec[33].c_str());
                tick.smj4 = atof(vec[34].c_str());
                tick.sml4 = atoi(vec[35].c_str());
                tick.ssj4 = atof(vec[36].c_str());
                tick.ssl4 = atoi(vec[37].c_str());
                tick.smj5 = atof(vec[38].c_str());
                tick.sml5 = atoi(vec[39].c_str());
                tick.ssj5 = atof(vec[40].c_str());
                tick.ssl5 = atoi(vec[41].c_str());
		vr.push_back(tick);
	}
	freeReplyObject(reply);
}
