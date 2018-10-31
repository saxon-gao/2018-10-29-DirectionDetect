
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "DirectionDetect.h"
#include "MainFrm.h"
#include "logger\StaticLogger.h"
extern CStaticLogger g_logger;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_UPDATE_COMMAND_UI(ID_CMD_START, &CMainFrame::OnUpdateCmdStart)
	ON_UPDATE_COMMAND_UI(ID_CMD_STOP, &CMainFrame::OnUpdateCmdStop)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STUDY, &CMainFrame::OnUpdateEditStudy)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, &CMainFrame::OnUpdateAppExit)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CMainFrame::OnUpdateFileOpen)
	ON_WM_SIZE()
	ON_COMMAND(ID_CMD_START, &CMainFrame::OnCmdStart)
	ON_COMMAND(ID_CMD_STOP, &CMainFrame::OnCmdStop)
	ON_COMMAND(ID_EDIT_STUDY, &CMainFrame::OnEditStudy)
	ON_COMMAND(ID_PIC_OPEN, &CMainFrame::OnPicOpen)
	ON_COMMAND(ID_PIC_SAVE, &CMainFrame::OnPicSave)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	//for (int i = 0; i < 50; i++) {
	//	m_MenuUiStatusMap[i] = 0;
	//}
	////enableMenu(3, 0, 2, 8);
	//enableMenu(2, 0, 2);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	
	if (!m_wndMenuBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_MAINFRAME))//
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) 
		|| !m_wndToolBar.LoadToolBar(/*theApp.m_bHiColorIcons ?*/ IDR_MAINFRAME_256 /*: IDR_MAINFRAME*/))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	ID_FILE_OPEN;

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作: 
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	//初始化需要禁用启用的菜单项添加入map，启用1 禁用0  
	m_MenuUiStatusMap[ID_CMD_START] = 1;
	m_MenuUiStatusMap[ID_CMD_STOP] = 0;
	m_MenuUiStatusMap[ID_APP_EXIT] = 1;
	m_MenuUiStatusMap[ID_FILE_OPEN] = 1;
	m_MenuUiStatusMap[ID_EDIT_STUDY] = 1;
	
	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	//此处报错
	//if (CMFCToolBar::GetUserImages() == NULL)
	//{
	//	// 加载用户定义的工具栏图像
	//	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
	//	{
	//		CMFCToolBar::SetUserImages(&m_UserImages);
	//	}
	//}

	//隐藏下面断取消菜单栏折叠
	//// 启用菜单个性化(最近使用的命令)
	//// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	//CList<UINT, UINT> lstBasicCommands;

	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	//CMFCToolBar::SetBasicCommands(lstBasicCommands);


	//设置标题栏and 任务栏 图标
	HICON m_hIcon = AfxGetApp()->LoadIcon(ID_MAIN_ICON);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//更改标题栏字符串
	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = _T("FIVISION");
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}




void CMainFrame::enableMenu(unsigned int prametersNum, ...) {
	va_list args;
	va_start(args, prametersNum);
	while (prametersNum>0)
	{
		//通过va_arg(args,int)依次获取参数的值
		m_MenuUiStatusMap[va_arg(args, int)] = 1;
		prametersNum--;
	}
	va_end(args);
	return;
}
void CMainFrame::disableMenu(unsigned int prametersNum, ...) {
	va_list args;
	va_start(args, prametersNum);
	while (prametersNum>0)
	{
		//通过va_arg(args,int)依次获取参数的值
		m_MenuUiStatusMap[va_arg(args, int)] = 0;
		prametersNum--;
	}
	va_end(args);
	return;
}
void CMainFrame::changeMenuUiStatus(CCmdUI *pCmdUI, unsigned int menuIndex) {
#ifdef IS_DISABLE_MENU
	if (0 == m_MenuUiStatusMap[menuIndex]) {
		pCmdUI->Enable(0);
		//g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("禁用--%d"), pCmdUI->m_nIndex);
	}
	else if (1 == m_MenuUiStatusMap[menuIndex])
	{
		pCmdUI->Enable(1);
		//g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("启用==%d"), pCmdUI->m_nIndex);
	}
#endif 
}


void CMainFrame::OnUpdateCmdStart(CCmdUI *pCmdUI)
{
	changeMenuUiStatus(pCmdUI, pCmdUI->m_nID);
}


void CMainFrame::OnUpdateCmdStop(CCmdUI *pCmdUI)
{
	changeMenuUiStatus(pCmdUI, pCmdUI->m_nID);
}


void CMainFrame::OnUpdateAppExit(CCmdUI *pCmdUI)
{
	changeMenuUiStatus(pCmdUI, pCmdUI->m_nID);
}


void CMainFrame::OnUpdateEditStudy(CCmdUI *pCmdUI)
{
	changeMenuUiStatus(pCmdUI, pCmdUI->m_nID);
}


void CMainFrame::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	changeMenuUiStatus(pCmdUI, pCmdUI->m_nID);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect);
	int nwidth(rect.right);
	int nheight(rect.bottom);	//获取客户区窗口大小

	if (!m_splitwnd.CreateStatic(this, 1, 2))	//窗口分割
	{
		MessageBox(_T("分割窗口错误"), _T("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	//关联相关的View类
	m_splitwnd.CreateView(0, 0, RUNTIME_CLASS(CDirectionDetectView), CSize(/*nwidth / 10 * 7, nheight*/0,0), pContext);
	m_pDirectionDetectView = (CDirectionDetectView*)m_splitwnd.GetPane(0, 0);

	//对子窗口进行在分割
	if (!m_rigetSubSplitwnd.CreateStatic(&m_splitwnd, 2, 1, WS_VISIBLE | WS_CHILD, m_splitwnd.IdFromRowCol(0, 1)))
	{
		MessageBox(_T("子窗口分割窗口错误"), _T("Error"), MB_OK | MB_ICONERROR);
		return false;
	}
	//关联相关的View类
	m_rigetSubSplitwnd.CreateView(0, 0, RUNTIME_CLASS(CDlg_1FormView), CSize(/*nwidth / 10 * 7, nheight*/0, 0), pContext);
	m_pDlg_1FormView = (CDlg_1FormView*)m_rigetSubSplitwnd.GetPane(0, 0);

	m_rigetSubSplitwnd.CreateView(1, 0, RUNTIME_CLASS(CDlg_2FormView), CSize(/*nwidth / 10 * 7, nheight*/0, 0), pContext);
	m_pDlg_2FormView = (CDlg_2FormView*)m_rigetSubSplitwnd.GetPane(1, 0);

	m_splitwnd.SetActivePane(0, 0);

	return true;
	//return CFrameWndEx::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//调整主框架下各子窗口的比例
	if (::IsWindow(m_rigetSubSplitwnd))
	{
		CRect m_rect;
		GetClientRect(&m_rect);
		m_splitwnd.SetColumnInfo(0, m_rect.Width() / 10 * 7, 10);
		m_splitwnd.RecalcLayout();//Call to redisplay the splitter window after adjusting row or column size.
		//m_pDirectionDetectView->MoveWindow(m_rect);//无需调用调整，自动发送onsize消息给各子视图类

		m_rigetSubSplitwnd.SetRowInfo(0, m_rect.Height() / 10*3, 10);
		m_rigetSubSplitwnd.SetRowInfo(1, m_rect.Height() / 10*7, 10);
		m_rigetSubSplitwnd.RecalcLayout();
	}
}


void CMainFrame::OnCmdStart()
{
	// TODO: 在此添加命令处理程序代码
	m_pDirectionDetectView->OnCmdStart();
}


void CMainFrame::OnCmdStop()
{
	// TODO: 在此添加命令处理程序代码
	m_pDirectionDetectView->OnCmdStop();
}


void CMainFrame::OnEditStudy()
{
	// TODO: 在此添加命令处理程序代码
	m_pDirectionDetectView->OnEditStudy();
}


void CMainFrame::OnPicOpen()
{
	// TODO: 在此添加命令处理程序代码
	m_pDirectionDetectView->OnFileOpen();
}


void CMainFrame::OnPicSave()
{
	// TODO: 在此添加命令处理程序代码
	m_pDirectionDetectView->OnFileSave();
}
