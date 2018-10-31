#pragma once
#include "afxwin.h"


// CStudyDlgTabPage0 对话框

class CStudyDlgTabPage0 : public CDialogEx
{
	DECLARE_DYNAMIC(CStudyDlgTabPage0)

public:
	CStudyDlgTabPage0(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStudyDlgTabPage0();

	void updateMember(void*p);

public:
	//采集模式 单帧、连续
	CComboBox m_CameraAcquisitionMode;
	// 图像宽度
	int m_iImgeWidth;
	// 行频
	int m_iLineRate;
	//曝光时间
	int m_iExposureTime;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY1_P0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
