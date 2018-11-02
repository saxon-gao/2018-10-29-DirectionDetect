
// DirectionDetectDoc.cpp : CDirectionDetectDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DirectionDetect.h"
#endif

#include "DirectionDetectDoc.h"
#include "CppToMysql.h"
#include <propkey.h>
#include "logger\StaticLogger.h"
// 唯一的一个 日志 对象
CStaticLogger g_logger;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDirectionDetectDoc

IMPLEMENT_DYNCREATE(CDirectionDetectDoc, CDocument)

BEGIN_MESSAGE_MAP(CDirectionDetectDoc, CDocument)
END_MESSAGE_MAP()


// CDirectionDetectDoc 构造/析构

CDirectionDetectDoc::CDirectionDetectDoc()
{
	// TODO: 在此添加一次性构造代码

	//初始化日志系统
	LPCTSTR lf = NULL;
	ILogger::LogLevel ll = ILogger::DEFAULT_LOG_LEVEL;
	int pf = ILogger::PRINT_FLAG_FILE;
	if (g_logger->Init(lf, ll, pf))
	{
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("-------====-------"));
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("日志系统初始化完成"));
	}
	else
	{
		AfxMessageBox(_T("日志系统初始化错误"));
	}


	//连接数据库
	char* host = "127.0.0.1";
	char* user = "root";
	char* port = "3306";
	char* passwd = "123456";
	char* dbname = "ji_yu_db";
	char* charset = "GBK";//支持中文
	char *Msg  = NULL;//消息变量
	m_pCppToMysql = new CCppToMysql;
	if (m_pCppToMysql->ConnMySQL(host, port, dbname, user, passwd, charset, &Msg) != 0)
	{
		CString sztmp(Msg);
		AfxMessageBox(sztmp);
		g_logger->Log(ILogger::LogLevel::LL_ERROR, sztmp);
	}
	else {
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("mysql connect success"));
	}

	//读取数据库数据
	CString szdate = _T("2019-09-11");
	initYieldDataFromMysql(szdate);

}

CDirectionDetectDoc::~CDirectionDetectDoc()
{
	//更新数据库数据
	//UpdateYieldDataToMysql();

	//关闭数据库连接
	m_pCppToMysql->CloseMySQLConn();
	m_pCppToMysql->~CCppToMysql();
	m_pCppToMysql = NULL;
	g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("mysql closeConnect success"));
	
	//关闭日志系统
	g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("------------------"));
	Sleep(100);
	g_logger->UnInit();
}


BOOL CDirectionDetectDoc::initYieldDataFromMysql(CString szdate)
{
	PTCHAR sss = szdate.GetBuffer();
	char chdate[20];
	int n = szdate.GetLength(); //按字符计算，str的长度
	int len = WideCharToMultiByte(CP_ACP, 0, szdate, n, NULL, 0, NULL, NULL);//按Byte计算str长度
	//
	WideCharToMultiByte(CP_ACP, 0, szdate, n, chdate, len, NULL, NULL);//宽字节转换为多字节编码
	chdate[len] = '\0';//不要忽略末尾结束标志

	char mysqlCommand[100] = { 0 };
	sprintf(mysqlCommand, "select * from tb1 where date = '%s'", chdate);

	char *Msg = NULL;//消息变量
	std::string str = m_pCppToMysql->SelectData(mysqlCommand, 3, &Msg);
	const char*p = str.data();
	//解包
	int i=0;

	while (str.find(0x5, i)!=-1)
	{
		int indexDate = str.find(0x6, i);
		std::string subDate = str.substr(i, indexDate-i);
		const char *p1 = subDate.data();
		//m_ThisDayYieldData[0].sz_date = subDate.data();

		indexDate += 1;
		int indexType = str.find(0x6, indexDate);
		std::string subType = str.substr(indexDate, indexType - indexDate);
		const char *p2 = subType.data();
		int nType = atoi(subType.data());
		//m_ThisDayYieldData[nType-1].n_type = nType;

		indexType += 1;
		int indexDateYield = str.find(0x6, indexType);
		std::string subDateYield = str.substr(indexType, indexDateYield - indexType);
		const char *p3 = subDateYield.data();
		m_ThisDayYieldData[nType-1].n_dateYield = atoi(subDateYield.data());

		i = indexDateYield + 2;
	}

	for (int j = 0; j < 4; j++)//初始化日期栏
	{
		m_ThisDayYieldData[j].sz_date = szdate;
		m_ThisDayYieldData[j].n_type = j + 1;
	}

	return 0;
}

BOOL CDirectionDetectDoc::UpdateYieldDataToMysql(char *cmd)
{
	return 0;
}

BOOL CDirectionDetectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


// CDirectionDetectDoc 序列化

void CDirectionDetectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDirectionDetectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDirectionDetectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDirectionDetectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDirectionDetectDoc 诊断

#ifdef _DEBUG
void CDirectionDetectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDirectionDetectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDirectionDetectDoc 命令
