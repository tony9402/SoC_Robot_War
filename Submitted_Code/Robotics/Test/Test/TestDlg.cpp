
// TestDlg.cpp: 구현 파일
//

#pragma region DONT_CHANGE
#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include"Color.h"
#include<memory>
#include<stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BITMAPINFO BmInfo;
LPBYTE pImgBuffer;	

CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_stDisplay);
	DDX_Control(pDX, IDC_STATIC2, m_stDisplay2);
	//DDX_Control(pDX, IDC_STATIC2, m_a);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTestDlg 메시지 처리기


BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	

	this->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOSIZE);

	m_Cap = capCreateCaptureWindow(TEXT("Image Test"), WS_CHILD | WS_VISIBLE, 0, 0, 640, 480, m_stDisplay, NULL);
	if (capDriverConnect(m_Cap, NULL) == FALSE)return FALSE;
	if (capSetCallbackOnFrame(m_Cap, CallbackOnFrame) == FALSE)return FALSE;
	
	capPreviewRate(m_Cap, 33);
	capOverlay(m_Cap, false);
	capPreview(m_Cap, true);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	capDriverDisconnect(m_Cap);

	if (pImgBuffer != NULL) {
		delete[] pImgBuffer;
	}
}
#pragma endregion

struct XY
{
	int Mini;
	int Maxi;
	int Minj;
	int Maxj;
};

int labeling(BYTE (*input)[width], int &x, int &y, XY &m);
void Close();

BYTE Yellow[height][width] = { 0 };
BYTE Red[height][width] = { 0 };
BYTE Blue[height][width] = { 0 };
BYTE Green[height][width] = { 0 };
BYTE Shrimp[height][width] = { 0 };

int Area_red = 0, Area_yellow = 0, Area_blue = 0, Area_green = 0, Area_shrimp = 0;

XY _red;
XY _green;
XY _yellow;
XY _blue;
XY _shrimp;

#define min(x,y) (x) > (y) ? (y) : (x)
#define max(x,y) (x) > (y) ? (x) : (y)

int Waiting_check = 0;

LRESULT CALLBACK CallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	short i, j;
	int Bluexy_i, Bluexy_j;
	int Yellowxy_i, Yellowxy_j;
	int Redxy_i, Redxy_j;
	int Greenxy_i, Greenxy_j;
	int Shrimpxy_i, Shrimpxy_j;

	__color::Input(lpVHdr);
	memset(Blue, 0, sizeof(BYTE) * height * width);
	memset(Red, 0, sizeof(BYTE) * height * width);
	memset(Yellow, 0, sizeof(BYTE) * height * width);
	memset(Green, 0, sizeof(BYTE) * height * width);
	memset(Shrimp, 0, sizeof(BYTE) * height * width);
	
	//Start
	//*
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (!IsPocarIColor(i, j) && !IsCantataColor(i,j) && !IsPocaColor(i,j) && !IsWheelColor(i,j) && !IsShrimp(i, j))
			{
				mRGB[i][j][RED] = mRGB[i][j][GREEN] = mRGB[i][j][BLUE] = 0;
			}
			else
			{
				//*
				if (IsPocarIColor(i, j))
				{
					Blue[i][j] = 255;
				}
				else {
					Blue[i][j] = 0;
				}//*/
				//*
				if (IsPocaColor(i, j))
				{
					Yellow[i][j] = 255;
				}
				else
				{
					Yellow[i][j] = 0;
				}//*/
				//*
				if (IsCantataColor(i, j))
				{
					Red[i][j] = 255;
				}
				else
				{
					Red[i][j] = 0;
				}//*/
				//*
				if (IsWheelColor(i, j))
				{
					Green[i][j] = 255;
				}
				else
				{
					Green[i][j] = 0;
				}//*/
				if (IsShrimp(i, j))
				{
					Shrimp[i][j] = 255;
				}
				else
				{
					Shrimp[i][j] = 0;
				}
			}
		}
	}

	Close();

	Area_blue = labeling(Blue, Bluexy_i, Bluexy_j, _blue);
	Area_red = labeling(Red, Redxy_i, Redxy_j, _red);
	Area_yellow = labeling(Yellow, Yellowxy_i, Yellowxy_j, _yellow);
	Area_green = labeling(Green, Greenxy_i, Greenxy_j, _green);
	Area_shrimp = labeling(Shrimp, Shrimpxy_i, Shrimpxy_j, _shrimp);
	
	//printf("Red : %5d Yellow : %5d Blue : %5d green : %5d Shrimp : %5d\n", Area_red, Area_yellow, Area_blue,Area_green, Area_shrimp); //각각 Color Channel에서 가장 큰 넓이

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Red[i][j] == 255 || Yellow[i][j] == 255 || Blue[i][j] == 255 || Green[i][j] == 255 || Shrimp[i][j] == 255)
			{
				mRGB[i][j][RED] = mRGB[i][j][GREEN] = mRGB[i][j][BLUE] = 255;
			}
			else
			{
				mRGB[i][j][RED] = mRGB[i][j][GREEN] = mRGB[i][j][BLUE] = 0;
			}
		}
	}
	
	//*
	if (Area_shrimp >= 5000 && !(Area_green >= 1500))
	{
		Waiting_check = 0;
		printf("새우깡이랑 비슷한 물체 발견\n");
		for (i = -5; i <= 5; i++)
		{
			mRGB[Shrimpxy_i + i][Shrimpxy_j][GREEN] = 0;
			mRGB[Shrimpxy_i][Shrimpxy_j + i][GREEN] = 0;
			mRGB[Shrimpxy_i + i][Shrimpxy_j][BLUE] = 0;
			mRGB[Shrimpxy_i][Shrimpxy_j + i][BLUE] = 0;
			mRGB[Shrimpxy_i + i][Shrimpxy_j][RED] = 128;
			mRGB[Shrimpxy_i][Shrimpxy_j + i][RED] = 128;
			mGRAY[Shrimpxy_i + i][Shrimpxy_j] = 0;
			mGRAY[Shrimpxy_i][Shrimpxy_j + i] = 0;
		}
		_shrimp.Maxi = _shrimp.Maxi > height ? height : _shrimp.Maxi;
		_shrimp.Maxj = _shrimp.Maxj > width ? width : _shrimp.Maxj;
		_shrimp.Mini = _shrimp.Mini < 0 ? 0 : _shrimp.Mini;
		_shrimp.Minj = _shrimp.Minj < 0 ? 0 : _shrimp.Minj;

		for (i = _shrimp.Mini; i <= _shrimp.Maxi; i++)
		{
			mRGB[i][_shrimp.Maxj][GREEN] = 0;
			mRGB[i][_shrimp.Maxj][RED] = 128;
			mRGB[i][_shrimp.Maxj][BLUE] = 0;
			mRGB[i][_shrimp.Minj][GREEN] = 0;
			mRGB[i][_shrimp.Minj][RED] = 128;
			mRGB[i][_shrimp.Minj][BLUE] = 0;
			mGRAY[i][_shrimp.Minj] = 0;
			mGRAY[i][_shrimp.Maxj] = 0;
		}

		for (j = _shrimp.Minj; j <= _shrimp.Maxj; j++)
		{
			mRGB[_shrimp.Maxi][j][GREEN] = 128;
			mRGB[_shrimp.Maxi][j][RED] = 128;
			mRGB[_shrimp.Maxi][j][BLUE] = 0;
			mRGB[_shrimp.Mini][j][GREEN] = 128;
			mRGB[_shrimp.Mini][j][RED] = 128;
			mRGB[_shrimp.Mini][j][BLUE] = 0;
			mGRAY[_shrimp.Mini][j] = 0;
			mGRAY[_shrimp.Maxi][j] = 0;
		}
	}
	else if (Area_red >= 1200 && Area_green >= 2000 || Area_green >= 2000)
	{
		Waiting_check = 0;
		printf("고래밥이랑 비슷한 물체 발견\n");

		if (Area_red > 0) {
			for (i = -5; i <= 5; i++)
			{
				mRGB[Yellowxy_i + i][Yellowxy_j][GREEN] = 255;
				mRGB[Yellowxy_i][Yellowxy_j + i][GREEN] = 255;
				mRGB[Yellowxy_i + i][Yellowxy_j][BLUE] = 0;
				mRGB[Yellowxy_i][Yellowxy_j + i][BLUE] = 0;
				mRGB[Yellowxy_i + i][Yellowxy_j][RED] = 255;
				mRGB[Yellowxy_i][Yellowxy_j + i][RED] = 255;
				mGRAY[Yellowxy_i][Yellowxy_j + i] = 0;
				mGRAY[Yellowxy_i + i][Yellowxy_j] = 0;
			}
			_yellow.Maxi = _yellow.Maxi > height ? height : _yellow.Maxi;
			_yellow.Maxj = _yellow.Maxj > width ? width : _yellow.Maxj;
			_yellow.Mini = _yellow.Mini < 0 ? 0 : _yellow.Mini;
			_yellow.Minj = _yellow.Minj < 0 ? 0 : _yellow.Minj;

			for (i = _yellow.Mini; i <= _yellow.Maxi; i++)
			{
				mRGB[i][_yellow.Maxj][GREEN] = 0;
				mRGB[i][_yellow.Maxj][RED] = 0;
				mRGB[i][_yellow.Maxj][BLUE] = 255;
				mRGB[i][_yellow.Minj][GREEN] = 0;
				mRGB[i][_yellow.Minj][RED] = 0;
				mRGB[i][_yellow.Minj][BLUE] = 255;
				mGRAY[i][_yellow.Minj] = 0;
				mGRAY[i][_yellow.Maxj] = 0;
			}

			for (j = _yellow.Minj; j <= _yellow.Maxj; j++)
			{
				mRGB[_yellow.Maxi][j][GREEN] = 255;
				mRGB[_yellow.Maxi][j][RED] = 0;
				mRGB[_yellow.Maxi][j][BLUE] = 0;
				mRGB[_yellow.Mini][j][GREEN] = 255;
				mRGB[_yellow.Mini][j][RED] = 0;
				mRGB[_yellow.Mini][j][BLUE] = 0;
				mGRAY[_yellow.Mini][j] = 0;
				mGRAY[_yellow.Maxi][j] = 0;
			}

			for (i = -5; i <= 5; i++)
			{
				mRGB[Redxy_i + i][Redxy_j][GREEN] = 0;
				mRGB[Redxy_i][Redxy_j + i][GREEN] = 0;
				mRGB[Redxy_i + i][Redxy_j][BLUE] = 0;
				mRGB[Redxy_i][Redxy_j + i][BLUE] = 0;
				mRGB[Redxy_i + i][Redxy_j][RED] = 255;
				mRGB[Redxy_i][Redxy_j + i][RED] = 255;
				mGRAY[Redxy_i + i][Redxy_j] = 0;
				mGRAY[Redxy_i][Redxy_j + i] = 0;
			}
			_red.Maxi = _red.Maxi > height ? height : _red.Maxi;
			_red.Maxj = _red.Maxj > width ? width : _red.Maxj;
			_red.Mini = _red.Mini < 0 ? 0 : _red.Mini;
			_red.Minj = _red.Minj < 0 ? 0 : _red.Minj;

			for (i = _red.Mini; i <= _red.Maxi; i++)
			{
				mRGB[i][_red.Maxj][GREEN] = 0;
				mRGB[i][_red.Maxj][RED] = 255;
				mRGB[i][_red.Maxj][BLUE] = 0;
				mRGB[i][_red.Minj][GREEN] = 0;
				mRGB[i][_red.Minj][RED] = 255;
				mRGB[i][_red.Minj][BLUE] = 0;
				mGRAY[i][_red.Minj] = 0;
				mGRAY[i][_red.Maxj] = 0;
			}

			for (j = _red.Minj; j <= _red.Maxj; j++)
			{
				mRGB[_red.Maxi][j][GREEN] = 255;
				mRGB[_red.Maxi][j][RED] = 0;
				mRGB[_red.Maxi][j][BLUE] = 0;
				mRGB[_red.Mini][j][GREEN] = 255;
				mRGB[_red.Mini][j][RED] = 0;
				mRGB[_red.Mini][j][BLUE] = 0;
				mGRAY[_red.Mini][j] = 0;
				mGRAY[_red.Maxi][j] = 0;
			}

			for (i = -5; i <= 5; i++)
			{
				mRGB[(Greenxy_i+Redxy_i+Yellowxy_i) / 3 + i][(Greenxy_j + Redxy_j + Yellowxy_j) / 3][GREEN] = 255;
				mRGB[(Greenxy_i + Redxy_i + Yellowxy_i) / 3][(Greenxy_j + Redxy_j + Yellowxy_j) / 3 + i][GREEN] = 255;
				mRGB[(Greenxy_i + Redxy_i + Yellowxy_i) / 3 + i][(Greenxy_j + Redxy_j + Yellowxy_j) / 3][BLUE] = 255;
				mRGB[(Greenxy_i + Redxy_i + Yellowxy_i) / 3][(Greenxy_j + Redxy_j + Yellowxy_j) / 3 + i][BLUE] = 255;
				mRGB[(Greenxy_i + Redxy_i + Yellowxy_i) / 3 + i][(Greenxy_j + Redxy_j + Yellowxy_j) / 3][RED] = 0;
				mRGB[(Greenxy_i + Redxy_i + Yellowxy_i) / 3][(Greenxy_j + Redxy_j + Yellowxy_j) / 3 + i][RED] = 0;
				mGRAY[(Greenxy_i + Redxy_i + Yellowxy_i) / 3 + i][(Greenxy_j + Redxy_j + Yellowxy_j) / 3] = 0;
				mGRAY[(Greenxy_i + Redxy_i + Yellowxy_i) / 3][(Greenxy_j + Redxy_j + Yellowxy_j) / 3+ i] = 0;
			}
		}

		for (i = -5; i <= 5; i++)
		{
			mRGB[Greenxy_i + i][Greenxy_j][GREEN] = 255;
			mRGB[Greenxy_i][Greenxy_j + i][GREEN] = 255;
			mRGB[Greenxy_i + i][Greenxy_j][BLUE] = 0;
			mRGB[Greenxy_i][Greenxy_j + i][BLUE] = 0;
			mRGB[Greenxy_i + i][Greenxy_j][RED] = 0;
			mRGB[Greenxy_i][Greenxy_j + i][RED] = 0;
			mGRAY[Greenxy_i + i][Greenxy_j] = 0;
			mGRAY[Greenxy_i][Greenxy_j + i] = 0;
		}
		_green.Maxi = _green.Maxi > height ? height : _green.Maxi;
		_green.Maxj = _green.Maxj > width ? width : _green.Maxj;
		_green.Mini = _green.Mini < 0 ? 0 : _green.Mini;
		_green.Minj = _green.Minj < 0 ? 0 : _green.Minj;

		for (i = _green.Mini; i <= _green.Maxi; i++)
		{
			mRGB[i][_green.Maxj][GREEN] = 255;
			mRGB[i][_green.Maxj][RED] = 0;
			mRGB[i][_green.Maxj][BLUE] = 0;
			mRGB[i][_green.Minj][GREEN] = 255;
			mRGB[i][_green.Minj][RED] = 0;
			mRGB[i][_green.Minj][BLUE] = 0;
			mGRAY[i][_green.Minj] = 0;
			mGRAY[i][_green.Maxj] = 0;
		}

		for (j = _green.Minj; j <= _green.Maxj; j++)
		{
			mRGB[_green.Maxi][j][GREEN] = 0;
			mRGB[_green.Maxi][j][RED] = 0;
			mRGB[_green.Maxi][j][BLUE] = 255;
			mRGB[_green.Mini][j][GREEN] = 0;
			mRGB[_green.Mini][j][RED] = 0;
			mRGB[_green.Mini][j][BLUE] = 255;
			mGRAY[_green.Mini][j] = 0;
			mGRAY[_green.Maxi][j] = 0;
		}
	}
	else if (Area_red >= 700 && Area_yellow >= 1000 || Area_yellow >= 1500)
	{
		Waiting_check = 0;
		printf("포카칩이랑 비슷한 물체 발견\n");
		if (Area_red >= 700) {
			for (i = -5; i <= 5; i++)
			{
				mRGB[Redxy_i + i][Redxy_j][GREEN] = 0;
				mRGB[Redxy_i][Redxy_j + i][GREEN] = 0;
				mRGB[Redxy_i + i][Redxy_j][BLUE] = 0;
				mRGB[Redxy_i][Redxy_j + i][BLUE] = 0;
				mRGB[Redxy_i + i][Redxy_j][RED] = 255;
				mRGB[Redxy_i][Redxy_j + i][RED] = 255;
				mGRAY[Redxy_i + i][Redxy_j] = 0;
				mGRAY[Redxy_i][Redxy_j + i] = 0;
			}
			_red.Maxi = _red.Maxi > height ? height : _red.Maxi;
			_red.Maxj = _red.Maxj > width ? width : _red.Maxj;
			_red.Mini = _red.Mini < 0 ? 0 : _red.Mini;
			_red.Minj = _red.Minj < 0 ? 0 : _red.Minj;

			for (i = _red.Mini; i <= _red.Maxi; i++)
			{
				mRGB[i][_red.Maxj][GREEN] = 0;
				mRGB[i][_red.Maxj][RED] = 255;
				mRGB[i][_red.Maxj][BLUE] = 0;
				mRGB[i][_red.Minj][GREEN] = 0;
				mRGB[i][_red.Minj][RED] = 255;
				mRGB[i][_red.Minj][BLUE] = 0;
				mGRAY[i][_red.Minj] = 0;
				mGRAY[i][_red.Maxj] = 0;
			}

			for (j = _red.Minj; j <= _red.Maxj; j++)
			{
				mRGB[_red.Maxi][j][GREEN] = 255;
				mRGB[_red.Maxi][j][RED] = 0;
				mRGB[_red.Maxi][j][BLUE] = 0;
				mRGB[_red.Mini][j][GREEN] = 255;
				mRGB[_red.Mini][j][RED] = 0;
				mRGB[_red.Mini][j][BLUE] = 0;
				mGRAY[_red.Mini][j] = 0;
				mGRAY[_red.Maxi][j] = 0;
			}
		}
		for (i = -5; i <= 5; i++)
		{
			mRGB[Yellowxy_i + i][Yellowxy_j][GREEN] = 255;
			mRGB[Yellowxy_i][Yellowxy_j + i][GREEN] = 255;
			mRGB[Yellowxy_i + i][Yellowxy_j][BLUE] = 0;
			mRGB[Yellowxy_i][Yellowxy_j + i][BLUE] = 0;
			mRGB[Yellowxy_i + i][Yellowxy_j][RED] = 0;
			mRGB[Yellowxy_i][Yellowxy_j + i][RED] = 0;
			mGRAY[Yellowxy_i][Yellowxy_j + i] = 0;
			mGRAY[Yellowxy_i + i][Yellowxy_j] = 0;
		}
		_yellow.Maxi = _yellow.Maxi > height ? height : _yellow.Maxi;
		_yellow.Maxj = _yellow.Maxj > width ? width : _yellow.Maxj;
		_yellow.Mini = _yellow.Mini < 0 ? 0 : _yellow.Mini;
		_yellow.Minj = _yellow.Minj < 0 ? 0 : _yellow.Minj;

		for (i = _yellow.Mini; i <= _yellow.Maxi; i++)
		{
			mRGB[i][_yellow.Maxj][GREEN] = 0;
			mRGB[i][_yellow.Maxj][RED] = 0;
			mRGB[i][_yellow.Maxj][BLUE] = 255;
			mRGB[i][_yellow.Minj][GREEN] = 0;
			mRGB[i][_yellow.Minj][RED] = 0;
			mRGB[i][_yellow.Minj][BLUE] = 255;
			mGRAY[i][_yellow.Minj] = 0;
			mGRAY[i][_yellow.Maxj] = 0;
		}

		for (j = _yellow.Minj; j <= _yellow.Maxj; j++)
		{
			mRGB[_yellow.Maxi][j][GREEN] = 255;
			mRGB[_yellow.Maxi][j][RED] = 0;
			mRGB[_yellow.Maxi][j][BLUE] = 0;
			mRGB[_yellow.Mini][j][GREEN] = 255;
			mRGB[_yellow.Mini][j][RED] = 0;
			mRGB[_yellow.Mini][j][BLUE] = 0;
			mGRAY[_yellow.Mini][j] = 0;
			mGRAY[_yellow.Maxi][j] = 0;
		}
	}
	else if (Area_blue >= 1500 && !(Area_yellow >= 800) && !(Area_red >= 800))
	{
		Waiting_check = 0;
		printf("포카리이랑 비슷한 물체 발견\n");
		for (i = -5; i <= 5; i++)
		{
			mRGB[Bluexy_i + i][Bluexy_j][GREEN] = 255;
			mRGB[Bluexy_i][Bluexy_j + i][GREEN] = 255;
			mRGB[Bluexy_i + i][Bluexy_j][BLUE] = 0;
			mRGB[Bluexy_i][Bluexy_j + i][BLUE] = 0;
			mRGB[Bluexy_i + i][Bluexy_j][RED] = 0;
			mRGB[Bluexy_i][Bluexy_j + i][RED] = 0;
			mGRAY[Bluexy_i][Bluexy_j + i] = 0;
			mGRAY[Bluexy_i + i][Bluexy_j] = 0;
		}
		_blue.Maxi = _blue.Maxi > height ? height : _blue.Maxi;
		_blue.Maxj = _blue.Maxj > width ? width : _blue.Maxj;
		_blue.Mini = _blue.Mini < 0 ? 0 : _blue.Mini;
		_blue.Minj = _blue.Minj < 0 ? 0 : _blue.Minj;

		for (i = _blue.Mini; i <= _blue.Maxi; i++)
		{
			mRGB[i][_blue.Maxj][GREEN] = 0;
			mRGB[i][_blue.Maxj][RED] = 0;
			mRGB[i][_blue.Maxj][BLUE] = 255;
			mRGB[i][_blue.Minj][GREEN] = 0;
			mRGB[i][_blue.Minj][RED] = 0;
			mRGB[i][_blue.Minj][BLUE] = 255;
			mGRAY[i][_blue.Minj] = 0;
			mGRAY[i][_blue.Maxj] = 0;
		}

		for (j = _blue.Minj; j <= _blue.Maxj; j++)
		{
			mRGB[_blue.Maxi][j][GREEN] = 255;
			mRGB[_blue.Maxi][j][RED] = 0;
			mRGB[_blue.Maxi][j][BLUE] = 0;
			mRGB[_blue.Mini][j][GREEN] = 255;
			mRGB[_blue.Mini][j][RED] = 0;
			mRGB[_blue.Mini][j][BLUE] = 0;
			mGRAY[_blue.Mini][j] = 0;
			mGRAY[_blue.Maxi][j] = 0;
		}
	}
	else if (Area_red >= 900 && !(Area_blue >= 1250) && !(Area_yellow >= 1300))
	{
		Waiting_check = 0;
		printf("칸타타이랑 비슷한 물체 발견\n");


		for (i = -5; i <= 5; i++)
		{
			mRGB[Redxy_i + i][Redxy_j][GREEN] = 0;
			mRGB[Redxy_i][Redxy_j + i][GREEN] = 0;
			mRGB[Redxy_i + i][Redxy_j][BLUE] = 0;
			mRGB[Redxy_i][Redxy_j + i][BLUE] = 0;
			mRGB[Redxy_i + i][Redxy_j][RED] = 255;
			mRGB[Redxy_i][Redxy_j + i][RED] = 255;
			mGRAY[Redxy_i + i][Redxy_j] = 0;
			mGRAY[Redxy_i][Redxy_j + i] = 0;
		}
		_red.Maxi = _red.Maxi > height ? height : _red.Maxi;
		_red.Maxj = _red.Maxj > width ? width : _red.Maxj;
		_red.Mini = _red.Mini < 0 ? 0 : _red.Mini;
		_red.Minj = _red.Minj < 0 ? 0 : _red.Minj;

		for (i = _red.Mini; i <= _red.Maxi; i++)
		{
			mRGB[i][_red.Maxj][GREEN] = 0;
			mRGB[i][_red.Maxj][RED] = 255;
			mRGB[i][_red.Maxj][BLUE] = 0;
			mRGB[i][_red.Minj][GREEN] = 0;
			mRGB[i][_red.Minj][RED] = 255;
			mRGB[i][_red.Minj][BLUE] = 0;
			mGRAY[i][_red.Minj] = 0;
			mGRAY[i][_red.Maxj] = 0;
		}

		for (j = _red.Minj; j <= _red.Maxj; j++)
		{
			mRGB[_red.Maxi][j][GREEN] = 255;
			mRGB[_red.Maxi][j][RED] = 0;
			mRGB[_red.Maxi][j][BLUE] = 0;
			mRGB[_red.Mini][j][GREEN] = 255;
			mRGB[_red.Mini][j][RED] = 0;
			mRGB[_red.Mini][j][BLUE] = 0;
			mGRAY[_red.Mini][j] = 0;
			mGRAY[_red.Maxi][j] = 0;
		}
	}
	else
	{
		if (Waiting_check == 0) {
			printf("Waiting\n");
			Waiting_check = 1;
		}
	}
	
	__color::Output(lpVHdr);

	return (LRESULT)true;
}

BYTE sRed[height][width] = { 0 };
BYTE sYellow[height][width] = { 0 };
BYTE sBlue[height][width] = { 0 };
BYTE sGreen[height][width] = { 0 };
BYTE sShrimp[height][width] = { 0 };

void Close()
{
	short i, j;

	for (i = 0; i < height; i++)
	{
		memcpy(sRed[i], Red[i], sizeof(BYTE) * width);
		memcpy(sYellow[i], Yellow[i], sizeof(BYTE) * width);
		memcpy(sBlue[i], Blue[i], sizeof(BYTE) * width);
		memcpy(sGreen[i], Green[i], sizeof(BYTE) * width);
		memcpy(sShrimp[i], Shrimp[i], sizeof(BYTE) * width);
	}

	for (int CNT = 0; CNT < 4; CNT++) {
		for (i = 1; i < height - 1; i++)
		{
			for (j = 1; j < width - 1; j++)
			{
				if (sRed[i][j] == 0) {
					for (int m = -1; m <= 1; m++)
					{
						for (int n = -1; n <= 1; n++)
						{
							if (sRed[i + m][j + n] != 0)
							{
								Red[i][j] = 255;
								break;
							}
						}
					}
				}
				if (sYellow[i][j] == 0) {
					for (int m = -1; m <= 1; m++)
					{
						for (int n = -1; n <= 1; n++)
						{
							if (sYellow[i + m][j + n] != 0)
							{
								Yellow[i][j] = 255;
								break;
							}
						}
					}
				}
				if (sBlue[i][j] == 0) {
					for (int m = -1; m <= 1; m++)
					{
						for (int n = -1; n <= 1; n++)
						{
							if (sBlue[i + m][j + n] != 0)
							{
								Blue[i][j] = 255;
								break;
							}
						}
					}
				}
				if (sGreen[i][j] == 0) {
					for (int m = -1; m <= 1; m++)
					{
						for (int n = -1; n <= 1; n++)
						{
							if (sGreen[i + m][j + n] != 0)
							{
								Green[i][j] = 255;
								break;
							}
						}
					}
				}
				if (sShrimp[i][j] == 0) {
					for (int m = -1; m <= 1; m++)
					{
						for (int n = -1; n <= 1; n++)
						{
							if (sShrimp[i + m][j + n] != 0)
							{
								Shrimp[i][j] = 255;
								break;
							}
						}
					}
				}
			}
		}
		for (i = 0; i < height; i++) {
			memcpy(sRed[i], Red[i], sizeof(BYTE) * width);
			memcpy(sYellow[i], Yellow[i], sizeof(BYTE) * width);
			memcpy(sGreen[i], Green[i], sizeof(BYTE) * width);
			memcpy(sBlue[i], Blue[i], sizeof(BYTE) * width);
			memcpy(sShrimp[i], Shrimp[i], sizeof(BYTE) * width);
		}
	}

	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			if (sRed[i][j] == 255) {
				for (int m = -1; m <= 1; m++)
				{
					for (int n = -1; n <= 1; n++)
					{
						if (sRed[i + m][j + n] == 0)
						{
							Red[i][j] = 0;
							break;
						}
					}
				}
			}
			if (sYellow[i][j] == 255) {
				for (int m = -1; m <= 1; m++)
				{
					for (int n = -1; n <= 1; n++)
					{
						if (sYellow[i + m][j + n] == 0)
						{
							Yellow[i][j] = 0;
							break;
						}
					}
				}
			}
			if (sBlue[i][j] == 255) {
				for (int m = -1; m <= 1; m++)
				{
					for (int n = -1; n <= 1; n++)
					{
						if (sBlue[i + m][j + n] == 0)
						{
							Blue[i][j] = 0;
							break;
						}
					}
				}
			}
			if (sGreen[i][j] == 255) {
				for (int m = -1; m <= 1; m++)
				{
					for (int n = -1; n <= 1; n++)
					{
						if (sGreen[i + m][j + n] == 0)
						{
							Green[i][j] = 0;
							break;
						}
					}
				}
			}
			if (sShrimp[i][j] == 255) {
				for (int m = -1; m <= 1; m++)
				{
					for (int n = -1; n <= 1; n++)
					{
						if (sShrimp[i + m][j + n] == 0)
						{
							Shrimp[i][j] = 0;
							break;
						}
					}
				}
			}
		}
	}

	return;
}

int labeling(BYTE(*input)[width], int &x, int &y, XY &m)
{
	short i, j;
	int **index = (int**)malloc(sizeof(int*) * height);
	int *cnt_Val = (int*)malloc(sizeof(int) * 1000);
	int *area = (int*)malloc(sizeof(int) * 1000);

	for (i = 0; i < height; i++)
	{
		index[i] = (int*)malloc(sizeof(int) * width);
		memset(index[i], 0, sizeof(int) * width);
	}
	memset(cnt_Val, 0, sizeof(int) * 1000);
	memset(area, 0, sizeof(int) * 1000);

	int cnt = 0, last_cnt = 0;

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (input[i][j] == 255)
			{
				if (index[i - 1][j] == 0 && index[i][j - 1] == 0)
				{
					cnt++;
					index[i][j] = cnt;
					cnt_Val[cnt] = cnt;
				}
				else if (index[i - 1][j] != 0 && index[i][j - 1] == 0)
				{
					index[i][j] = index[i - 1][j];
				}
				else if (index[i - 1][j] == 0 && index[i][j - 1] != 0)
				{
					index[i][j] = index[i][j - 1];
				}
				else if (index[i - 1][j] == index[i][j - 1] && index[i][j - 1] != 0)
				{
					index[i][j] = index[i][j - 1];
				}
				else if (index[i - 1][j] != index[i][j - 1] && index[i - 1][j] != 0 && index[i][j - 1] != 0)
				{
					index[i][j] = min(index[i][j - 1], index[i - 1][j]);
					cnt_Val[max(index[i][j - 1], index[i - 1][j])] = min(cnt_Val[max(index[i][j - 1], index[i - 1][j])], min(index[i][j - 1], index[i - 1][j]));
				}
				else
				{
					index[i][j] = 0;
				}
				last_cnt = cnt;
			}
		}
	}
	if (last_cnt == 0) {
		for (i = 0; i < height; i++)
		{
			free(index[i]);
		}
		free(index);
		free(cnt_Val);
		free(area);
		return 0;
	}
	int Forcnt;

	for (Forcnt = last_cnt; Forcnt >= 1; Forcnt--)
	{
		if (cnt_Val[Forcnt] != Forcnt)
		{
			for (i = 1; i < height; i++)
			{
				for (j = 1; j < width; j++)
				{
					if (index[i][j] == Forcnt)
					{
						index[i][j] = cnt_Val[Forcnt];
					}
				}
			}
		}
	}

	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			if (index[i][j] != 0)
			{
				area[index[i][j]]++;
			}
		}
	}

	int area_Max = 0, area_cnt = 0;
	int Max_Save_i= 0, Max_Save_j=0;
	int Min_Save_i=10e10, Min_Save_j=10e10;

	for (i = 1; i < last_cnt; i++)
	{
		if (area[i] > area_Max && area[i] > 150) //넓이 기준값보다 클때 계산
		{
			area_Max = area[i];
			area_cnt = i;
		}
	}

	if (area_Max == 0) {
		for (i = 0; i < height; i++)
		{
			free(index[i]);
		}
		free(index);
		free(cnt_Val);
		free(area);
		return 0;
	}

	int Max_area_i = 0, Max_area_j = 0, xycnt = 0;

	if (area_cnt == 0)
	{
		memset(input, 0, sizeof(BYTE)*height * width);
	}
	else
	{
		for (i = 1; i < height; i++)
		{
			for (j = 1; j < width; j++)
			{
				if (index[i][j] != area_cnt)
				{
					input[i][j] = 0;
				}
				else
				{
					input[i][j] = 255;
					Max_area_i += i;
					Max_area_j += j;
					xycnt++;
					if (i < Min_Save_i)
					{
						Min_Save_i = i;
					}
					if (j < Min_Save_j)
					{
						Min_Save_j = j;
					}
					if (i > Max_Save_i)
					{
						Max_Save_i = i;
					}
					if (j > Max_Save_j)
					{
						Max_Save_j = j;
					}

				}
			}
		}
	}

	m.Maxi = Max_Save_i;
	m.Maxj = Max_Save_j;
	m.Mini = Min_Save_i;
	m.Minj = Min_Save_j;

	x = Max_area_i / (float)xycnt;
	y = Max_area_j / (float)xycnt;

	for (i = 0; i < height; i++)
	{
		free(index[i]);
	}
	free(index);
	free(cnt_Val);
	free(area);

	return area_Max;
}