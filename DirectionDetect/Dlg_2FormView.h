#pragma once
#include "afxcmn.h"



// CDlg_2FormView ������ͼ

class CDlg_2FormView : public CFormView
{
	DECLARE_DYNCREATE(CDlg_2FormView)

protected:
	CDlg_2FormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDlg_2FormView();

public:
	// ͳ��ÿ�ռ��������ʾ��
	CListCtrl m_statisticListCtrl;
	CListCtrl m_statisticListCtrlHistory;// ͳ����ʷ���������ʾ��


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_VIEW_DLG_2 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


