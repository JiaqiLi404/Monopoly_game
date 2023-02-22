
// GameDemoDlg.h: 头文件
//
#include"C2048.h"
#pragma once

extern int mon;
extern int res;//1通过2不通过 
extern	int loc;
extern boolean hasLZ;//是否有路障
extern int BScost;//别墅按揭付款
extern double sco;//分数
extern double highestsco;
// CGameDemoDlg 对话框
class CGameDemoDlg : public CDialogEx
{
	
// 构造
public:
	CGameDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数
	void RefreshIndividualControl(UINT uCtlID);
	int getRand();

	
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit t2;
	CEdit t1;
	CEdit t3;
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
	CButton b1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit t15;
	CEdit t16;
	afx_msg void OnBnClickedButton1();
	CEdit t17;
	CButton b2;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CButton b;
	afx_msg void OnBnClickedButton5();
	CEdit tonline;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
};
