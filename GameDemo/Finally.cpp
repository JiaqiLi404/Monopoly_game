// Finally.cpp: 实现文件
//

#include "pch.h"
#include "GameDemo.h"
#include "Finally.h"
#include "afxdialogex.h"
#include"GameDemoDlg.h"
#include<atlconv.h>
#include <afxinet.h>

// Finally 对话框
int w, t, i, j, k;
IMPLEMENT_DYNAMIC(Finally, CDialogEx)

Finally::Finally(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Finally::~Finally()
{
}
void Finally::RefreshIndividualControl(UINT uCtlID)
{
	CRect rect;
	GetDlgItem(uCtlID)->GetWindowRect(&rect); //获取控件区域  
	ScreenToClient(&rect); //屏幕区域对客户区域的转换    
	InvalidateRect(rect);//刷新 
}
void Finally::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, t21);
	DDX_Control(pDX, IDC_EDIT2, t22);
	DDX_Control(pDX, IDC_EDIT3, t23);
	DDX_Control(pDX, IDC_EDIT4, t24);
	DDX_Control(pDX, IDC_EDIT5, t25);
}
BEGIN_MESSAGE_MAP(Finally, CDialogEx)
END_MESSAGE_MAP()


// Finally 消息处理程序
BOOL Finally::OnInitDialog()
{
	UpdateData(false);

	//以下是本地数据库的操作
	int ws = 0, te;
	char writeBuffer[100] = "";     // 要写入的数据的缓存   
	char readBuffer[100] = "";      // 存放读取数据的缓存   
	double s1 = 0, s2 = 0, s3 = 0;
	// 构造CFile对象，同时以创建和读写的方式打开文件E:\1.txt   
	CFile file(_T("1.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	te = sco;
	while (te != 0) { ws = ws + 1; te = te / 10; }
	te = sco;
	file.Read(readBuffer, 100);
	CString x;
	USES_CONVERSION;
	x = A2T(readBuffer);
	//将要存储的数据格式化
	if (readBuffer[0] == 0) {
		writeBuffer[ws] = 0;
		s1 = sco;
		for (i = ws - 1; i >= 0; i--) {
			writeBuffer[i] = '0' + te % 10;
			te = te / 10;
		}
		// 将数据写入到文件中   
		file.Write(writeBuffer, ws + 1);
		file.Close();
	}
	else {
		// 重新新建文件   
		file.Close();
		CFile file(_T("1.txt"), CFile::modeCreate | CFile::modeReadWrite);
		int idx1 = x.Find(_T(" "), 0);
		int idx2 = x.Find(_T(" "), idx1 + 1);
		if (idx1 == -1) {
			s1 = _ttol(x);
			if (s1 > sco) {
				s2 = sco;
			}
			else {
				s2 = s1;
				s1 = sco;
			}
			x.Format(_T("%.lf %.lf"), s1, s2);
		}
		else if (idx2 == -1) {
			s1 = _ttol(x.Mid(0, idx1));
			s2 = _ttol(x.Mid(idx1 + 1, x.GetLength() - idx1 - 1));
			if (sco > s1) {
				s3 = s2; s2 = s1; s1 = sco;
			}
			else if (sco > s2) {
				s3 = s2; s2 = sco;
			}
			else {
				s3 = sco;
			}
			x.Format(_T("%.lf %.lf %.lf"), s1, s2, s3);
		}
		else {
			s1 = _ttol(x.Mid(0, idx1));
			s2 = _ttol(x.Mid(idx1 + 1, idx2 - idx1 - 1));
			s3 = _ttol(x.Mid(idx2 + 1, x.GetLength() - idx2 - 1));
			if (sco > s1) {
				s3 = s2; s2 = s1; s1 = sco;
			}
			else if (sco > s2) {
				s3 = s2; s2 = sco;
			}
			else if (sco > s3) {
				s3 = sco;
			}
			x.Format(_T("%.lf %.lf %.lf"), s1, s2, s3);
		}
		int i;
		for (i = 0; i < x.GetLength(); i++)
		{
			writeBuffer[i] = x.GetAt(i);
		}
		writeBuffer[i] = 0;
		// 将数据写入到文件中   
		file.Write(writeBuffer, x.GetLength() + 1);
		file.Close();
	}
	t21.SetWindowTextW(_T("最高的三次本地记录为："));
	x.Format(_T("%.lf"), s1);
	t22.SetWindowTextW(x);
	x.Format(_T("%.lf"), s2);
	t23.SetWindowTextW(x);
	x.Format(_T("%.lf"), s3);
	t24.SetWindowTextW(x);
	x.Format(_T("您本次的分数为：%.lf"), sco);
	t25.SetWindowTextW(x);


	//通过 http GET 协议来通知本次分数和最高分
	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
	CString c;
	c.Format(TEXT("/Game/Game?sco=%.0lf"), sco);//将本次分数提交给服务器
	CHttpConnection* pConnection = session.GetHttpConnection(TEXT("www.jiqili.xyz"), (INTERNET_PORT)80);
	CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, c);
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

		//MessageBox(_T("已同步到服务器"), _T("提示"), MB_OK);
	}
	session.Close();
	pFile->Close();
	delete pFile;


	Invalidate();
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}