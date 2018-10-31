#pragma once
//��Դ��Ӧ��ʾ����https://www.cnblogs.com/newpanderking/p/3325674.html

#include <stdio.h>
#include <string>
//#include <afxsock.h>
#include "mysql.h"
using   namespace   std;
class CCppToMysql
{
public:

	//����
	MYSQL mysql;

	/*
	���캯����ϡ������
	*/
	CCppToMysql();
	~CCppToMysql();

	/*
	��Ҫ�Ĺ��ܣ�
	��ʼ�����ݿ�
	�������ݿ�
	�����ַ���

	��ڲ�����
	host ��MYSQL������IP
	port:���ݿ�˿�
	Db�����ݿ�����
	user�����ݿ��û�
	passwd�����ݿ��û�������
	charset��ϣ��ʹ�õ��ַ���
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	int ��0��ʾ�ɹ���1��ʾʧ��
	*/
	int ConnMySQL(char *host, char * port, char * Db, char * user, char* passwd, char * charset, char * * Msg);

	/*
	��Ҫ�Ĺ��ܣ�
	��ѯ����

	��ڲ�����
	SQL����ѯ��SQL���
	Cnum:��ѯ������
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	string ׼�����÷��ص����ݣ�������¼����0x06����,�����λ��0x05����
	��� ���صĳ��ȣ� 0�����ʾ����
	*/
	string SelectData(char * SQL, int Cnum, char * * Msg);

	/*
	��Ҫ���ܣ�
	��������

	��ڲ���
	SQL����ѯ��SQL���
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	int ��0��ʾ�ɹ���1��ʾʧ��
	*/
	int InsertData(char * SQL, char * * Msg);

	/*
	��Ҫ���ܣ�
	�޸�����

	��ڲ���
	SQL����ѯ��SQL���
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	int ��0��ʾ�ɹ���1��ʾʧ��
	*/
	int UpdateData(char * SQL, char * * Msg);


	/*
	��Ҫ���ܣ�
	ɾ������

	��ڲ���
	SQL����ѯ��SQL���
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	int ��0��ʾ�ɹ���1��ʾʧ��
	*/
	int DeleteData(char * SQL, char * * Msg);

	/*
	��Ҫ���ܣ�
	�ر����ݿ�����
	*/
	void CloseMySQLConn();

};