#pragma once
#include "afxcmn.h"



// CDlg_2FormView 窗体视图

class CDlg_2FormView : public CFormView
{
	DECLARE_DYNCREATE(CDlg_2FormView)

protected:
	CDlg_2FormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlg_2FormView();

public:
	CListCtrl m_statisticListCtrl;// 统计每日检测数据显示表
	CListCtrl m_statisticListCtrlHistory;// 统计历史检测数据显示表

public:
	void updateStatisticListCtrl();


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
};


