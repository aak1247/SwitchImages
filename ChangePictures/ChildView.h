
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once


// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
private:
	CImage* img1;
	CImage* img2;
	CImage* img3;

public:
	void mmx();
	void ummx();
	int costSecond = 0;
	int costMSecond = 0;
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	afx_msg void OnMMX();
	afx_msg void OnUMXX();
	afx_msg void OnShowTime();
	afx_msg void OnSwitch();
	DECLARE_MESSAGE_MAP()
};

