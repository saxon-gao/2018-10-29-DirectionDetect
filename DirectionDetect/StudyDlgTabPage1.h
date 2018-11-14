#pragma once
#include "afxcmn.h"


// CStudyDlgTabPage1 对话框

class  CSerialPort;

class CStudyDlgTabPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CStudyDlgTabPage1)

public:
	CStudyDlgTabPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStudyDlgTabPage1();


private:
	//锐视光源亮度调节----串口
	CSerialPort *m_pSerialPort;
public:
	// 光源亮度调节滑条
	CSliderCtrl mSliderCtrl;
	//光源亮度编辑框数据
	int m_iLightIntensity;
	// 光源控制器通过com返回数据
	CString m_szComRet;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY1_P1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	//滑块滑动消息响应
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	

	afx_msg void OnBnClickedButtonLightOn();
	afx_msg void OnBnClickedButtonLightOff();
};
