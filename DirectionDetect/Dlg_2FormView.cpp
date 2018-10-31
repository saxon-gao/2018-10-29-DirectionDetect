// Dlg_2FormView.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "Dlg_2FormView.h"


// CDlg_2FormView

IMPLEMENT_DYNCREATE(CDlg_2FormView, CFormView)

CDlg_2FormView::CDlg_2FormView()
	: CFormView(IDD_FORM_VIEW_DLG_2)
{

}

CDlg_2FormView::~CDlg_2FormView()
{
}

void CDlg_2FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_statisticListCtrl);
}

BEGIN_MESSAGE_MAP(CDlg_2FormView, CFormView)
END_MESSAGE_MAP()


// CDlg_2FormView 诊断

#ifdef _DEBUG
void CDlg_2FormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlg_2FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlg_2FormView 消息处理程序


void CDlg_2FormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化表格数据
	DWORD dwStyle = m_statisticListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_statisticListCtrl.SetExtendedStyle(dwStyle);
	m_statisticListCtrl.InsertColumn(0, _T("日期"), LVCFMT_CENTER,80);
	m_statisticListCtrl.InsertColumn(1, _T("类型"), LVCFMT_CENTER, 60);
	m_statisticListCtrl.InsertColumn(2, _T("当日检测量"), LVCFMT_CENTER, 80);
	m_statisticListCtrl.InsertColumn(3, _T("本次开机检测量"), LVCFMT_CENTER, 100);
	//m_statisticListCtrl.InsertColumn(4, _T("向下数量"), LVCFMT_CENTER, 60);
	


	
}
