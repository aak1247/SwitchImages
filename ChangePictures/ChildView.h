
// ChildView.h : CChildView 类的接口
//


#pragma once


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
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

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	afx_msg void OnMMX();
	afx_msg void OnUMXX();
	afx_msg void OnShowTime();
	afx_msg void OnSwitch();
	DECLARE_MESSAGE_MAP()
};

