// DiaCostTime.cpp : 实现文件
//

#include "stdafx.h"
#include "ChangePictures.h"
#include "DiaCostTime.h"
#include "afxdialogex.h"


// CDiaCostTime 对话框

IMPLEMENT_DYNAMIC(CDiaCostTime, CDialogEx)

CDiaCostTime::CDiaCostTime(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaCostTime::IDD, pParent)
{

	//CPaintDC dc(this);
	//int m = 10;
	// CFont m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
	// 设置   
	// dc.SetBkMode(TRANSPARENT);
	// 设置文本颜色为红色   
	//dc.SetTextColor(RGB(255, 0, 0));
	// 在指定位置输出文本   
	//dc.TextOut(m, 10, _T("欢迎来到鸡啄米！"));
	//CDialogEx::OnPaint();
}

CDiaCostTime::~CDiaCostTime()
{
}

void CDiaCostTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);



}


BEGIN_MESSAGE_MAP(CDiaCostTime, CDialogEx)
END_MESSAGE_MAP()


// CDiaCostTime 消息处理程序
