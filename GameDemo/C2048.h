#pragma once

// C2048 对话框
class C2048 : public CDialogEx
{
	DECLARE_DYNAMIC(C2048)

public:
	C2048(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C2048();
	void left();
	void up();
	void down();
	void right();
	void XS();
	void JC();
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit t2;
	CEdit t1;
	CEdit t3;
	// welcome to edit
	CEdit t4;
	CEdit t5;
	CEdit t6;
	CEdit t7;
	CEdit t8;
	CEdit t9;
	CEdit t10;
	CEdit t11;
	CEdit t12;
	CEdit t13;
	CEdit t14;
	CEdit t15;
	CEdit t16;

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CButton bx;
	afx_msg void OnBnClickedButton6();
};
