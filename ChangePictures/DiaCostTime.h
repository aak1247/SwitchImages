#pragma once


// CDiaCostTime 对话框

class CDiaCostTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaCostTime)

public:
	CDiaCostTime(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiaCostTime();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
