#pragma once


// about 对话框

class about : public CDialogEx
{
	DECLARE_DYNAMIC(about)

public:
	about(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~about();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit tabout;
};
