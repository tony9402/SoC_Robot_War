
// TestDlg.cpp: 구현 파일
//

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

LRESULT CALLBACK CallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	short i, j;
	BYTE* Histogram = (BYTE*)malloc(sizeof(BYTE)*color_scale);
	memset(Histogram, 0, sizeof(BYTE)*color_scale);
	__color::Input(lpVHdr, Histogram);
	

	
	__color::Output(lpVHdr, Histogram);
	free(Histogram);
	return (LRESULT)true;
}
