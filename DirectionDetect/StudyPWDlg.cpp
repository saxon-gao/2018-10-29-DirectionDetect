// StudyPWDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudyPWDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CStudyPWDlg 对话框

IMPLEMENT_DYNAMIC(CStudyPWDlg, CDialogEx)

CStudyPWDlg::CStudyPWDlg(CString *psz, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY_PW, pParent)
	, m_szPW(_T(""))
{
	m_pszPW_ret = psz;
}

CStudyPWDlg::~CStudyPWDlg()
{
}

void CStudyPWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PW, m_szPW);
}


BEGIN_MESSAGE_MAP(CStudyPWDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CStudyPWDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CStudyPWDlg 消息处理程序


void CStudyPWDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


void CStudyPWDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(1);
	*m_pszPW_ret = m_szPW;
	CDialogEx::OnOK();
}


void CStudyPWDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
