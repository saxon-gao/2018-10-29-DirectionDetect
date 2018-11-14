#pragma once


// CStudyPWDlg 对话框

class CStudyPWDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudyPWDlg)

public:
	CString m_szPW;
	CString *m_pszPW_ret;



public:
	CStudyPWDlg(CString *psz, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStudyPWDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY_PW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedCancel();
};
