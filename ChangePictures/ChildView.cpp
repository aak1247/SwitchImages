
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "ChangePictures.h"
#include "ChildView.h"
#include "String.h"
#include "DiaCostTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace std;
// CChildView

CChildView::CChildView()
{
	img1 = new CImage();
	img2 = new CImage();
	img3 = new CImage();
	img1->Load(_T("res/pic1.bmp"));
	img2->Load(_T("res/pic2.bmp"));
	img3->Load(_T("res/pic1.bmp"));
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_MMXChange, &CChildView::OnMMX)
	ON_COMMAND(ID_nMMXChange, &CChildView::OnUMXX)
	ON_COMMAND(ID_SHOWTIME, &CChildView::OnShowTime)
	ON_COMMAND(ID_showSwitch, &CChildView::OnSwitch)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	HDC pDC = this->GetDC()->GetSafeHdc();
	int width = img1->GetWidth();
	int height = img1->GetHeight();
	img1->Draw(pDC, 100, 0, width*0.2, height*0.2);
	img2->Draw(pDC, 148, 0, width*0.2, height*0.2);
	img3->Draw(pDC, 24, 64);
	// TODO:  在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}

void CChildView::mmx()
{
	HDC pDC = this->GetDC()->GetSafeHdc();    //获得句柄

	int width = img1->GetWidth();
	int height = img1->GetHeight();	  //图片大小	

	DWORD * pImg1 = (DWORD*)(img1->GetPixelAddress(0, height - 1));   //获取像素地址
	DWORD * pImg2 = (DWORD*)(img2->GetPixelAddress(0, height - 1));
	DWORD * pImg3 = (DWORD*)(img3->GetPixelAddress(0, height - 1));
	SYSTEMTIME Time0 = { 0 };
	GetLocalTime(&Time0);
	int n = width*height * 3 / 4;     //24位位图

	for (int k = 255; k >= 0; k--)
	{
		DWORD * t1 = pImg1;
		DWORD * t2 = pImg2;
		DWORD * t3 = pImg3;

		BYTE  *fadeA = new BYTE[4];   //32位  像素点
		BYTE  *fadeB = new BYTE[4];
		fadeA[0] = k;
		fadeA[1] = k;
		fadeA[2] = k;
		fadeA[3] = k;

		fadeB[0] = 255 - k;
		fadeB[1] = 255 - k;
		fadeB[2] = 255 - k;
		fadeB[3] = 255 - k;
		for (int i = 0; i<n; i++)    //汇编处理MMX
		{
			_asm{
				mov ebx, fadeA;
				movd mm3, [ebx];
				mov ebx, fadeB;
				movd mm4, [ebx];

				mov edx, t1;
				movd mm0, [edx];
				mov edx, t2;
				movd mm1, [edx];

				pxor mm7, mm7;
				punpcklbw	mm0, mm7
				punpcklbw	mm1, mm7
				punpcklbw	mm3, mm7;
				punpcklbw	mm4, mm7;

				pmullw		mm0, mm3;
				pmullw		mm1, mm4;
				paddw		mm0, mm1;
				psrlw		mm0, 8;
				packuswb	mm0, mm7;

				mov edi, t3;
				movd[edi], mm0;

				EMMS;
			}
			t1++;
			t2++;
			t3++;
		}
		delete[]fadeA;
		delete[]fadeB;
		img3->Draw(pDC, 24, 64);    //绘制中间过程		
	}
	SYSTEMTIME Time1 = { 0 };
	GetLocalTime(&Time1);
	costMSecond = Time1.wMilliseconds - Time0.wMilliseconds;
	costSecond = Time1.wSecond - Time0.wSecond;
	costMSecond += 1000 * costSecond;
	CImage *img0;      //交换img1与img2,进行下一次变换
	img0 = img1;
	img1 = img2;
	img2 = img0;
}
void CChildView::ummx()
{
	HDC pDC = this->GetDC()->GetSafeHdc();    //获得句柄

	int width = img1->GetWidth();
	int height = img1->GetHeight();	  //图片大小	

	BYTE * pImg1 = (BYTE*)(img1->GetPixelAddress(0, height - 1));   //获取像素地址
	BYTE * pImg2 = (BYTE*)(img2->GetPixelAddress(0, height - 1));
	BYTE * pImg3 = (BYTE*)(img3->GetPixelAddress(0, height - 1));
	SYSTEMTIME Time0 = { 0 };
	GetLocalTime(&Time0);
	int n = width*height*3;         //24位的位图

	for (int k = 255; k >= 0; k--)
	{
		BYTE * t1 = pImg1;
		BYTE * t2 = pImg2;
		BYTE * t3 = pImg3;

		BYTE  fadeA = k;           //单个色道  
		BYTE  fadeB = 255 - k;

		for (int i = 0; i<n; i++)    //汇编暴力处理像素点
		{
			_asm{
				mov ecx, 0;
				mov eax, 0;
				mov ebx, 0;
				mov edx, 0;
				mov al, fadeA;
				mov ebx, t1;
				mov dl, [ebx];
				mul dx;
				mov ecx, eax;
				mov eax, 0;
				mov edx, 0;
				mov al, fadeB;
				mov ebx, t2;
				mov dl, [ebx]
				mul dx;
				add eax, ecx;
				shr eax, 8;

				mov edi, t3;
				mov [edi], eax;
				}
			t1++;
			t2++;
			t3++;
		}
		img3->Draw(pDC, 24, 64);    //绘制中间过程		
	}
	SYSTEMTIME Time1 = { 0 };
	GetLocalTime(&Time1);
	costMSecond = Time1.wMilliseconds - Time0.wMilliseconds;
	costSecond = Time1.wSecond - Time0.wSecond;
	costMSecond += 1000 * costSecond;
	CImage *img0;      //交换img1与img2,进行下一次变换
	img0 = img1;
	img1 = img2;
	img2 = img0;
}
void CChildView::OnMMX()
{
	mmx();
}
void CChildView::OnUMXX()
{
	ummx();
}
void  CChildView::OnShowTime()
{
	// CDiaCostTime diaCostTime;
	//diaCostTime.DoModal();
	CString str;
	str.Format("%u毫秒", costMSecond);
	MessageBox(str,"本次切换用时");
	costSecond = 0;
	costMSecond = 0;
}
void CChildView::OnSwitch(){
	HDC pDC = this->GetDC()->GetSafeHdc();    //获得句柄

	int width = img1->GetWidth();
	int height = img1->GetHeight();	  //图片大小	

	DWORD * pImg1 = (DWORD*)(img1->GetPixelAddress(0, height - 1));   //获取像素地址
	DWORD * pImg2 = (DWORD*)(img2->GetPixelAddress(0, height - 1));
	DWORD * pImg3 = (DWORD*)(img3->GetPixelAddress(0, height - 1));
	SYSTEMTIME Time0 = { 0 };
	GetLocalTime(&Time0);
	int n = width*height * 3 / 4;     //24位位图

	for (int k = 255; k >= 0; k--)
	{
		DWORD * t1 = pImg1;
		DWORD * t2 = pImg2;
		DWORD * t3 = pImg3;

		BYTE  *fadeA = new BYTE[4];   //32位  像素点
		BYTE  *fadeB = new BYTE[4];
		fadeA[0] = k;
		fadeA[1] = k;
		fadeA[2] = k;
		fadeA[3] = k;

		fadeB[0] = 255 - k;
		fadeB[1] = 255 - k;
		fadeB[2] = 255 - k;
		fadeB[3] = 255 - k;
		for (int i = 0; i < n; i++)    //汇编处理MMX
		{
			_asm{
				mov ebx, fadeA;
				movd mm3, [ebx];
				mov ebx, fadeB;
				movd mm4, [ebx];

				mov edx, t1;
				movd mm0, [edx];
				mov edx, t2;
				movd mm1, [edx];

				pxor mm7, mm7;
				punpcklbw	mm0, mm7
					punpcklbw	mm1, mm7
					punpcklbw	mm3, mm7;
				punpcklbw	mm4, mm7;

				pmullw		mm0, mm3;
				pmullw		mm1, mm4;
				paddw		mm0, mm1;
				psrlw		mm0, 8;
				packuswb	mm0, mm7;

				mov edi, t3;
				movd[edi], mm0;

				EMMS;
			}
			t1++;
			t2++;
			t3++;
		}
		delete[]fadeA;
		delete[]fadeB;
		Sleep(10);
		img3->Draw(pDC, 24, 64);    //绘制中间过程	
	}
	SYSTEMTIME Time1 = { 0 };
	GetLocalTime(&Time1);
	costMSecond = Time1.wMilliseconds - Time0.wMilliseconds;
	costSecond = Time1.wSecond - Time0.wSecond;
	costMSecond += 1000 * costSecond;
	CImage *img0;      //交换img1与img2,进行下一次变换
	img0 = img1;
	img1 = img2;
	img2 = img0;
}