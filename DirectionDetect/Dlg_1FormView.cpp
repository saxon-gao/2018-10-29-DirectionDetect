// Dlg_1FormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "Dlg_1FormView.h"


// CDlg_1FormView

IMPLEMENT_DYNCREATE(CDlg_1FormView, CFormView)

CDlg_1FormView::CDlg_1FormView()
	: CFormView(IDD_FORM_VIEW_DLG_1)
{

}

CDlg_1FormView::~CDlg_1FormView()
{
}

void CDlg_1FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg_1FormView, CFormView)
END_MESSAGE_MAP()


// CDlg_1FormView ���

#ifdef _DEBUG
void CDlg_1FormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlg_1FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

int CDlg_1FormView::getSelectJIYUNum()
{
	int  a = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO4);
	switch (a) 
	{
	case IDC_RADIO1:
		a = 1;
		break;
	case IDC_RADIO2:
		a = 2;
		break;
	case IDC_RADIO3:
		a = 3;
		break;
	case IDC_RADIO4:
		a = 4;
		break;
	default:
		AfxMessageBox(_T("����ѡ�������ͣ�"), MB_OK);
		a = 0;
	}
	return a;
}


void CDlg_1FormView::resetSelectJIYUNum()
{
	CButton* radio = (CButton*)GetDlgItem(IDC_RADIO1);
	radio->SetCheck(BST_UNCHECKED);
	radio = (CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(BST_UNCHECKED);
	radio = (CButton*)GetDlgItem(IDC_RADIO3);
	radio->SetCheck(BST_UNCHECKED);
	radio = (CButton*)GetDlgItem(IDC_RADIO4);
	radio->SetCheck(BST_UNCHECKED);
}


// CDlg_1FormView ��Ϣ�������
