
// DirectionDetectDoc.h : CDirectionDetectDoc ��Ľӿ�
//


#pragma once

struct yieldData
{
	yieldData()
	{
		n_type = 0;
		n_dateYield = 0;
		n_thisTimeYield = 0;
	}
	CString sz_date;//����
	int n_type;//����
	int n_dateYield;//���ռ����
	int n_thisTimeYield;//���ο��������
};

class CCppToMysql;

class CDirectionDetectDoc : public CDocument
{
protected: // �������л�����
	CDirectionDetectDoc();
	DECLARE_DYNCREATE(CDirectionDetectDoc)

// ����
public:
	CCppToMysql *m_pCppToMysql;
	yieldData  m_ThisDayYieldData[4];
	yieldData  m_HistoryYieldData[4];
// ����
public:
	//��ʼ���������
	BOOL initYieldDataFromMysql(CString szdate);
	//�������ݿ�����
	BOOL UpdateYieldDataToMysql(char *cmd);




// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CDirectionDetectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
