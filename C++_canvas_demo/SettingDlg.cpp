// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USBHelper.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(const CString &strCustom,const CString &strClass,const CString &strDevice,BOOL bNode /*=false*/,CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_strCustom(strCustom)
	, m_strClass(strClass)
	, m_strDevice(strDevice)
	, m_bNode(bNode)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������


BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if (m_bNode)
	{
		GetDlgItem(IDC_EDIT_CUSTOM)->SetWindowText(m_strCustom);
		GetDlgItem(IDC_EDIT_CLASS)->SetWindowText(m_strClass);
		GetDlgItem(IDC_EDIT_DEVICE)->SetWindowText(m_strDevice);

		GetDlgItem(IDC_EDIT_DEVICE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DEVICE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CUSTOM)->SetWindowText(m_strCustom);
		GetDlgItem(IDC_EDIT_CLASS)->SetWindowText(m_strClass);

		GetDlgItem(IDC_STATIC_DEVICE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DEVICE)->ShowWindow(SW_HIDE);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSettingDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_CUSTOM)->GetWindowText(m_strCustom);
	GetDlgItem(IDC_EDIT_CLASS)->GetWindowText(m_strClass);
	GetDlgItem(IDC_EDIT_DEVICE)->GetWindowText(m_strDevice);
	CDialog::OnOK();
}

void CSettingDlg::GetSettingInfo(CString &strCustom,CString &strClass,CString &strDevice)
{
	strCustom = m_strCustom;
	strClass = m_strClass;
	strDevice = m_strDevice;
}