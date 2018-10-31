#pragma once



// CDlg_1FormView 窗体视图

class CDlg_1FormView : public CFormView
{
	DECLARE_DYNCREATE(CDlg_1FormView)

protected:
	CDlg_1FormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlg_1FormView();

public:
	int getSelectJIYUNum();


public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_VIEW_DLG_1 };
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
};


