#pragma once


// CCameraDlg �Ի���

class CCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraDlg)

public:
	CCameraDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();

protected:
	CRect m_rect;	
	void ReSize(void);  
	POINT old;
public:
//	afx_msg void OnPaint();
};
