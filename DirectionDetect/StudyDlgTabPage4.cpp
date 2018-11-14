// StudyDlgTabPage4.cpp : 实现文件
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlgTabPage4.h"
#include "afxdialogex.h"
#include "Ini.h"
#include "logger\StaticLogger.h"



extern CStaticLogger g_logger;
// CStudyDlgTabPage4 对话框

IMPLEMENT_DYNAMIC(CStudyDlgTabPage4, CDialogEx)

CStudyDlgTabPage4::CStudyDlgTabPage4(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY1_P4, pParent)
	, m_szOld_pw(_T(""))
	, m_szNew_pw(_T(""))
{

}

CStudyDlgTabPage4::~CStudyDlgTabPage4()
{
}

void CStudyDlgTabPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD_PW, m_szOld_pw);
	DDX_Text(pDX, IDC_EDIT_NEW_PW, m_szNew_pw);
}


BEGIN_MESSAGE_MAP(CStudyDlgTabPage4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CStudyDlgTabPage4::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudyDlgTabPage4::OnBnClickedButton2)
END_MESSAGE_MAP()


// CStudyDlgTabPage4 消息处理程序


void CStudyDlgTabPage4::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	//更改密码
	if (m_pCini->GetString(_T("Studypw"), _T("szStudypw")) == m_szOld_pw)
	{
		m_pCini->WriteString(_T("Studypw"), _T("szStudypw"), m_szNew_pw);
		m_szOld_pw.Empty();
		m_szNew_pw.Empty();
		UpdateData(0);
		g_logger->Log(ILogger::LogLevel::LL_INFO, _T("更改密码成功"));
		AfxMessageBox(_T("更改密码成功"));
	}
	else
	{
		AfxMessageBox(_T("输入正确密码"));
		m_szOld_pw.Empty();
		m_szNew_pw.Empty();
		UpdateData(0);
	}
}


void CStudyDlgTabPage4::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_szOld_pw.Empty();
	m_szNew_pw.Empty();
	UpdateData(0);
}
