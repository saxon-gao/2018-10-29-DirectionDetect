#include "StdAfx.h"

#include <Windows.h>  
#include "LasyLSerialPort.h"  
#include <process.h>    
#include <iostream>
using namespace std;



ComAsy::ComAsy():
m_hCom(INVALID_HANDLE_VALUE),  
m_IsOpen(false),  
m_Thread(NULL)  
{  
	memset(&m_ovWait, 0, sizeof(m_ovWait));  
	memset(&m_ovWrite, 0, sizeof(m_ovWrite));  
	memset(&m_ovRead, 0, sizeof(m_ovRead));  
}  

ComAsy::~ComAsy()  
{  
	UninitCOM();  
} 


bool ComAsy::InitCOM(LPCTSTR Port)  
{  
 	m_hCom = CreateFile(Port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,  
 		FILE_FLAG_OVERLAPPED|FILE_ATTRIBUTE_NORMAL,//�����첽��ʶ  
 		NULL);  
 	if (INVALID_HANDLE_VALUE == m_hCom)  
 	{  
 		return false;  
 	}  
 	SetupComm(m_hCom, 4096, 4096);//���÷��ͽ��ջ���  
 
 	DCB dcb;  
 	GetCommState(m_hCom, &dcb);  
 	dcb.DCBlength = sizeof(dcb);  
 	dcb.BaudRate = CBR_9600;  
 	dcb.StopBits = ONESTOPBIT;  
 	SetCommState(m_hCom, &dcb);//���ô���  
 
 	PurgeComm(m_hCom, PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT);  
 
 	COMMTIMEOUTS ct;  
 	ct.ReadIntervalTimeout = MAXDWORD;//��ȡ����ʱ����Ϊ��WaitCommEvent�ȴ�����  
 	ct.ReadTotalTimeoutConstant = 0;  //  
 	ct.ReadTotalTimeoutMultiplier = 0;//  
 
 	ct.WriteTotalTimeoutMultiplier = 500;  
 	ct.WriteTotalTimeoutConstant = 5000;  
 
 	SetCommTimeouts(m_hCom, &ct);  
 
 	//�����¼�����  
 	m_ovRead.hEvent = CreateEvent(NULL, false, false, NULL);  
 	m_ovWrite.hEvent = CreateEvent(NULL, false, false, NULL);  
 	m_ovWait.hEvent = CreateEvent(NULL, false, false, NULL);  
 
 	SetCommMask(m_hCom, EV_ERR | EV_RXCHAR);//���ý����¼�  
 
 	//������ȡ�߳�  
 	m_Thread = (HANDLE)_beginthreadex(NULL, 0, &ComAsy::OnRecv, this, 0, NULL);  
 	m_IsOpen = true;  
	return true;  
}  



bool ComAsy::ComWrite(LPBYTE buf, int &len)  
{  
 	BOOL rtn = FALSE;  
 	DWORD WriteSize = 0;  
 
 	PurgeComm(m_hCom, PURGE_TXCLEAR|PURGE_TXABORT);  
 	m_ovWait.Offset = 0;  
 	rtn = WriteFile(m_hCom, buf, len, &WriteSize, &m_ovWrite);  
 
 	len = 0;  
 	if (FALSE == rtn && GetLastError() == ERROR_IO_PENDING)//��̨��ȡ  
 	{  
 		//�ȴ�����д�����  
 		if (FALSE == ::GetOverlappedResult(m_hCom, &m_ovWrite, &WriteSize, TRUE))  
 		{  
 			return false;  
 		}  
 	}  
 
 	len = WriteSize;  
 	return rtn != FALSE;  
}  

char g_lastLeft[8] = {0};
unsigned int g_lastLeftNum = 0;
unsigned int __stdcall ComAsy::OnRecv( void* LPParam)  
{  
 	ComAsy *obj = static_cast<ComAsy*>(LPParam);  
 
 	DWORD WaitEvent = 0, Bytes = 0;  
 	BOOL Status = FALSE;  
 	BYTE ReadBuf[4096];  
 	DWORD Error;  
 	COMSTAT cs = {0};  
 
 	while(obj->m_IsOpen)  
 	{  
 		WaitEvent = 0;  
 		obj->m_ovWait.Offset = 0;  
 		Status = WaitCommEvent(obj->m_hCom,&WaitEvent, &obj->m_ovWait );  
 		//WaitCommEventҲ��һ���첽���������Ҫ�ȴ�  
 		if (FALSE == Status && GetLastError() == ERROR_IO_PENDING)//  
 		{  
 			//����������������̻߳�ͣ�ڴˣ����hCom�رջ���������False  
 			Status = GetOverlappedResult(obj->m_hCom, &obj->m_ovWait,  &Bytes, TRUE);  
 		}  
 		ClearCommError(obj->m_hCom, &Error, &cs);  
 		if (TRUE == Status //�ȴ��¼��ɹ�  
 			&& WaitEvent&EV_RXCHAR//�����������ݵ���  
 			&& cs.cbInQue > 0)//������  
 		{  
 			Bytes = 0;  
 			obj->m_ovRead.Offset = 0;  
 			memset(ReadBuf, 0, sizeof(ReadBuf));  
 			//�����Ѿ����ﻺ������ReadFile���ᵱ���첽�������������ȡ������True  
 			Status = ReadFile(obj->m_hCom, ReadBuf, sizeof(ReadBuf), &Bytes, &obj->m_ovRead);  
 			if (Status != FALSE)  
 			{  
 				//cout<<"Read:"<<(LPCSTR*)ReadBuf<<"   Len:"<< Bytes<<endl;  
				unsigned int i = 0;
				cout<<"Len:"<< Bytes<<"\t\t";
				if(Bytes < 8)
				{
					if(0==g_lastLeftNum)
					{
						g_lastLeftNum = Bytes;
						memcpy(g_lastLeft, ReadBuf, g_lastLeftNum);

					}else
					{
						memcpy(g_lastLeft+g_lastLeftNum, ReadBuf, Bytes);
						if(Bytes+g_lastLeftNum == 8)
						{
							memcpy(ReadBuf,g_lastLeft,8);
							g_lastLeftNum = 0;
						}else
						{
							g_lastLeftNum = Bytes+g_lastLeftNum;
						}
					}

				}else if(Bytes > 8)
				{
					//printf("read bytes num error\n");
				}
				if(0 == g_lastLeftNum)
				{
					for (i=0; i<8;)
					{
						INT16 n = 0;
						memcpy(&n, ReadBuf+i, 1);
						printf("%02x ",n);
						i++;
					}
					cout<<endl;
					PurgeComm(obj->m_hCom, PURGE_RXCLEAR|PURGE_RXABORT); 
				}
 			}  
 		}  
 
 	}  
	return 0;  
}  


void ComAsy::UninitCOM()  
{  
 	m_IsOpen = false;  
 	if (INVALID_HANDLE_VALUE != m_hCom)  
 	{  
 		CloseHandle(m_hCom);  
 		m_hCom = INVALID_HANDLE_VALUE;  
 	}  
 	if (NULL != m_ovRead.hEvent)  
 	{  
 		CloseHandle(m_ovRead.hEvent);  
 		m_ovRead.hEvent = NULL;  
 	}  
 	if (NULL != m_ovWrite.hEvent)  
 	{  
 		CloseHandle(m_ovWrite.hEvent);  
 		m_ovWrite.hEvent = NULL;  
 	}  
 	if (NULL != m_ovWait.hEvent)  
 	{  
 		CloseHandle(m_ovWait.hEvent);  
 		m_ovWait.hEvent = NULL;  
 	}  
 	if (NULL != m_Thread)  
 	{  
 		WaitForSingleObject(m_Thread, 5000);//�ȴ��߳̽���  
 		CloseHandle(m_Thread);  
 		m_Thread = NULL;  
 	}  
}  

