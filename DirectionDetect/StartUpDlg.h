#pragma once


// CStartUpDlg 对话框

class CStartUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartUpDlg)

public:
	CStartUpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStartUpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTUP };
#endif
public:
	UINT_PTR m_lSTRTimer;//窗口显示时间计时器ID，OnInitDialog内改时间

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
