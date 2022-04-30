
// FloatConvDlg.h: 头文件
//

#pragma once


// CFloatConvDlg 对话框
class CFloatConvDlg : public CDialogEx
{
// 构造
public:
	CFloatConvDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLOATCONV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void SetDefVal();
	afx_msg void OnBnClickedOk1();
	CComboBox ComboBox_Type;
	CEdit CEdit_Input;
	CEdit CEdit_Result;
};

#define HEXTOFLOAT 0
#define FLOATTOHEX 1
