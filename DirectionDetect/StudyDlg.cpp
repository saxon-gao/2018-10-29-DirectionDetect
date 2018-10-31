// StudyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlg.h"
#include "afxdialogex.h"
#include "MfcHalcon.h"

// CStudyDlg �Ի���

IMPLEMENT_DYNAMIC(CStudyDlg, CDialogEx)

CStudyDlg::CStudyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY, pParent)
{

}

CStudyDlg::~CStudyDlg()
{
}

void CStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStudyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN_PIC, &CStudyDlg::OnClickedOpenPic)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CStudyDlg ��Ϣ��������

BOOL CStudyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	//ShowWindow(SW_MAXIMIZE);//�Ի���Ĭ����󻯵���


	//��ʼ��halcon����
	CRect rect;
	GetClientRect(&rect);
	rect.right = rect.right*6/10;
	rect.bottom = rect.bottom - 120;
	m_hStudyDlgWindowID =  MFC_HALCON::MH_OpenWindow(m_hWnd, rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CStudyDlg::OnClickedOpenPic()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CString m_path;
	CFileDialog hFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY,
		TEXT("֧�ֵ�ͼ���ļ� (*.jpg;*.gif;*.bmp;...)|*.jpg;*.gif;*.bmp|ר��Tiffͼ���ļ�(*.tiff;*.tif)|*.tiff;*.tif|�����ļ�(*.*)|*.*||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 1;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("��ͼ���ļ�...\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;
	if (hFileDlg.DoModal() == IDOK)
	{
		m_path = hFileDlg.GetPathName();
		HObject Image;
		CRect rect;
		MFC_HALCON::MH_ReadImage(m_path, Image);
		MFC_HALCON::MH_DispImage(Image, m_hStudyDlgWindowID);
	}
}




void CStudyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴�������Ϣ�����������
}


void CStudyDlg::OnOK()
{
	// TODO: �ڴ�����ר�ô����/����û���

	CDialogEx::OnOK();
}