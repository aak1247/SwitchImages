
// ChangePictures.h : ChangePictures Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChangePicturesApp:
// �йش����ʵ�֣������ ChangePictures.cpp
//

class CChangePicturesApp : public CWinApp
{
public:
	CChangePicturesApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
public:
	afx_msg void OnAppAbout();
//	afx_msg void OnMMX();
//	afx_msg void OnUMXX();
	DECLARE_MESSAGE_MAP()
};

extern CChangePicturesApp theApp;
