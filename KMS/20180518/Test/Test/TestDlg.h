
// TestDlg.h: 헤더 파일
//

#pragma once

#pragma comment(lib,"vfw32.lib")

#include"vfw.h"
#include"afxwin.h"

#define _DEF_WEBCAM 1000

LRESULT CALLBACK CallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr);

// CTestDlg 대화 상자
class CTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	void OnDestroy();

public:
	afx_msg void OnBnClickedOk();

	HWND m_Cap;
	CStatic m_stDisplay;
	CStatic m_stDisplay2;
};
