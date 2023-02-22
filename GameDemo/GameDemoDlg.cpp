// GameDemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GameDemo.h"
#include "GameDemoDlg.h"
#include "afxdialogex.h"
#include<time.h>
#include "Finally.h"
#include <afxinet.h>
#include<atlconv.h>
#include "afxdialogex.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//变量定义
Finally f;
int mon;
int res;//1通过2不通过 
int loc;
boolean hasLZ;//是否有路障
int BScost;//别墅按揭付款
double sco;//分数
double highestsco;

//icon定义
CGameDemoDlg::CGameDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameDemoDlg::RefreshIndividualControl(UINT uCtlID)
{
	CRect rect;
	GetDlgItem(uCtlID)->GetWindowRect(&rect); //获取控件区域  
	ScreenToClient(&rect); //屏幕区域对客户区域的转换    
	InvalidateRect(rect);//刷新 
}

//高度随机数生产函数
int CGameDemoDlg::getRand()
{
	srand(time(0));
	srand(rand());
	srand(rand());
	return rand();

}

//获取控件到对象
void CGameDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, t2);
	DDX_Control(pDX, IDC_EDIT3, t1);
	DDX_Control(pDX, IDC_EDIT12, t3);
	DDX_Control(pDX, IDC_EDIT8, t4);
	DDX_Control(pDX, IDC_EDIT13, t5);
	DDX_Control(pDX, IDC_EDIT14, t6);
	DDX_Control(pDX, IDC_EDIT15, t7);
	DDX_Control(pDX, IDC_EDIT11, t8);
	DDX_Control(pDX, IDC_EDIT10, t9);
	DDX_Control(pDX, IDC_EDIT6, t10);
	DDX_Control(pDX, IDC_EDIT7, t11);
	DDX_Control(pDX, IDC_EDIT9, t12);
	DDX_Control(pDX, IDC_EDIT5, t13);
	DDX_Control(pDX, IDC_EDIT4, t14);
	DDX_Control(pDX, IDC_BUTTON1, b1);
	DDX_Control(pDX, IDC_EDIT1, t15);
	DDX_Control(pDX, IDC_EDIT16, t16);
	DDX_Control(pDX, IDC_EDIT17, t17);
	DDX_Control(pDX, IDC_BUTTON2, b2);
	DDX_Control(pDX, IDC_BUTTON3, b);
	DDX_Control(pDX, IDC_EDIT18, tonline);
}

//控件事件注册
BEGIN_MESSAGE_MAP(CGameDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CGameDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CGameDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CGameDemoDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CGameDemoDlg 消息处理程序
BOOL CGameDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标
	ShowWindow(SW_MAXIMIZE);         //最大化
	MessageBox(_T("当资产为负数时，你将会被淘汰。\r\n软件使用前请先保证互联网连接哦！"), _T("规则"), MB_OK);
	//设置控件属性
	CFont m_editFont;
	m_editFont.CreatePointFont(180, _T("黑体"));
	b1.SetFont(&m_editFont);
	t1.SetFont(&m_editFont);
	t2.SetFont(&m_editFont);
	t3.SetFont(&m_editFont);
	t4.SetFont(&m_editFont);
	t5.SetFont(&m_editFont);
	t6.SetFont(&m_editFont);
	t7.SetFont(&m_editFont);
	t8.SetFont(&m_editFont);
	t9.SetFont(&m_editFont);
	t10.SetFont(&m_editFont);
	t11.SetFont(&m_editFont);
	t12.SetFont(&m_editFont);
	t13.SetFont(&m_editFont);
	t14.SetFont(&m_editFont);
	t15.SetFont(&m_editFont);
	t16.SetFont(&m_editFont);
	t1.SetWindowText(_T("起始位置"));
	t2.SetWindowText(_T("超级别墅：\r\n可以选择获得资产5000万\r\n随后每天减少资产500万"));
	t3.SetWindowText(_T("地主抢劫：\r\n资产减少800万"));
	t4.SetWindowText(_T("路障：\r\n可以选择花费700万随后每次\r\n经过获得400万"));
	t5.SetWindowText(_T("银行：\r\n获得资产800万"));
	t6.SetWindowText(_T("盲僧大招：\r\n后退n格，n在0-6中"));
	t7.SetWindowText(_T("打开了淘宝APP：\r\n资产减少500万"));
	t8.SetWindowText(_T("彩票：\r\n可以选择随机资产变动一次，\r\n资产变动最大值为1000万"));
	t9.SetWindowText(_T("赌博：\r\n资产随机变动，有可能直接淘汰\r\n（直接被吸引，不能选择是否\r\n参加）"));
	t10.SetWindowText(_T("赚钱之道：\r\n获得资产1000万"));
	t11.SetWindowText(_T("学校：\r\n做一道2048到512，成功则资产加1000万\r\n否则直接失败"));
	t12.SetWindowText(_T("天降正义：\r\n资产清零"));
	t13.SetWindowText(_T("交警查岗：\r\n再投一次骰子"));
	t14.SetWindowText(_T("桃花运：\r\n获得了一个女朋友，资产减半"));
	b2.SetWindowText(_T("关于(v0.1)"));
	t15.SetWindowText(_T("你的资产：1000万"));
	b1.SetWindowText(_T("投骰子"));
	b1.SetFocus();

	//初始化变量
	hasLZ = false;
	mon = 1000;
	loc = 0;
	BScost = 0;
	sco = 0;

	//通过 http GET 协议来获取并保存文件
	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
	CString c;
	c.Format(TEXT("/Game/Game?sco=-1"));                        //sco=-1表示获取当前最高分
	CHttpConnection* pConnection = session.GetHttpConnection(TEXT("www.jiqili.xyz"), (INTERNET_PORT)80);
	CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,
		c);
	CString szHeaders = L"Accept: *,*/*\r\n";

	pFile->AddRequestHeaders(szHeaders);
	pFile->SendRequest();
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);

	if (dwRet != HTTP_STATUS_OK)
	{
		CString errText;
		errText.Format(L"POST出错，错误码：%d", dwRet);
		AfxMessageBox(errText);
	}
	else
	{
		int len = pFile->GetLength();
		char buf[20] = "";
		int numread;
		while ((numread = pFile->Read(buf, sizeof(buf) - 1)) > 0)
		{
			buf[numread] = '\0';
		}
		USES_CONVERSION;
		CString highest;
		highest = A2T(buf);
		highestsco = _ttof(highest);
		highest = _T("当前联机的全球最高分数为：") + highest;
		tonline.SetWindowTextW(highest);
	}
	session.Close();
	pFile->Close();
	delete pFile;


	return FALSE;
	//return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGameDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




//重写控件重绘函数，实现控件的颜色等属性的改变
HBRUSH CGameDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (loc == 13 && pWnd->GetDlgCtrlID() == IDC_EDIT2) {// IDC_Display为所选文本框ID     
		pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
		pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
		 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
	}
	else
		if (loc == 12 && pWnd->GetDlgCtrlID() == IDC_EDIT12) {// IDC_Display为所选文本框ID     
			pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
			pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
			 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
		}
		else
			if (loc == 11 && pWnd->GetDlgCtrlID() == IDC_EDIT8) {// IDC_Display为所选文本框ID     
				pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
				pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
				 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
			}
			else
				if (loc == 10 && pWnd->GetDlgCtrlID() == IDC_EDIT13) {// IDC_Display为所选文本框ID     
					pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
					pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
					 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
				}
				else
					if (loc == 9 && pWnd->GetDlgCtrlID() == IDC_EDIT14) {// IDC_Display为所选文本框ID     
						pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
						pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
						 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
					}
					else
						if (loc == 8 && pWnd->GetDlgCtrlID() == IDC_EDIT15) {// IDC_Display为所选文本框ID     
							pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
							pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
							 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
						}
						else
							if (loc == 7 && pWnd->GetDlgCtrlID() == IDC_EDIT11) {// IDC_Display为所选文本框ID     
								pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
								pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
								 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
							}
							else
								if (loc == 6 && pWnd->GetDlgCtrlID() == IDC_EDIT10) {// IDC_Display为所选文本框ID     
									pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
									pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
									 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
								}
								else
									if (loc == 5 && pWnd->GetDlgCtrlID() == IDC_EDIT6) {// IDC_Display为所选文本框ID     
										pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
										pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
										 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
									}
									else
										if (loc == 4 && pWnd->GetDlgCtrlID() == IDC_EDIT7) {// IDC_Display为所选文本框ID     
											pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
											pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
											 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
										}
										else
											if (loc == 3 && pWnd->GetDlgCtrlID() == IDC_EDIT9) {// IDC_Display为所选文本框ID     
												pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
												pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
												 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
											}
											else
												if (loc == 2 && pWnd->GetDlgCtrlID() == IDC_EDIT5) {// IDC_Display为所选文本框ID     
													pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
													pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
													 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
												}
												else
													if (loc == 1 && pWnd->GetDlgCtrlID() == IDC_EDIT4) {// IDC_Display为所选文本框ID     
														pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
														pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
														 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
													}
													else
														if (loc == 0 && pWnd->GetDlgCtrlID() == IDC_EDIT3) {// IDC_Display为所选文本框ID     
															pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
															pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
															 //pDC->SetBkMode(TRANSPARENT);//设置背景透明
														}

	return hbr;
}

//投骰子按钮
void CGameDemoDlg::OnBnClickedButton1()
{
	C2048 school;
	sco = sco + 100;
	int a = (unsigned)(getRand() % (6 - 1 + 1)) + 1;
	CString c;
	c.Format(_T("你投到了%d"), a);
	t16.SetWindowTextW(c);
	loc = (loc + a) % 14;
	Invalidate();
	UpdateData(false);
	switch (loc) {
	case 0:
		c.Format(_T("什么都没变，穷还是那么穷"));
		t17.SetWindowTextW(c);
		break;
	case 1:
		c.Format(_T("恭喜你，获得了一个女朋友，资产减半"));
		t17.SetWindowTextW(c);
		mon = mon / 2;
		break;
	case 2:
		MessageBox(_T("你重新投了一次"), _T("提示"), MB_OK);
		OnBnClickedButton1();
		break;
	case 3:
		c.Format(_T("恭喜你，天降正义，资产充公"));
		t17.SetWindowTextW(c);
		mon = 0;
		break;
	case 4:
		c.Format(_T("你进了学校做了一道2048"));
		t17.SetWindowTextW(c);
		school.DoModal();
		break;
	case 5:
		c.Format(_T("恭喜你，获得资产1000万"));
		t17.SetWindowTextW(c);
		mon = mon + 1000;
		break;
	case 6:
		a = (getRand() % (5000 + 1)) - 1000;
		c.Format(_T("由于参加了赌博，你的资产重新变动了，变成了%d"), a);
		t17.SetWindowTextW(c);
		mon = a;
		break;
	case 7:
		if (IDYES == MessageBox(_T("是否要买一次彩票?"), _T("提示"), MB_YESNO))
		{
			a = (getRand() % (2000 + 1)) - 1000;
			if (a >= 0) {
				c.Format(_T("恭喜你，获得资产%d万"), a);
				t17.SetWindowTextW(c);
				mon = mon + a;
			}
			else {
				c.Format(_T("很可惜，彩票失算了，资产减少%d万"), -a);
				t17.SetWindowTextW(c);
				mon = mon + a;
			}
		}
		else {
			c.Format(_T("什么都没变，穷还是那么穷"));
			t17.SetWindowTextW(c);
		}

		break;
	case 8:
		c.Format(_T("很可惜，你捐了500万给马叔叔"));
		t17.SetWindowTextW(c);
		mon = mon - 500;
		break;
	case 9:
		MessageBox(_T("你被盲僧的大招踢了回去"), _T("提示"), MB_OK);
		loc = loc - 6;
		OnBnClickedButton1();
		break;
	case 10:
		c.Format(_T("恭喜你，获得资产800万"));
		t17.SetWindowTextW(c);
		mon = mon + 800;
		break;
	case 11:
		if (hasLZ) {
			mon = mon + 400;
			c.Format(_T("恭喜你，经过路障获得资产400万"));
			t17.SetWindowTextW(c);
		}
		else {
			if (IDYES == MessageBox(_T("是否要花700万买下路障?此后每经过一次获得400万"), _T("提示"), MB_YESNO)) {
				hasLZ = true;
				mon = mon - 700;
				c.Format(_T("恭喜你，买下了路障，但是资产减700万"));
				t17.SetWindowTextW(c);
			}
			else {
				c.Format(_T("什么都没变，穷还是那么穷"));
				t17.SetWindowTextW(c);
			}
		}
		break;
	case 12:
		c.Format(_T("你遇到了打劫，资产减少800万"));
		t17.SetWindowTextW(c);
		mon = mon - 800;
		break;
	case 13:
		if (BScost == 0) {
			if (IDYES == MessageBox(_T("是否要预付款得到超级别墅？获得5000万并且每次减少500万"), _T("提示"), MB_YESNO)) {
				BScost = 500;
				mon = mon + 5000;
				c.Format(_T("恭喜你，得到了5000万"));
				t17.SetWindowTextW(c);
			}
			else {
				c.Format(_T("你拒绝了购买超级别墅"));
				t17.SetWindowTextW(c);
			}
		}
		else {
			c.Format(_T("你已经有了%d套别墅，是否再买一套？"), BScost / 500);
			if (IDYES == MessageBox(c, _T("提示"), MB_YESNO)) {
				hasLZ = true;
				mon = mon + 5000;
				c.Format(_T("恭喜你，又得到了5000万"));
				t17.SetWindowTextW(c);
			}
			else {
				c.Format(_T("你拒绝了购买超级别墅"));
				t17.SetWindowTextW(c);
			}
		}
		break;
	default:break;
	}
	mon = mon - BScost;
	CString d;
	d.Format(_T("你的资产：%d万\r\n你的分数：%.lf"), mon, sco);
	t15.SetWindowText(d);
	Invalidate();
	UpdateData(false);
	//资产小于0
	if (mon < 0) {
		CString d;
		d.Format(_T("。你的资产变成了%d万,你输了。\r\n最终得分为%.lf"), mon, sco);
		MessageBox(c + d, _T("提示"), MB_OK);

		f.DoModal();
		CString highest;
		highest.Format(_T("%.lf"), highestsco);
		if (highestsco <= sco) {
			MessageBox(_T("你破了目前的全球最高纪录！！！"), _T("恭喜"), MB_OK);
		}
		highest = _T("当前全球最高分数为：") + highest;
		tonline.SetWindowTextW(highest);
		hasLZ = false;
		mon = 1000;
		loc = 0;
		BScost = 0;
		sco = 0;
		t15.SetWindowText(_T("你的资产：1000万"));
		t16.SetWindowText(_T(""));
		t17.SetWindowText(_T(""));


		Invalidate();
		UpdateData(false);
	}
}

void CGameDemoDlg::OnBnClickedButton3()
{
	// 必输后门
	mon = -5000;
	sco += 800;
}


void CGameDemoDlg::OnBnClickedButton4()
{
	// 删除临时文件
	CFile    TempFile;
	TempFile.Remove(_T("1.txt"));
}


void CGameDemoDlg::OnBnClickedButton5()
{
	// 打开分数纪录界面
	f.DoModal();
}


void CGameDemoDlg::OnBnClickedButton2()
{
	// 打开关于界面
	about a;
	a.DoModal();
}

void CGameDemoDlg::OnBnClickedButton6()
{
	//打开2048
	C2048 school;
	school.DoModal();
}
