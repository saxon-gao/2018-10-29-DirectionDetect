// StudyDlgTabPage3.cpp : 实现文件
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlgTabPage3.h"
#include "afxdialogex.h"
#include "Ini.h"

// CStudyDlgTabPage3 对话框

IMPLEMENT_DYNAMIC(CStudyDlgTabPage3, CDialogEx)

CStudyDlgTabPage3::CStudyDlgTabPage3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY1_P3, pParent)
	, m_szImageSavePath(_T(""))
{

}

CStudyDlgTabPage3::~CStudyDlgTabPage3()
{
}

void CStudyDlgTabPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szImageSavePath);
}


BEGIN_MESSAGE_MAP(CStudyDlgTabPage3, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_IMAGE_PATH, &CStudyDlgTabPage3::OnBnClickedSaveImagePath)
END_MESSAGE_MAP()


void CStudyDlgTabPage3::updateMember(void*p) {
	if (NULL == p)
		AfxMessageBox(_T("page0 p_CIni==0!"));
	CIni * pCini = (CIni *)p;
	m_szImageSavePath = pCini->GetString(_T("ImageProcess Configuration"), _T("ImageSavaPath"));
	UpdateData(FALSE);
}




// CStudyDlgTabPage3 消息处理程序


void CStudyDlgTabPage3::OnBnClickedSaveImagePath()
{
	//CFileDialog 不能选择文件夹路径
	CFolderPickerDialog fd(NULL, 0, this, 0);

	if (fd.DoModal() == IDOK)
	{
		m_szImageSavePath = fd.GetPathName();
		UpdateData(FALSE);
	}

}
