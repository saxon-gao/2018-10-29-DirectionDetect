#pragma once



// CDlg_1FormView ������ͼ

class CDlg_1FormView : public CFormView
{
	DECLARE_DYNCREATE(CDlg_1FormView)

protected:
	CDlg_1FormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDlg_1FormView();

public:
	int getSelectJIYUNum();
	void resetSelectJIYUNum();

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


