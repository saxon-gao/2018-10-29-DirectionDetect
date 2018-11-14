// StudyDlgTabPage1.cpp : 实现文件
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "StudyDlgTabPage1.h"
#include "afxdialogex.h"
#include "LSerialPort.h"

// CStudyDlgTabPage1 对话框

IMPLEMENT_DYNAMIC(CStudyDlgTabPage1, CDialogEx)

CStudyDlgTabPage1::CStudyDlgTabPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY1_P1, pParent)
	, m_iLightIntensity(0)
	, m_szComRet(_T(""))
{
	//初始化锐视光源调节串口
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


// CStudyDlgTabPage1 消息处理程序


BOOL CStudyDlgTabPage1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	mSliderCtrl.SetRange(0, 255);//设置滑动范围为1到20
	mSliderCtrl.SetTicFreq(1);//每1个单位画一刻度
	//mSliderCtrl.SetPos(10);//设置滑块初始位置为1 



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CStudyDlgTabPage1::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	//m_int 即为当前滑块的值。
	m_iLightIntensity = pSlidCtrl->GetPos();//取得当前位置值  
	
	//打包发送
	char chSendData[20] = {0};
	sprintf(chSendData, "SC%04d#", m_iLightIntensity);
	m_pSerialPort->WriteData((byte*)chSendData, 20);

	//等待返回
	char cRecved[20] = { 0 };
	m_szComRet.Empty();
	if (-1 == m_pSerialPort->readString(cRecved))
		m_szComRet = "光源控制器串口无响应";
	else
		m_szComRet = cRecved;

	UpdateData(FALSE);
	*pResult = 0;
}


void CStudyDlgTabPage1::OnBnClickedButtonLightOn()
{
	// TODO: 在此添加控件通知处理程序代码
	char chSendData[20] = { 0 };
	sprintf(chSendData, "SH#");
	m_pSerialPort->WriteData((byte*)chSendData, 20);

	char cRecved[20] = { 0 };
	m_szComRet.Empty();
	if (-1 == m_pSerialPort->readString(cRecved))
		m_szComRet = "光源控制器串口无响应";
	else
		m_szComRet = cRecved;

	UpdateData(FALSE);
}


void CStudyDlgTabPage1::OnBnClickedButtonLightOff()
{
	// TODO: 在此添加控件通知处理程序代码
	char chSendData[20] = { 0 };
	sprintf(chSendData, "SL#");
	m_pSerialPort->WriteData((byte*)chSendData, 20);

	char cRecved[20] = { 0 };
	m_szComRet.Empty();
	if (-1 == m_pSerialPort->readString(cRecved))
		m_szComRet = "光源控制器串口无响应";
	else
		m_szComRet = cRecved;

	UpdateData(FALSE);
}
