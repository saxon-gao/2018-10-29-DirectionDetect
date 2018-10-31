
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include<map>//不会前置申明
//class CDlg_1FormView;
//class CDlg_2FormView;
//class CDirectionDetectView;
#include "DirectionDetectDoc.h"//需要在相关View类头文件中添加XXXdoc.h，View类xxxdoc.h要在xxxView.h前面
#include "Dlg_1FormView.h"
#include "Dlg_2FormView.h"
#include "DirectionDetectView.h"

class CMainFrame : public CFrameWndEx
{
// 操作
public:
	void enableMenu(unsigned int prametersNum, ...);//指定启用菜单项
	void disableMenu(unsigned int prametersNum, ...);//指定禁用菜单项
private:
	void changeMenuUiStatus(CCmdUI *pCmdUI, unsigned int menuIndex);

protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

private:
	//菜单栏、工具栏按钮状态标记  启用1 禁用0  
	//图下标对应按钮ID
	//不能用按钮下标作标记，CCmdUI->m_index 不完全准确
	std::map <long,bool>m_MenuUiStatusMap;


// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
	//单文档窗口分割 https://blog.csdn.net/gxmirror_lee/article/details/65938187
	//							https://www.cnblogs.com/diysoul/p/5878291.html
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar; 
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	////装载工具栏上资源图片 
	//CImageList m_ImgList;
	////创建新的工具栏
	//CToolBar m_newToolBar;

public:
	//窗口分割器
	CSplitterWnd m_splitwnd;
	CSplitterWnd m_rigetSubSplitwnd;
	//3个子窗口视图类
	CDlg_1FormView *m_pDlg_1FormView;
	CDlg_2FormView *m_pDlg_2FormView;
	CDirectionDetectView *m_pDirectionDetectView;



// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	//调整主框架下各子窗口的比例
	afx_msg void OnSize(UINT nType, int cx, int cy);


	//通过按钮 状态标准改变 启 禁状态
	afx_msg void OnUpdateCmdStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCmdStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditStudy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	

	//活动窗口不同时，没有按钮处理函数的窗口导致按钮禁用。阅读mfc消息路由相关。
	//https://blog.csdn.net/rinuanlantian1/article/details/55047394
	//执行逻辑：当激活窗口为CDirectionDetectView时，直接调用相关处理函数；
	//当 激活窗口、doc都无处理函数时，通过此处调用CDirectionDetectView函数处理。
	afx_msg void OnCmdStart();
	afx_msg void OnCmdStop();
	afx_msg void OnEditStudy();
	afx_msg void OnPicOpen();
	afx_msg void OnPicSave();
};


