#pragma once



class ComAsy  
{  
public:   
	ComAsy();  
	~ComAsy();  
	bool InitCOM(LPCTSTR Port);//�򿪴���  
	void UninitCOM(); //�رմ��ڲ�����  

	//д������  
	bool ComWrite(LPBYTE buf, int &len);  

	//��ȡ�߳�  
	static unsigned int __stdcall OnRecv(void*);  


private:  
	HANDLE m_hCom;  
	OVERLAPPED m_ovWrite;//����д������  
	OVERLAPPED m_ovRead;//���ڶ�ȡ����  
	OVERLAPPED m_ovWait;//���ڵȴ�����  
	volatile bool m_IsOpen;//�����Ƿ��  
	HANDLE m_Thread;//��ȡ�߳̾��  
};  