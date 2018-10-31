
// DirectionDetectView.h : CDirectionDetectView 类的接口
//

#pragma once

class  CIni;

class CDirectionDetectView : public CView
{
protected: // 仅从序列化创建
	CDirectionDetectView();
	DECLARE_DYNCREATE(CDirectionDetectView)
// 操作
public:
	void setHaloconWindRect();
private:

// 特性
public:
	CDirectionDetectDoc* GetDocument() const;
	UINT_PTR m_lTimer;												//初始化窗口界面计时器ID（等待窗口创建完成）
	LONG64 m_hMainViewWindowID;							//主界面halcon window ID
	CRect m_rect;
	CIni *m_pIni;
private:
	HANDLE m_handle;//拍照线程句柄

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图

	//改变halcon 界面视图大小
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//延时后初始化界面相关
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	
// 实现
public:
	virtual ~CDirectionDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnEnableStartButtom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnableStopButtom(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public://菜单栏、工具栏事件响应函数
	//开始检测
	afx_msg void OnCmdStart();
	//停止检测
	afx_msg void OnCmdStop();
	//打开学习对话框
	afx_msg void OnEditStudy();
	//打开一张图片
	afx_msg void OnFileOpen();
	//保存一张图片
	afx_msg void OnFileSave();
};

#ifndef _DEBUG  // DirectionDetectView.cpp 中的调试版本
inline CDirectionDetectDoc* CDirectionDetectView::GetDocument() const
   { return reinterpret_cast<CDirectionDetectDoc*>(m_pDocument); }
#endif

