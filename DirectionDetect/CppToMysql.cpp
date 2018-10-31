
#include "stdafx.h"
#include "CppToMysql.h"


CCppToMysql::CCppToMysql()
{
}

CCppToMysql::~CCppToMysql()
{
}

//��ʼ������
int CCppToMysql::ConnMySQL(char *host, char * port, char * Db, char * user, char* passwd, char * charset, char ** Msg)
{
	if (mysql_init(&mysql) == NULL)
	{
		*Msg = "inital mysql handle error";
		return 1;
	}

	if (mysql_real_connect(&mysql, host, user, passwd, Db, 0, NULL, 0) == NULL)
	{
		*Msg = "Failed to connect to database: Error";
		return 1;
	}

	if (mysql_set_character_set(&mysql, "GBK") != 0)
	{
		*Msg = "mysql_set_character_set Error";
		return 1;
	}
	return 0;
}

//��ѯ����
string CCppToMysql::SelectData(char * SQL, int Cnum, char * * Msg)
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf(sql, SQL);
	int rnum = 0;
	char rg = 0x06;//�и���
	char cg = { 0x05 };//�ֶθ���

	if (mysql_query(&mysql, sql) != 0)
	{
		*Msg = "select ps_info Error";
		return "";
	}
	m_res = mysql_store_result(&mysql);

	if (m_res == NULL)
	{
		*Msg = "select username Error";
		return "";
	}
	string str("");
	while (m_row = mysql_fetch_row(m_res))
	{
		for (int i = 0; i < Cnum; i++)
		{
			str += m_row[i];
			str += rg;
		}
		str += cg;
		rnum++;
	}

	mysql_free_result(m_res);

	return str;
}


//��������
int CCppToMysql::InsertData(char * SQL, char * * Msg)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		*Msg = "Insert Data Error";
		return 1;
	}
	return 0;
}

//��������
int CCppToMysql::UpdateData(char * SQL, char * * Msg)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		*Msg = "Update Data Error";
		return 1;
	}
	return 0;
}

//ɾ������
int CCppToMysql::DeleteData(char * SQL, char * * Msg)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		*Msg = "Delete Data error";
		return 1;
	}
	return 0;
}

//�ر����ݿ�����
void CCppToMysql::CloseMySQLConn()
{
	mysql_close(&mysql);
}