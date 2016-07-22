#ifndef __REDIS_H__
#define __REDIS_H__

#include <hiredis/hiredis.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

struct Tick
{
	string jyr;
        string hydm;
        string jysdm;
        string hyszjysddm;
        float zxj;
        float scjsj;
        float zsp;
        unsigned int zccl;
        float jkp;
        float zgj;
        float zdj;
        unsigned int sl;
        float cjje;
        unsigned int ccl;
        float jsp;
        float bcjsj;
        float ztbj;
        float dtbj;
        float zxsd;
        float jxsd;
        string zhxgsj;
        unsigned int zhxghm;
        float smj1;
        unsigned int sml1;
        float ssj1;
        unsigned int ssl1;
        float smj2;
        unsigned int sml2;
        float ssj2;
        unsigned int ssl2;
        float smj3;
        unsigned int sml3;
        float ssj3;
        unsigned int ssl3;
        float smj4;
        unsigned int sml4;
	float ssj4;
        unsigned int ssl4;
        float smj5;
        unsigned int sml5;
        float ssj5;
        unsigned int ssl5;
};

extern vector<Tick> vr;

class ObjectRedis
{
	public:
		ObjectRedis();
		~ObjectRedis();
		virtual void Connect();
		virtual void Insert(Tick tick);
		virtual void Select(string key, string a, string b ,vector<Tick> &v);
	private:
		redisContext* conn;
		redisReply* reply;
		string sql;
};

#endif
