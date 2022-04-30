
// FloatConvDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FloatConv.h"
#include "FloatConvDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFloatConvDlg 对话框



CFloatConvDlg::CFloatConvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FLOATCONV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFloatConvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ComboBox_Type);
	DDX_Control(pDX, IDC_EDIT1, CEdit_Input);
	DDX_Control(pDX, IDC_EDIT2, CEdit_Result);
}

BEGIN_MESSAGE_MAP(CFloatConvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFloatConvDlg::OnBnClickedOk1)
END_MESSAGE_MAP()


// CFloatConvDlg 消息处理程序

BOOL CFloatConvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetDefVal();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFloatConvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFloatConvDlg::OnPaint()
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
HCURSOR CFloatConvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFloatConvDlg::SetDefVal()
{
	ComboBox_Type.SetCurSel(0);

	return;
}

void CFloatConvDlg::OnBnClickedOk1()
{
	int i = 0;
	int iActionType = 0;
	CHAR szInput[32] = { 0 };
	UCHAR szResult[32] = { 0 };
	UCHAR szHex[4] = {0};
	CString strTemp;
	float fResult = 0.0;

	iActionType = ComboBox_Type.GetCurSel();
	if (HEXTOFLOAT == iActionType)
	{
		if (CEdit_Input.GetWindowTextLengthA() > 8)
		{
			MessageBox("输入字符不能超过8个！");
			return;
		}
	}

	CEdit_Input.GetWindowText(strTemp);
	strncpy(szInput, (char*)(LPCTSTR)(strTemp), sizeof(szInput) -1);
	
	if (HEXTOFLOAT == iActionType)
	{
		for (i = 0; i < 8; i++)
		{
			if (szInput[i] >= 'A' && szInput[i] <= 'F')
			{
				szInput[i] += 32;
			}
		}
		for (i = 0; i < 4; i++)
		{
			if (szInput[(3 - i) * 2] >= 'a' && szInput[(3 - i) * 2] <= 'f')
			{
				szHex[i] = (szInput[(3 - i) * 2] - 'a' + 10) * 16;
			}
			else
			{
				szHex[i] = (szInput[(3 - i) * 2] - '0') * 16;
			}
			if (szInput[(3 - i) * 2 + 1] >= 'a' && szInput[(3 - i) * 2 + 1] <= 'f')
			{
				szHex[i] += (szInput[(3 - i) * 2 + 1] - 'a' + 10);
			}
			else
			{
				szHex[i] += (szInput[(3 - i) * 2 + 1] - '0');
			}
		}
		snprintf((char *)szResult, sizeof(szResult), "%x%x%x%x", szHex[0], szHex[1], szHex[2], szHex[3]);
		//MessageBox((CString)szResult);
		//memcpy(&fResult, szHex, 4);
		fResult = *(float *)szHex;
		snprintf((char*)szResult, sizeof(szResult), "%f", fResult);
	}
	else
	{
		fResult = atof(szInput);
		snprintf((char*)szResult, sizeof(szResult), "%02x%02x%02x%02x", *(((UCHAR *) & fResult) + 3), *(((UCHAR *)&fResult) + 2), *(((UCHAR *)&fResult) + 1), *(((UCHAR *)&fResult) + 0));
	}

	
	CEdit_Result.SetWindowText(CString(szResult));

	return;
}
