// StudyDlgTabPage0.cpp : 实现文件
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlgTabPage0.h"
#include "afxdialogex.h"
#include "Ini.h"

// CStudyDlgTabPage0 对话框

IMPLEMENT_DYNAMIC(CStudyDlgTabPage0, CDialogEx)

CStudyDlgTabPage0::CStudyDlgTabPage0(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY1_P0, pParent)
	, m_iImgeWidth(0)
	, m_iLineRate(0)
	, m_iExposureTime(0)
{

}

CStudyDlgTabPage0::~CStudyDlgTabPage0()
{
}

void CStudyDlgTabPage0::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_CameraAcquisitionMode);
	DDX_Text(pDX, IDC_IMAGE_WIDTH, m_iImgeWidth);
	DDX_Text(pDX, IDC_LINE_RATE, m_iLineRate);
	DDX_Text(pDX, IDC_EXPOSURE_TIME, m_iExposureTime);
}


BEGIN_MESSAGE_MAP(CStudyDlgTabPage0, CDialogEx)
END_MESSAGE_MAP()


void CStudyDlgTabPage0::updateMember(void*p) {
	if (NULL == p)
		AfxMessageBox(_T("page0 p_CIni==0!"));
	CIni * pCini = (CIni *)p;
	m_iImgeWidth = pCini->GetInt(_T("Camera Configuration"), _T("ImageHeight"));
	m_iLineRate = pCini->GetInt(_T("Camera Configuration"), _T("LineRate"));
	m_iExposureTime = pCini->GetInt(_T("Camera Configuration"), _T("ExposureTime"));
	UpdateData(FALSE);
}



// CStudyDlgTabPage0 消息处理程序




BOOL CStudyDlgTabPage0::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CameraAcquisitionMode.AddString(_T("同步采集"));
	m_CameraAcquisitionMode.AddString(_T("异步采集"));
	m_CameraAcquisitionMode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
