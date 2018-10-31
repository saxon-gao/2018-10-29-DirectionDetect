
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include<map>//����ǰ������
//class CDlg_1FormView;
//class CDlg_2FormView;
//class CDirectionDetectView;
#include "DirectionDetectDoc.h"//��Ҫ�����View��ͷ�ļ������XXXdoc.h��View��xxxdoc.hҪ��xxxView.hǰ��
#include "Dlg_1FormView.h"
#include "Dlg_2FormView.h"
#include "DirectionDetectView.h"

class CMainFrame : public CFrameWndEx
{
// ����
public:
	void enableMenu(unsigned int prametersNum, ...);//ָ�����ò˵���
	void disableMenu(unsigned int prametersNum, ...);//ָ�����ò˵���
private:
	void changeMenuUiStatus(CCmdUI *pCmdUI, unsigned int menuIndex);

protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

private:
	//�˵�������������ť״̬���  ����1 ����0  
	//ͼ�±��Ӧ��ťID
	//�����ð�ť�±�����ǣ�CCmdUI->m_index ����ȫ׼ȷ
	std::map <long,bool>m_MenuUiStatusMap;


// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
	//���ĵ����ڷָ� https://blog.csdn.net/gxmirror_lee/article/details/65938187
	//							https://www.cnblogs.com/diysoul/p/5878291.html
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar; 
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	////װ�ع���������ԴͼƬ 
	//CImageList m_ImgList;
	////�����µĹ�����
	//CToolBar m_newToolBar;

public:
	//���ڷָ���
	CSplitterWnd m_splitwnd;
	CSplitterWnd m_rigetSubSplitwnd;
	//3���Ӵ�����ͼ��
	CDlg_1FormView *m_pDlg_1FormView;
	CDlg_2FormView *m_pDlg_2FormView;
	CDirectionDetectView *m_pDirectionDetectView;



// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	//����������¸��Ӵ��ڵı���
	afx_msg void OnSize(UINT nType, int cx, int cy);


	//ͨ����ť ״̬��׼�ı� �� ��״̬
	afx_msg void OnUpdateCmdStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCmdStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditStudy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	

	//����ڲ�ͬʱ��û�а�ť�������Ĵ��ڵ��°�ť���á��Ķ�mfc��Ϣ·����ء�
	//https://blog.csdn.net/rinuanlantian1/article/details/55047394
	//ִ���߼����������ΪCDirectionDetectViewʱ��ֱ�ӵ�����ش�������
	//�� ����ڡ�doc���޴�����ʱ��ͨ���˴�����CDirectionDetectView��������
	afx_msg void OnCmdStart();
	afx_msg void OnCmdStop();
	afx_msg void OnEditStudy();
	afx_msg void OnPicOpen();
	afx_msg void OnPicSave();
};


