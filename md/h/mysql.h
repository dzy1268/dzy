#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <mysql/mysql.h>
#include "redis.h"
#include "md.h"

static const char *ip = "localhost";
static const char *user = "ctp";
static const char *pass = "0yV2T0D=s4jX$OQw";
static const char *db = "ctp";
static const int port = 3306;

class ObjectMysql
{
	public:
		ObjectMysql();
		~ObjectMysql();
		virtual void Connect();
		virtual void disConnect();
		virtual void Insert(Tick tick);
	private:
		MYSQL mysql;
};

#endif
