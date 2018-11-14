// StudyDlgTabPage2.cpp : 实现文件
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlgTabPage2.h"
#include "afxdialogex.h"






// CStudyDlgTabPage2 对话框

IMPLEMENT_DYNAMIC(CStudyDlgTabPage2, CDialogEx)

CStudyDlgTabPage2::CStudyDlgTabPage2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY1_P2, pParent)
{




}

CStudyDlgTabPage2::~CStudyDlgTabPage2()
{

		
}

void CStudyDlgTabPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStudyDlgTabPage2, CDialogEx)
	ON_BN_CLICKED(IDC_BanKa_SET, &CStudyDlgTabPage2::OnBnClickedBankaSet)
END_MESSAGE_MAP()


// CStudyDlgTabPage2 消息处理程序


void CStudyDlgTabPage2::OnBnClickedBankaSet()
{
	//if ((int)ShellExecute(m_hWnd, NULL,
	//	_T("C:\\Users\\Administrator\\Desktop\\Shell_VBCode\\Shell.exe"),
	//	NULL, NULL, SW_SHOWNORMAL) <= 32)
	//{
	//	AfxMessageBox(_T("打开板卡设置程序失败！"));
	//}
	//HWND  hw = ::FindWindow(NULL,_T("Shell"));
	//::SetWindowPos(hw, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);




}
