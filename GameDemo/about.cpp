// about.cpp: 实现文件
//

#include "pch.h"
#include "GameDemo.h"
#include "about.h"
#include "afxdialogex.h"


// about 对话框

IMPLEMENT_DYNAMIC(about, CDialogEx)

about::about(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

about::~about()
{
}

void about::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, tabout);
}


BEGIN_MESSAGE_MAP(about, CDialogEx)
END_MESSAGE_MAP()


// about 消息处理程序
BOOL about::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont m_editFont;
	m_editFont.CreatePointFont(180, _T("黑体"));
	tabout.SetFont(&m_editFont);
	UpdateData(false);
	tabout.SetWindowTextW(_T("大富翁软件\r\n制作人：李嘉祺\r\n个人联机服务器地址：www.jiqili.xyz\r\n\r\n\r\n2048小游戏\r\n制作人：黄凌玉 李根安"));
	return TRUE;
}


