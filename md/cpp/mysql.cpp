#include "mysql.h"

ObjectMysql::ObjectMysql()
{
	mysql_init (&mysql);
}
ObjectMysql::~ObjectMysql(){}

void ObjectMysql::Connect()
{
	mysql_real_connect (&mysql, ip, user, pass, db, 0, NULL, 0);
}

void ObjectMysql::disConnect()
{
	mysql_close(&mysql);
}

void ObjectMysql::Insert(Tick tick)
{
	char buffer[37];
	gcvt(tick.zxj, 37, buffer);
        string zxj = buffer;
        gcvt(tick.scjsj, 37, buffer);
        string scjsj = buffer;
        gcvt(tick.zsp, 37, buffer);
        string zsp = buffer;
        gcvt(tick.zccl, 37, buffer);
        string zccl = buffer;
        gcvt(tick.jkp, 37, buffer);
        string jkp = buffer;
        gcvt(tick.zgj, 37, buffer);
        string zgj = buffer;
        gcvt(tick.zdj, 37, buffer);
        string zdj = buffer;
        gcvt(tick.sl, 37, buffer);
        string sl = buffer;
        gcvt(tick.cjje, 37, buffer);
        string cjje = buffer;
        gcvt(tick.ccl, 37, buffer);
        string ccl = buffer;
        gcvt(tick.jsp, 37, buffer);
        string jsp = buffer;
        gcvt(tick.bcjsj, 37, buffer);
        string bcjsj = buffer;
        gcvt(tick.ztbj, 37, buffer);
        string ztbj = buffer;
        gcvt(tick.dtbj, 37, buffer);
        string dtbj = buffer;
	gcvt(tick.zxsd, 37, buffer);
        string zxsd = buffer;
        gcvt(tick.jxsd, 37, buffer);
        string jxsd = buffer;
        gcvt(tick.zhxghm, 37, buffer);
        string zhxghm = buffer;
        gcvt(tick.smj1, 37, buffer);
        string smj1 = buffer;
        gcvt(tick.sml1, 37, buffer);
        string sml1 = buffer;
        gcvt(tick.ssj1, 37, buffer);
        string ssj1 = buffer;
        gcvt(tick.ssl1, 37, buffer);
        string ssl1 = buffer;
        gcvt(tick.smj2, 37, buffer);
        string smj2 = buffer;
        gcvt(tick.sml2, 37, buffer);
        string sml2 = buffer;
        gcvt(tick.ssj2, 37, buffer);
        string ssj2 = buffer;
        gcvt(tick.ssl2, 37, buffer);
        string ssl2 = buffer;
        gcvt(tick.smj3, 37, buffer);
        string smj3 = buffer;
        gcvt(tick.sml3, 37, buffer);
        string sml3 = buffer;
        gcvt(tick.ssj3, 37, buffer);
        string ssj3 = buffer;
        gcvt(tick.ssl3, 37, buffer);
        string ssl3 = buffer;
        gcvt(tick.smj4, 37, buffer);
	string smj4 = buffer;
	gcvt(tick.sml4, 37, buffer);
        string sml4 = buffer;
        gcvt(tick.ssj4, 37, buffer);
        string ssj4 = buffer;
        gcvt(tick.ssl4, 37, buffer);
        string ssl4 = buffer;
        gcvt(tick.smj5, 37, buffer);
        string smj5 = buffer;
        gcvt(tick.sml5, 37, buffer);
        string sml5 = buffer;
        gcvt(tick.ssj5, 37, buffer);
        string ssj5 = buffer;
        gcvt(tick.ssl5, 37, buffer);
        string ssl5 = buffer;

	string sql = "create table if not exists `" + tick.hydm + "` (`jyr` date DEFAULT NULL,`hydm` varchar(255) NOT NULL,`jysdm` varchar(255) DEFAULT NULL,`hyszjysddm` varchar(255) DEFAULT NULL,`zxj` float DEFAULT NULL,`scjsj` float DEFAULT NULL,`zsp` float DEFAULT NULL,`zccl` int(255) DEFAULT NULL,`jkp` float DEFAULT NULL,`zgj` float DEFAULT NULL,`zdj` float DEFAULT NULL,`sl` int(255) DEFAULT NULL,`cjje` float DEFAULT NULL,`ccl` int(255) DEFAULT NULL,`jsp` float DEFAULT NULL,`bcjsj` float DEFAULT NULL,`ztbj` float DEFAULT NULL,`dtbj` float DEFAULT NULL,`zxsd` float DEFAULT NULL,`jxsd` float DEFAULT NULL,`zhxgsj` time DEFAULT NULL,`zhxghm` int(255) DEFAULT NULL,`smj1` float DEFAULT NULL,`sml1` int(255) DEFAULT NULL,`ssj1` float DEFAULT NULL,`ssl1` int(255) DEFAULT NULL,`smj2` float DEFAULT NULL,`sml2` int(255) DEFAULT NULL,`ssj2` float DEFAULT NULL,`ssl2` int(255) DEFAULT NULL,`smj3` float DEFAULT NULL,`sml3` int(255) DEFAULT NULL,`ssj3` float DEFAULT NULL,`ssl3` int(255) DEFAULT NULL,`smj4` float DEFAULT NULL,`sml4` int(255) DEFAULT NULL,`ssj4` float DEFAULT NULL,`ssl4` int(255) DEFAULT NULL,`smj5` float DEFAULT NULL,`sml5` int(255) DEFAULT NULL,`ssj5` float DEFAULT NULL,`ssl5` int(255) DEFAULT NULL) ENGINE=InnoDB DEFAULT CHARSET=utf8/*!50100 PARTITION BY LINEAR KEY (jyr)(PARTITION p0 ENGINE = InnoDB,PARTITION p1 ENGINE = InnoDB,PARTITION p2 ENGINE = InnoDB,PARTITION p3 ENGINE = InnoDB,PARTITION p4 ENGINE = InnoDB,PARTITION p5 ENGINE = InnoDB,PARTITION p6 ENGINE = InnoDB,PARTITION p7 ENGINE = InnoDB,PARTITION p8 ENGINE = InnoDB,PARTITION p9 ENGINE = InnoDB,PARTITION p10 ENGINE = InnoDB) */;";
	mysql_query (&mysql, sql.c_str());

	sql = "'" + tick.jyr + "','" + tick.hydm + "','" + tick.jysdm + "','" + tick.hyszjysddm + "'," + zxj + "," + scjsj + "," + zsp + "," + zccl + "," + jkp + "," + zgj + "," + zdj + "," + sl + "," + cjje + "," + ccl + "," + jsp + "," + bcjsj + "," + ztbj + "," + dtbj + "," + zxsd + "," + jxsd + ",'" + tick.zhxgsj + "'," + zhxghm + "," + smj1 + "," + sml1 + "," + ssj1 + "," + ssl1 + "," + smj2 + "," + sml2 + "," + ssj2 + "," + ssl2 + "," + smj3 + "," + sml3 + "," + ssj3 + "," + ssl3 + "," + smj4 + "," + sml4 + "," + ssj4 + "," + ssl4 + "," + smj5 + "," + sml5 + "," + ssj5 + "," + ssl5;
	sql = "insert into `" + tick.hydm + "` values(" + sql + ");";
	mysql_query (&mysql, sql.c_str());
}
