

#include "TMysql.h"
/*方法一 使用mysql c api
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <iostream>
using namespace std;

PersonInfo TestMysql()
{
	PersonInfo personInfo;
	const char user[] = "chenglong";
	const char pswd[] = "123456";
	const char host[] = "192.168.1.21";
	const char table[] = "nfgame";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		res = mysql_query(&myCont, "select * from test");//查询
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					//cout << "id:\t\t" << sql_row[0] << endl;
					//cout << "name:\t\t" << sql_row[1] << endl;
					//cout << "email:\t\t" << sql_row[2] << endl;
					personInfo.id = atoi(sql_row[0]);
					personInfo.name = string(sql_row[1]);
					personInfo.email = string(sql_row[2]);
					break;
				}
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else
	{
		cout << "connect failed!" << endl;
	}
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&myCont);
	

	
	
	
	return personInfo;
}
//*/



//*方法二 使用MySQL Connector C++ 1.1.5 和 boost
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/metadata.h"
#include "cppconn/exception.h"

using namespace std;
using namespace sql;

PersonInfo TestMysql()
{
	PersonInfo personInfo;
	sql::mysql::MySQL_Driver *driver = 0;
	sql::Connection *conn = 0;

	try
	{
		driver = sql::mysql::get_mysql_driver_instance();
		conn = driver->connect("tcp://192.168.1.21:3306/nfgame", "chenglong", "123456");
		cout << "连接成功" << endl;
	}
	catch (...)
	{
		cout << "连接失败" << endl;
	}
	sql::Statement* stat = conn->createStatement();
	stat->execute("set names 'gbk'");
	ResultSet *res;
	res = stat->executeQuery("select * from test");
	while (res->next())
	{
		personInfo.id = res->getInt("Id");
		personInfo.name = res->getString("name").c_str();
		personInfo.email = res->getString("email").c_str();
		break;
	}
	if (conn != 0)
	{
		delete conn;
	}
	return personInfo;

}
//*/
