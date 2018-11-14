// StudyDlgTabPage1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlgTabPage1.h"
#include "afxdialogex.h"
#include "LSerialPort.h"

// CStudyDlgTabPage1 �Ի���

IMPLEMENT_DYNAMIC(CStudyDlgTabPage1, CDialogEx)

CStudyDlgTabPage1::CStudyDlgTabPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY1_P1, pParent)
	, m_iLightIntensity(0)
	, m_szComRet(_T(""))
{
	//��ʼ�����ӹ�Դ���ڴ���
	m_pSerialPort = new CSerialPort();
	if (!m_pSerialPort->InitPort(1, CBR_19200))
	{
		AfxMessageBox(_T("initPort fail !"));
	}
	else
	{
		//AfxMessageBox(_T("initPort success !"));
	}
	//if (!m_pSerialPort->OpenListenThread())
	//{
	//	AfxMessageBox(_T("OpenListenThread fail !"));
	//}
	//else
	//{
	//	//AfxMessageBox(_T("OpenListenThread success !"));
	//}



}

CStudyDlgTabPage1::~CStudyDlgTabPage1()
{
	if (NULL != m_pSerialPort)
	{
		delete(m_pSerialPort);
		m_pSerialPort = NULL;
	}
}

void CStudyDlgTabPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, mSliderCtrl);
	DDX_Text(pDX, IDC_EDIT_LIGHT_INTENSITY, m_iLightIntensity);
	DDX_Text(pDX, IDC_EDIT_COM_RET, m_szComRet);
}


BEGIN_MESSAGE_MAP(CStudyDlgTabPage1, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CStudyDlgTabPage1::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_ON, &CStudyDlgTabPage1::OnBnClickedButtonLightOn)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_OFF, &CStudyDlgTabPage1::OnBnClickedButtonLightOff)
END_MESSAGE_MAP()


// CStudyDlgTabPage1 ��Ϣ�������


BOOL CStudyDlgTabPage1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	mSliderCtrl.SetRange(0, 255);//���û�����ΧΪ1��20
	mSliderCtrl.SetTicFreq(1);//ÿ1����λ��һ�̶�
	//mSliderCtrl.SetPos(10);//���û����ʼλ��Ϊ1 



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CStudyDlgTabPage1::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	//m_int ��Ϊ��ǰ�����ֵ��
	m_iLightIntensity = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ  
	
	//�������
	char chSendData[20] = {0};
	sprintf(chSendData, "SC%04d#", m_iLightIntensity);
	m_pSerialPort->WriteData((byte*)chSendData, 20);

	//�ȴ�����
	char cRecved[20] = { 0 };
	m_szComRet.Empty();
	if (-1 == m_pSerialPort->readString(cRecved))
		m_szComRet = "��Դ��������������Ӧ";
	else
		m_szComRet = cRecved;

	UpdateData(FALSE);
	*pResult = 0;
}


void CStudyDlgTabPage1::OnBnClickedButtonLightOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char chSendData[20] = { 0 };
	sprintf(chSendData, "SH#");
	m_pSerialPort->WriteData((byte*)chSendData, 20);

	char cRecved[20] = { 0 };
	m_szComRet.Empty();
	if (-1 == m_pSerialPort->readString(cRecved))
		m_szComRet = "��Դ��������������Ӧ";
	else
		m_szComRet = cRecved;

	UpdateData(FALSE);
}


void CStudyDlgTabPage1::OnBnClickedButtonLightOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char chSendData[20] = { 0 };
	sprintf(chSendData, "SL#");
	m_pSerialPort->WriteData((byte*)chSendData, 20);

	char cRecved[20] = { 0 };
	m_szComRet.Empty();
	if (-1 == m_pSerialPort->readString(cRecved))
		m_szComRet = "��Դ��������������Ӧ";
	else
		m_szComRet = cRecved;

	UpdateData(FALSE);
}
