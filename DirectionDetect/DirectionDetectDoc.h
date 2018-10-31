
// DirectionDetectDoc.h : CDirectionDetectDoc 类的接口
//


#pragma once

struct yieldData
{
	CString sz_date;//日期
	int n_type;//类型
	int n_dateYield;//当日检测量
	int n_thisTimeYield;//本次开机检测量
};

class CCppToMysql;

class CDirectionDetectDoc : public CDocument
{
protected: // 仅从序列化创建
	CDirectionDetectDoc();
	DECLARE_DYNCREATE(CDirectionDetectDoc)

// 特性
public:
	CCppToMysql *m_pCppToMysql;
// 操作
public:
	//初始化表格数据
	BOOL initYieldDataFromMysql();
	//更新数据库数据
	BOOL UpdateYieldDataToMysql();
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CDirectionDetectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
