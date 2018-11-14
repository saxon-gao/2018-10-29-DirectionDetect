#pragma once
#include "afxcmn.h"


// CStudyDlgTabPage1 �Ի���

class  CSerialPort;

class CStudyDlgTabPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CStudyDlgTabPage1)

public:
	CStudyDlgTabPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStudyDlgTabPage1();


private:
	//���ӹ�Դ���ȵ���----����
	CSerialPort *m_pSerialPort;
public:
	// ��Դ���ȵ��ڻ���
	CSliderCtrl mSliderCtrl;
	//��Դ���ȱ༭������
	int m_iLightIntensity;
	// ��Դ������ͨ��com��������
	CString m_szComRet;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY1_P1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	//���黬����Ϣ��Ӧ
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	

	afx_msg void OnBnClickedButtonLightOn();
	afx_msg void OnBnClickedButtonLightOff();
};
