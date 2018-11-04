
// DirectionDetectView.cpp : CDirectionDetectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DirectionDetect.h"
#endif

#include "DirectionDetectDoc.h"
#include "DirectionDetectView.h"
#include "StudyDlg1.h"
#include "MfcHalcon.h"
#include "logger\StaticLogger.h"
#include "MainFrm.h"
#include "Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern CStaticLogger g_logger;
IMPLEMENT_DYNCREATE(CDirectionDetectView, CView)


// CDirectionDetectView 消息处理程序
WorkThreadFunParameters g_WorkThreadFunParameter;



BEGIN_MESSAGE_MAP(CDirectionDetectView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_MESSAGE(ID_USER_MSG_THREAD_EXIT, &CDirectionDetectView::OnEnableStartButtom)
	ON_MESSAGE(ID_USER_MSG_THREAD_initialed, &CDirectionDetectView::OnEnableStopButtom)
	ON_MESSAGE(ID_USER_MSG_ADD_thistimeYeild, &CDirectionDetectView::OnAddThistimeYeildAtDoc)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//ON_UPDATE_COMMAND_UI(ID_CMD_START, &CDirectionDetectView::OnUpdateCmdStart)
	//ON_UPDATE_COMMAND_UI(ID_CMD_STOP, &CDirectionDetectView::OnUpdateCmdStop)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_STUDY, &CDirectionDetectView::OnUpdateEditStudy)
	//ON_UPDATE_COMMAND_UI(ID_APP_EXIT, &CDirectionDetectView::OnUpdateAppExit)
	ON_COMMAND(ID_CMD_START, &CDirectionDetectView::OnCmdStart)
	ON_COMMAND(ID_CMD_STOP, &CDirectionDetectView::OnCmdStop)
	ON_COMMAND(ID_EDIT_STUDY, &CDirectionDetectView::OnEditStudy)
	ON_COMMAND(ID_PIC_OPEN, &CDirectionDetectView::OnFileOpen)
	ON_COMMAND(ID_PIC_SAVE, &CDirectionDetectView::OnFileSave)
END_MESSAGE_MAP()

// CDirectionDetectView 构造/析构

CDirectionDetectView::CDirectionDetectView()
{
	// TODO: 在此处添加构造代码
	m_hMainViewWindowID = 0;

	m_pIni = new CIni(_T(".\\bulletPhotograp.ini"));
	//int a = m_pIni->WriteInt(_T("Camera Configuration"), _T("ImageHeight"),1);
	//a = m_pIni->WriteInt(_T("Camera Configuration"), _T("LineRate"), 2);
	//a = m_pIni->WriteInt(_T("Camera Configuration"), _T("ExposureTime"), 3);
}

CDirectionDetectView::~CDirectionDetectView()
{
}

BOOL CDirectionDetectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CDirectionDetectView 绘制

void CDirectionDetectView::OnDraw(CDC* /*pDC*/)
{
	CDirectionDetectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDirectionDetectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDirectionDetectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDirectionDetectView 诊断

#ifdef _DEBUG
void CDirectionDetectView::AssertValid() const
{
	CView::AssertValid();
}

void CDirectionDetectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDirectionDetectDoc* CDirectionDetectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirectionDetectDoc)));
	return (CDirectionDetectDoc*)m_pDocument;
}
#endif //_DEBUG




LRESULT  CDirectionDetectView::OnEnableStartButtom(WPARAM wParam, LPARAM lParam)
{
	((CMainFrame*)::AfxGetMainWnd())->enableMenu(4, ID_CMD_START, ID_APP_EXIT, ID_FILE_OPEN, ID_EDIT_STUDY);
	return 0;
}
LRESULT  CDirectionDetectView::OnEnableStopButtom(WPARAM wParam, LPARAM lParam)
{
	((CMainFrame*)::AfxGetMainWnd())->enableMenu(1, ID_CMD_STOP);
	return 0;
}
LRESULT CDirectionDetectView::OnAddThistimeYeildAtDoc(WPARAM wParam, LPARAM lParam)
{
	GetDocument()->addThisTimeYield(g_WorkThreadFunParameter.m_iJiYuType-1);
	return 0;
}




void CDirectionDetectView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//初始化住view界面  halcon窗口
	setHaloconWindRect();
	m_hMainViewWindowID = MFC_HALCON::MH_OpenWindow(m_hWnd, m_rect);

	KillTimer(m_lTimer);
	CView::OnTimer(nIDEvent);
}


void CDirectionDetectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	//更改halcon窗口大小
	if (0 != m_hMainViewWindowID)
	{
		//HalconCpp::CloseWindow(m_hMainViewWindowID);
		//m_hMainViewWindowID = MFC_HALCON::MH_OpenWindow(m_hWnd, m_rect);
		setHaloconWindRect();
		HalconCpp::SetWindowExtents(m_hMainViewWindowID, m_rect.top, m_rect.left, m_rect.Width(), m_rect.Height());
	}
}


void CDirectionDetectView::setHaloconWindRect()
{
	GetClientRect(m_rect);
	m_rect.top += 7;
	m_rect.left += 7;
	m_rect.right = m_rect.right -7;
	m_rect.bottom = m_rect.bottom-7;
}





void CDirectionDetectView::OnCmdStart()
{
	/*
	获取挤盂型号
	控件禁用
	初始化
	读取配置文件
	创建工作线程
	工作线程退出
	控件启用
	*/
	//((CMainFrame*)::AfxGetMainWnd())->enableMenu(1, ID_CMD_STOP);
	
	g_WorkThreadFunParameter.m_iJiYuType = ((CMainFrame*)AfxGetMainWnd())->m_pDlg_1FormView->getSelectJIYUNum();
	if (0 == g_WorkThreadFunParameter.m_iJiYuType)return;
	((CMainFrame*)::AfxGetMainWnd())->disableMenu(4, ID_CMD_START, ID_APP_EXIT, ID_FILE_OPEN, ID_EDIT_STUDY);
	g_WorkThreadFunParameter.m_hMainWnd = m_hWnd;
	g_WorkThreadFunParameter.m_lStopSignal = 0;
	g_WorkThreadFunParameter.m_lIsSaveImage = 0;
	g_WorkThreadFunParameter.m_szPath.Empty();
	g_WorkThreadFunParameter.m_szPath = m_pIni->GetString(_T("ImageProcess Configuration"), _T("ImageSavaPath"));
	g_WorkThreadFunParameter.m_iImageHeight = m_pIni->GetInt(_T("Camera Configuration"), _T("ImageHeight"));
	g_WorkThreadFunParameter.m_iLineRate = m_pIni->GetInt(_T("Camera Configuration"), _T("LineRate"));
	g_WorkThreadFunParameter.m_iExposureTime = m_pIni->GetInt(_T("Camera Configuration"), _T("ExposureTime"));
	g_WorkThreadFunParameter.m_lHalconWindId = m_hMainViewWindowID;



	m_handle = (HANDLE)_beginthreadex(NULL, 0, gWorkThreadFun, &g_WorkThreadFunParameter, 0, NULL);
	return;
}


void CDirectionDetectView::OnCmdStop()
{
	//if (WAIT_OBJECT_0 != WaitForSingleObject(m_handle, INFINITE))
	//{
	//	AfxMessageBox(_T("拍照线程退出错误！"));
	//	return;
	//}//此方法阻塞主线程，拍照线程界面操作时存在资源竞争，halcon报错。

	//((CMainFrame*)::AfxGetMainWnd())->enableMenu(4, ID_CMD_START, ID_APP_EXIT, ID_FILE_OPEN, ID_EDIT_STUDY);
	((CMainFrame*)::AfxGetMainWnd())->disableMenu(1, ID_CMD_STOP);

	if (0 == g_WorkThreadFunParameter.m_lStopSignal)
		InterlockedIncrement((LPLONG)&g_WorkThreadFunParameter.m_lStopSignal);

	//恢复类型选择复选框为未选中
	((CMainFrame*)AfxGetMainWnd())->m_pDlg_1FormView->resetSelectJIYUNum();
}



void CDirectionDetectView::OnEditStudy()
{
	// TODO: 在此添加命令处理程序代码
	CStudyDlg1 studyDlg(m_pIni);

	studyDlg.DoModal();
}




void CDirectionDetectView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
}


void CDirectionDetectView::OnFileSave()
{
	if (0 == g_WorkThreadFunParameter.m_lIsSaveImage)
		InterlockedIncrement((LPLONG)&g_WorkThreadFunParameter.m_lIsSaveImage);
}


