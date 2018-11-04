
// DirectionDetectDoc.cpp : CDirectionDetectDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DirectionDetect.h"
#endif

#include "DirectionDetectDoc.h"
#include "Dlg_2FormView.h"
#include "CppToMysql.h"
#include <propkey.h>
#include "logger\StaticLogger.h"
// Ψһ��һ�� ��־ ����
CStaticLogger g_logger;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDirectionDetectDoc

IMPLEMENT_DYNCREATE(CDirectionDetectDoc, CDocument)

BEGIN_MESSAGE_MAP(CDirectionDetectDoc, CDocument)
END_MESSAGE_MAP()


// CDirectionDetectDoc ����/����

CDirectionDetectDoc::CDirectionDetectDoc()
{
	// TODO: �ڴ����һ���Թ������

	//��ʼ����־ϵͳ
	LPCTSTR lf = NULL;
	ILogger::LogLevel ll = ILogger::DEFAULT_LOG_LEVEL;
	int pf = ILogger::PRINT_FLAG_FILE;
	if (g_logger->Init(lf, ll, pf))
	{
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("-------====-------"));
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("��־ϵͳ��ʼ�����"));
	}
	else
	{
		AfxMessageBox(_T("��־ϵͳ��ʼ������"));
	}


	//�������ݿ�
	char* host = "127.0.0.1";
	char* user = "root";
	char* port = "3306";
	char* passwd = "123456";
	char* dbname = "ji_yu_db";
	char* charset = "GBK";//֧������
	char *Msg  = NULL;//��Ϣ����
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

	//��ȡ���ݿ�����
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	CString szDate;
	szDate.Format(_T("%d-%02d-%02d"), systime.wYear, systime.wMonth, systime.wDay);

	//CString szDate = _T("2018-11-02");
	getYieldDataFromMysql(szDate, m_ThisDayYieldData);

}

CDirectionDetectDoc::~CDirectionDetectDoc()
{
	//�������ݿ�����
	UpdateYieldDataToMysql(m_ThisDayYieldData[0].sz_date);

	//�ر����ݿ�����
	m_pCppToMysql->CloseMySQLConn();
	m_pCppToMysql->~CCppToMysql();
	m_pCppToMysql = NULL;
	g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("mysql closeConnect success"));
	
	//�ر���־ϵͳ
	g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("------------------"));
	Sleep(100);
	g_logger->UnInit();
}


BOOL CDirectionDetectDoc::getYieldDataFromMysql(CString szdate, yieldData *pYieldData)
{
	char chdate[20];
	int n = szdate.GetLength(); //���ַ����㣬str�ĳ���
	int len = WideCharToMultiByte(CP_ACP, 0, szdate, n, NULL, 0, NULL, NULL);//��Byte����str����
	//
	WideCharToMultiByte(CP_ACP, 0, szdate, n, chdate, len, NULL, NULL);//���ֽ�ת��Ϊ���ֽڱ���
	chdate[len] = '\0';//��Ҫ����ĩβ������־

	char mysqlCommand[100] = { 0 };
	sprintf(mysqlCommand, "select * from tb1 where date = '%s'", chdate);

	char *Msg = NULL;//��Ϣ����
	std::string str = m_pCppToMysql->SelectData(mysqlCommand, 3, &Msg);
	const char*p = str.data();
	//���
	size_t i=0;

	while (str.find(0x5, i)!=-1)
	{
		size_t indexDate = str.find(0x6, i);
		std::string subDate = str.substr(i, indexDate-i);
		const char *p1 = subDate.data();
		//m_ThisDayYieldData[0].sz_date = subDate.data();

		indexDate += 1;
		size_t indexType = str.find(0x6, indexDate);
		std::string subType = str.substr(indexDate, indexType - indexDate);
		const char *p2 = subType.data();
		int nType = atoi(subType.data());
		//m_ThisDayYieldData[nType-1].n_type = nType;

		indexType += 1;
		size_t indexDateYield = str.find(0x6, indexType);
		std::string subDateYield = str.substr(indexType, indexDateYield - indexType);
		const char *p3 = subDateYield.data();
		pYieldData[nType-1].n_dateYield = atoi(subDateYield.data());

		i = indexDateYield + 2;
	}

	for (int j = 0; j < JIYU_TYPE_NUM; j++)//��ʼ��������+������
	{
		pYieldData[j].sz_date = szdate;
		pYieldData[j].n_type = j + 1;
	}
	g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("get mysql yeild data"));
	return 0;
}


void CDirectionDetectDoc::addThisTimeYield(int type)
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	CString szDate;
	szDate.Format(_T("%d-%02d-%02d"), systime.wYear, systime.wMonth, systime.wDay);

	if (szDate > m_ThisDayYieldData[type].sz_date)//�»�ȡ����ʱ��>��¼���ڣ���Ϊ�ڶ���
	{
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("addThisTimeYield ���ڷ����仯������ǰһ��������MySQL�����ñ��ؼ�¼"));
		
		UpdateYieldDataToMysql(m_ThisDayYieldData[type].sz_date);

		for (int i = 0; i < JIYU_TYPE_NUM; i++)
		{
			m_ThisDayYieldData[i].sz_date.Empty();
			m_ThisDayYieldData[i].sz_date = szDate;
			m_ThisDayYieldData[i].n_type = i + 1;
			m_ThisDayYieldData[i].n_dateYield = 0;
			m_ThisDayYieldData[i].n_thisTimeYield = 0;
		}
	}
	else if(szDate == m_ThisDayYieldData[type].sz_date)
	{

	}
	else
	{
		g_logger->Log(ILogger::LogLevel::LL_ERROR, _T("addThisTimeYield date get error"));
	}


	m_ThisDayYieldData[type].n_dateYield++;
	m_ThisDayYieldData[type].n_thisTimeYield++;

	//������ͼͨ�÷���
	//UpdateAllViews(NULL);  //then ondraw()
	//������  ��ȡָ�룬ֱ�ӵ��ã��˷���������Ϣ�Ŷ�==sendmessage��������ܶ�Ϊ���̣߳�
	//��ȡָ�뻹��ͨ����������ã����淽��ֻ�ܻ�ȡ���ĵ��󶨵���ͼ��
	CView* pView = NULL;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CDlg_2FormView)))
			break;
	}
	((CDlg_2FormView*)pView)->updateStatisticListCtrl();
}


BOOL CDirectionDetectDoc::UpdateYieldDataToMysql(CString szdate)
{
	char chdate[20];
	int n = szdate.GetLength(); //���ַ����㣬str�ĳ���
	int len = WideCharToMultiByte(CP_ACP, 0, szdate, n, NULL, 0, NULL, NULL);//��Byte����str����
	//
	WideCharToMultiByte(CP_ACP, 0, szdate, n, chdate, len, NULL, NULL);//���ֽ�ת��Ϊ���ֽڱ���
	chdate[len] = '\0';//��Ҫ����ĩβ������־

	int nret = 0;
	for (int i = 0; i < JIYU_TYPE_NUM; i++)
	{
		if (m_ThisDayYieldData[i].n_dateYield > 0)//Ϊ0�Ĳ�update
		{
			char mysqlCommand[100] = { 0 };
			sprintf(mysqlCommand, "REPLACE INTO tb1(date, type, dateYield) VALUES('%s', %d, %d);"/*��Ҫ��������*/, 
				chdate,
				m_ThisDayYieldData[i].n_type, 
				m_ThisDayYieldData[i].n_dateYield);
			char *Msg = NULL;//��Ϣ����
			nret = m_pCppToMysql->UpdateData(mysqlCommand, &Msg);
			if (nret == 1)
			{
				CString sztmp(Msg);
				AfxMessageBox(sztmp);
				g_logger->Log(ILogger::LogLevel::LL_ERROR, sztmp);
				break;
			}
		}
	}
	if (nret == 0)
		g_logger->Log(ILogger::LogLevel::LL_DEBUG, _T("UpdateYieldDataToMysql replace data success"));
	return 0;
}

BOOL CDirectionDetectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


// CDirectionDetectDoc ���л�

void CDirectionDetectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CDirectionDetectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CDirectionDetectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CDirectionDetectDoc ���

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


// CDirectionDetectDoc ����
