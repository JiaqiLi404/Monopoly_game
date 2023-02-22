// C2048.cpp: 实现文件
//

#include "pch.h"
#include "GameDemo.h"
#include "C2048.h"
#include "afxdialogex.h"
#include <time.h>
#include "afxdialogex.h"
#include"GameDemoDlg.h"
int a[5][5];
// C2048 对话框
IMPLEMENT_DYNAMIC(C2048, CDialogEx)

C2048::C2048(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

C2048::~C2048()
{
}

void C2048::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT19, t2);
	DDX_Control(pDX, IDC_EDIT1, t1);
	DDX_Control(pDX, IDC_EDIT16, t3);
	DDX_Control(pDX, IDC_EDIT8, t4);
	DDX_Control(pDX, IDC_EDIT17, t5);
	DDX_Control(pDX, IDC_EDIT20, t6);
	DDX_Control(pDX, IDC_EDIT21, t7);
	DDX_Control(pDX, IDC_EDIT12, t8);
	DDX_Control(pDX, IDC_EDIT22, t9);
	DDX_Control(pDX, IDC_EDIT23, t10);
	DDX_Control(pDX, IDC_EDIT4, t11);
	DDX_Control(pDX, IDC_EDIT24, t12);
	DDX_Control(pDX, IDC_EDIT25, t13);
	DDX_Control(pDX, IDC_EDIT26, t14);
	DDX_Control(pDX, IDC_EDIT9, t15);
	DDX_Control(pDX, IDC_EDIT27, t16);

	DDX_Control(pDX, IDC_BUTTON6, bx);
}


BEGIN_MESSAGE_MAP(C2048, CDialogEx)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON6, &C2048::OnBnClickedButton6)
END_MESSAGE_MAP()

// C2048 消息处理程序

void C2048::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// C2048 消息处理程序


	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
// C2048 消息处理程序
BOOL C2048::OnInitDialog()
{

	int i, j, k, H, L, l = 1;
	for (i = 0; i <= 4; i++)
		for (j = 0; j <= 4; j++)
			a[i][j] = 0;
	srand((unsigned)time(0));
	H = rand() % 3 + 0;
	L = rand() % 3 + 0;
	a[H][L] = 2;
	XS();
	UpdateData(false);
	bx.SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}




BOOL C2048::PreTranslateMessage(MSG* pMsg)
{

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case 65:
			//按下A
			left();
			XS();
			UpdateData(false);
			Initialize();
			return TRUE;
			break;

		case 83:
			//按下S
			down();
			XS();
			UpdateData(false);
			Initialize();
			return TRUE;
			break;
		case 87:
			//按下W
			up();
			XS();
			UpdateData(false);
			Initialize();
			return TRUE;
			break;
		case 68:
			//按下D
			right();
			XS();
			UpdateData(false);
			Initialize();
			return TRUE;
			break;
		case 80:
			//按下P
            mon = mon + 1000;
			CDialog::OnCancel(); //取消按钮被按下
			return TRUE;
			break;
			
		default:
			return TRUE;
			break;
		}

	}





	return CDialog::PreTranslateMessage(pMsg);
}



void C2048::up()
{
	JC();
	//在更新完图像后在判断游戏是否结束 
	int i, j, q, L = 0;
	int nh, nl;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 3; j++)
			if (a[j][i] == 0 || (a[j][i] != 0 && a[j][i] == a[j + 1][i]))
			{
				L = 1;
				break;
			}
		if (L)
			break;
	}
	if (L == 0)
		return;
	/*
	以上是防止死机,判断执行条件
	*/


	for (i = 0; i <= 3; i++)                 //列 
		for (j = 2; j >= 0; j--)             //行 
			if (a[j][i] == 0)
			{
				for (q = j; q < 3; q++)
				{
					a[q][i] = a[q + 1][i];
					a[q + 1][i] = 0;
				}
			}

	/*
		以上是将所有除了0的数字全部向上靠拢
	*/
	for (i = 0; i <= 3; i++)                //列 
		for (j = 0; j <= 2; j++)               //行 
			if (a[j][i] != 0 && a[j][i] == a[j + 1][i])
			{
				a[j][i] *= 2;
				for (q = j + 1; q <= 3; q++)
				{
					a[q][i] = a[q + 1][i];
					a[q + 1][i] = 0;
				}
			}
	/*
		以上是将除了0而且上下相同的数字合并，并且将下面剩余的数字向上靠拢。
	*/
	do
	{
		nh = rand() % 4 + 0;
		nl = rand() % 4 + 0;
	} while (a[nh][nl] != 0);        //如果新行和新列的值不为0；就重新找新行新列 
	a[nh][nl] = 2;
}




void C2048::left()
{
	JC();
	int i, j, q, L = 0;
	int nh, nl;
	for (i = 0; i <= 3; i++)       //行 
	{
		for (j = 0; j <= 3; j++)        //列 
			if (a[i][j] == 0 || (a[i][j] != 0 && a[i][j] == a[i][j + 1]))
			{
				L = 1;
				break;
			}
		if (L)
			break;
	}
	if (L == 0)
		return;

	/*
	防止死机
	*/



	for (i = 0; i <= 3; i++)                 //行 
		for (j = 3; j >= 0; j--)             //列 
			if (a[i][j] == 0)
				for (q = j; q < 3; q++)
				{
					a[i][q] = a[i][q + 1];
					a[i][q + 1] = 0;
				}
	/*
		以上是将所有除了0的数字全部向左靠拢
	*/
	for (i = 0; i <= 3; i++)                //行 
		for (j = 0; j <= 3; j++)               //列 
			if (a[i][j] != 0 && a[i][j] == a[i][j + 1])
			{
				a[i][j] *= 2;
				for (q = j + 1; q <= 3; q++)
				{
					a[i][q] = a[i][q + 1];
					a[i][q + 1] = 0;
				}
			}
	/*
		以上是将除了0而且左右相同的数字合并，并且将下面剩余的数字向左靠拢。
	*/
	do
	{
		nh = rand() % 4 + 0;
		nl = rand() % 4 + 0;
	} while (a[nh][nl] != 0);        //如果新行和新列的值不为0；就重新找新行新列 
	a[nh][nl] = 2;
}




void C2048::down()
{
	JC();
	int i, j, q, L = 0;
	int nh, nl;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 3; j++)
			if (a[j][i] == 0 || (a[j][i] != 0 && a[j][i] == a[j + 1][i]))
			{
				L = 1;
				break;
			}
		if (L)
			break;
	}
	if (L == 0)
		return;
	/*
	以上是防止死机
	*/


	for (i = 0; i <= 3; i++)        //列 
		for (j = 1; j <= 3; j++)         //行 
			if (a[j][i] == 0)
				for (q = j; q > 0; q--)
				{
					a[q][i] = a[q - 1][i];
					a[q - 1][i] = 0;
				}
	/*
		以上是将所有除了0的数字全部向下靠拢
	*/
	for (i = 0; i <= 3; i++)        //列 
		for (j = 3; j > 0; j--)     //行
			if (a[j][i] != 0 && a[j][i] == a[j - 1][i])
			{
				a[j][i] *= 2;
				for (q = j - 1; q >= 0; q--)
				{
					a[q][i] = a[q - 1][i];
					a[q - 1][i] = 0;
				}
			}
	/*
		以上是将除了0而且上下相同的数字合并，并且将下面剩余的数字向下靠拢。
	*/
	do
	{
		nh = rand() % 4 + 0;
		nl = rand() % 4 + 0;
	} while (a[nh][nl] != 0);        //如果新行和新列的值不为0；就重新找新行新列 
	a[nh][nl] = 2;
}




void C2048::right()
{
	int i, j, q, L = 0;;
	int nh, nl;
	for (i = 0; i <= 3; i++)       //行 
	{
		for (j = 0; j <= 3; j++)        //列 
			if (a[i][j] == 0 || (a[i][j] != 0 && a[i][j] == a[i][j + 1]))
			{
				L = 1;
				break;
			}
		if (L)
			break;
	}
	if (L == 0)
		return;

	/*
	防止死机
	*/
	for (i = 0; i < 4; i++)       //行 
		for (j = 1; j <= 3; j++)         //列 
			if (a[i][j] == 0)
				for (q = j; q > 0; q--)
				{
					a[i][q] = a[i][q - 1];
					a[i][q - 1] = 0;
				}

	/*
		以上是将所有除了0的数字全部向右靠拢
	*/
	for (i = 0; i < 4; i++)      //行 
		for (j = 3; j > 0; j--)            //列 
			if (a[i][j] != 0 && a[i][j] == a[i][j - 1])
			{
				a[i][j] *= 2;
				for (q = j - 1; q >= 0; q--)
				{
					a[i][q] = a[i][q - 1];
					a[i][q - 1] = 0;
				}
			}
	/*
		以上是将除了0而且上下相同的数字合并，并且将下面剩余的数字向右靠拢。
	*/
	do
	{
		nh = rand() % 4 + 0;
		nl = rand() % 4 + 0;
	} while (a[nh][nl] != 0);        //如果新行和新列的值不为0；就重新找新行新列 
	a[nh][nl] = 2;
	JC();
}

void C2048::JC()
{
	int m, i, j, I = 1, L = 0;
	for (i = 0; i <= 3; i++)
		for (j = 0; j <= 3; j++)
			if (a[i][j] == 0)
				return;



	for (i = 0; i <= 3; i++)          //列
		for (j = 0; j <= 2; j++)         //行
			if (a[j][i] == a[j + 1][i])                   //等于的话游戏可以继续 
			{
				return;
			}

	for (i = 0; i <= 3; i++)          //行
		for (j = 0; j <= 2; j++)       //列
			if (a[i][j] == a[i][j + 1])
			{
				return;
			}
	mon = -10000;
	CDialog::OnCancel(); //取消按钮被按下
}
void C2048::XS() {
	UpdateData(false);
	CString c;
	static CFont font;
	font.DeleteObject();
	font.CreatePointFont(120, _T("黑体"));
	t1.SetFont(&font);//设置字体
	t2.SetFont(&font);//设置字体
	t3.SetFont(&font);//设置字体
	t4.SetFont(&font);//设置字体
	t5.SetFont(&font);//设置字体
	t6.SetFont(&font);//设置字体
	t7.SetFont(&font);//设置字体
	t8.SetFont(&font);//设置字体
	t9.SetFont(&font);//设置字体
	t10.SetFont(&font);//设置字体
	t11.SetFont(&font);//设置字体
	t12.SetFont(&font);//设置字体
	t13.SetFont(&font);//设置字体
	t14.SetFont(&font);//设置字体
	t15.SetFont(&font);//设置字体
	t16.SetFont(&font);//设置字体
	if (a[0][0] != 0) { c.Format(_T("%d"), a[0][0]); }
	else { c.Format(_T(" ")); }
	t1.SetWindowTextW(c);
	if (a[0][1] != 0) { c.Format(_T("%d"), a[0][1]); }
	else { c.Format(_T(" ")); }
	t2.SetWindowTextW(c);
	if (a[0][2] != 0) { c.Format(_T("%d"), a[0][2]); }
	else { c.Format(_T(" ")); }
	t3.SetWindowTextW(c);
	if (a[0][3] != 0) { c.Format(_T("%d"), a[0][3]); }
	else { c.Format(_T(" ")); }
	t4.SetWindowTextW(c);
	if (a[1][0] != 0) { c.Format(_T("%d"), a[1][0]); }
	else { c.Format(_T(" ")); }
	t5.SetWindowTextW(c);
	if (a[1][1] != 0) { c.Format(_T("%d"), a[1][1]); }
	else { c.Format(_T(" ")); }
	t6.SetWindowTextW(c);
	if (a[1][2] != 0) { c.Format(_T("%d"), a[1][2]); }
	else { c.Format(_T(" ")); }
	t7.SetWindowTextW(c);
	if (a[1][3] != 0) { c.Format(_T("%d"), a[1][3]); }
	else { c.Format(_T(" ")); }
	t8.SetWindowTextW(c);
	if (a[2][0] != 0) { c.Format(_T("%d"), a[2][0]); }
	else { c.Format(_T(" ")); }
	t9.SetWindowTextW(c);
	if (a[2][1] != 0) { c.Format(_T("%d"), a[2][1]); }
	else { c.Format(_T(" ")); }
	t10.SetWindowTextW(c);
	if (a[2][2] != 0) { c.Format(_T("%d"), a[2][2]); }
	else { c.Format(_T(" ")); }
	t11.SetWindowTextW(c);
	if (a[2][3] != 0) { c.Format(_T("%d"), a[2][3]); }
	else { c.Format(_T(" ")); }
	t12.SetWindowTextW(c);
	if (a[3][0] != 0) { c.Format(_T("%d"), a[3][0]); }
	else { c.Format(_T(" ")); }
	t13.SetWindowTextW(c);
	if (a[3][1] != 0) { c.Format(_T("%d"), a[3][1]); }
	else { c.Format(_T(" ")); }
	t14.SetWindowTextW(c);
	if (a[3][2] != 0) { c.Format(_T("%d"), a[3][2]); }
	else { c.Format(_T(" ")); }
	t15.SetWindowTextW(c);
	if (a[3][3] != 0) { c.Format(_T("%d"), a[3][3]); }
	else { c.Format(_T(" ")); }
	t16.SetWindowTextW(c);
	int i, j;
	for (i = 0; i <= 3; i++)
		for (j = 0; j <= 3; j++)
			if (a[i][j] == 512) {
				mon = mon + 1000;
				CDialog::OnCancel(); //取消按钮被按下
			}

}


void C2048::OnBnClickedButton6()
{
	mon = -10000;
	CDialog::OnCancel(); //取消按钮被按下
}
