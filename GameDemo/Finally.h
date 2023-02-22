#pragma once
#include"C2048.h"

// Finally 对话框

class Finally : public CDialogEx
{
	DECLARE_DYNAMIC(Finally)

public:
	Finally(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Finally();
	void RefreshIndividualControl(UINT uCtlID);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:

private:

public:
	CEdit t21;
	CEdit t22;
	CEdit t23;
	CEdit t24;
	CEdit t25;
};
