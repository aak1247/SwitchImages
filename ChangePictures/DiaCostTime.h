#pragma once


// CDiaCostTime �Ի���

class CDiaCostTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaCostTime)

public:
	CDiaCostTime(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaCostTime();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
