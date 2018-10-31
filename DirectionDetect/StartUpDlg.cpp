// StartUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StartUpDlg.h"
#include "afxdialogex.h"
#include "resource.h" 

// CStartUpDlg 对话框

IMPLEMENT_DYNAMIC(CStartUpDlg, CDialogEx)

CStartUpDlg::CStartUpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STARTUP, pParent)
{
	
}

CStartUpDlg::~CStartUpDlg()
{
}

void CStartUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartUpDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CStartUpDlg 消息处理程序


void CStartUpDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CStartUpDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(m_lSTRTimer);
	OnOK();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CStartUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lSTRTimer = SetTimer( 1, 2000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
