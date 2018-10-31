#pragma once
//3.配置halcon12
//(1)项目 - 属性 - 配置属性 - 链接器 - 输入 - 附加依赖项添加如下：
//halconcpp.lib
//(2)项目 - 属性 - 配置属性 - VC++目录 - 包含目录添加如下：
//D : \software\halcon12\include;
//D:\software\halcon12\include\halconcpp;
//(3)项目 - 属性 - 配置属性 - VC++目录 - 库目录添加如下：
//D : \software\halcon12\lib\x64 - win64
//	(4)项目 - 属性 - 配置属性 - 配置管理器，将项目平台改为x64。
//	(5)源文件中添加如下：
//
//#include "Halconcpp.h"
//	using namespace HalconCpp;


//办公室电脑halcon路径  D:\program\halcon
//个人电脑halcon路径		F:\program files\HALCON


#include "Halconcpp.h"
using namespace HalconCpp;


BOOL halcon_test(void *p = NULL);								//全局测试函数


struct WorkThreadFunParameters {
	int m_iJiYuType = 0;//挤盂类型标记，工作线程通过此标记调用不同处理函数
	HWND m_hMainWnd = 0;//halcon窗口句柄
	volatile long m_lStopSignal = 0;//停止标记   1时图像工作线程停止循环
	volatile long m_lIsSaveImage = 0;//是否保存图片标记  1时保存图片
	CString m_szPath;//图片保存路径
	//HANDLE m_hIsSaveIamge=0;//主线程 、拍照线程保存图片功能 同步信号
	//int m_iDelayTime = 0;//延迟时间ms（不添加演示海康相机 halcon 抓取长时间图像报错） 也可用try 解决

	LONG64 m_lHalconWindId = 0;//halcon 窗口ID
	int m_iImageHeight = 0;//相机图像高度（单张图片获取图像行数）
	int m_iLineRate = 0;//每秒行数
	int m_iExposureTime = 0;//曝光时间ms


};


//检测挤盂方向
unsigned int __stdcall gWorkThreadFun(PVOID pM);



namespace MFC_HALCON
{
//打开一个halcon窗口   参数：父窗口，在父窗口中的左上、右下位置
	LONG64 MH_OpenWindow(HWND h_wFather, CRect rect);	

//读取指定路径图像
	BOOL MH_ReadImage(CString szpath, HObject &Image);

//保存图像到指定路径
	BOOL MH_WriteImage(CString szpath, HObject &Image);

//显示HObject图像
	BOOL MH_DispImage(HObject &Image, HTuple wndId, CRect position =0);
};