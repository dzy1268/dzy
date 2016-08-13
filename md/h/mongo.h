#ifndef __MONGO_H__
#define __MONGO_H__

#include "mongo/client/dbclient.h"
#include <iostream>
#include <string>
#include <vector>
#include "redis.h"

using namespace std;

class ObjectMongo
{
	public:
		ObjectMongo();
		~ObjectMongo();
		virtual void Conn();
		virtual void Insert(string table, vector<Tick> &v);
	public:
		mongo::DBClientConnection *c;
};
#endif
