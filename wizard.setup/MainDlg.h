// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define NAME_DUIWIZARD	_T("DuiEngineWizard")

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP_EX(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_BROWSE2, OnBrowseDuiEngineDir)
		COMMAND_ID_HANDLER(IDC_INSTALL, OnInstall)
		COMMAND_ID_HANDLER(IDC_UNINSTALL, OnUninstall)
		COMMAND_ID_HANDLER(IDC_SETOUTSOFT, OnSetoutsoft)
	END_MSG_MAP()

	enum {VS2005=0,VS2008,VS2010,VS2012};

	//"C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\"
	//"C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\"
	CString GetVSDir(int VSID)
	{
		TCHAR szVName[][30]={
			_T("VS80COMNTOOLS"),
			_T("VS90COMNTOOLS"),
			_T("VS100COMNTOOLS"),
			_T("VS110COMNTOOLS")
		};
		TCHAR szBuf[MAX_PATH+1]={0};
		GetEnvironmentVariable(szVName[VSID],szBuf,MAX_PATH);
		return szBuf;
	}

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);

		CString strDirVs05=GetVSDir(VS2005);
		CString strDirVs08=GetVSDir(VS2008);
		CString strDirVs10=GetVSDir(VS2010);
		CString strDirVs12=GetVSDir(VS2012);
		
		if(strDirVs05.IsEmpty())
			::EnableWindow(GetDlgItem(IDC_VS2005),FALSE);
		else
			::CheckDlgButton(m_hWnd,IDC_VS2005,1);

		if(strDirVs08.IsEmpty())
			::EnableWindow(GetDlgItem(IDC_VS2008),FALSE);
		else
			::CheckDlgButton(m_hWnd,IDC_VS2008,1);

		if(strDirVs10.IsEmpty())
			::EnableWindow(GetDlgItem(IDC_VS2010),FALSE);
		else
			::CheckDlgButton(m_hWnd,IDC_VS2010,1);

		if(strDirVs12.IsEmpty())
			::EnableWindow(GetDlgItem(IDC_VS2012),FALSE);
		else
			::CheckDlgButton(m_hWnd,IDC_VS2012,1);

		TCHAR szPath[MAX_PATH];
		if(GetEnvironmentVariable(_T("DUIENGINEPATH"),szPath,MAX_PATH))
		{
			SetDlgItemText(IDC_DUIENGINEDIR,szPath);
		}else
		{
			GetCurrentDirectory(MAX_PATH,szPath);
			TCHAR *pUp=_tcsrchr(szPath,_T('\\'));
			if(pUp)
			{
				_tcscpy(pUp,_T("\\DuiEngine"));
				if(GetFileAttributes(szPath)!=INVALID_FILE_ATTRIBUTES)
				{
					*pUp=0;
					SetDlgItemText(IDC_DUIENGINEDIR,szPath);
				}
			}
		}

		return TRUE;
	}
	LRESULT OnSetoutsoft(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ShellExecute(0,_T("open"),_T("http://www.setoutsoft.cn"),NULL,NULL,SW_SHOWNORMAL);
		return 0;
	}

	LRESULT OnBrowseDuiEngineDir(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFolderDialog folderDlg;
		if(folderDlg.DoModal()==IDOK)
		{
			SetDlgItemText(IDC_DUIENGINEDIR,folderDlg.GetFolderPath());
		}
		return 0;
	}

	LRESULT OnInstall(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		char toVS[4]={0},empty[4]={0};
		if(IsDlgButtonChecked(IDC_VS2005)) toVS[VS2005]=1;
		if(IsDlgButtonChecked(IDC_VS2008)) toVS[VS2008]=1;
		if(IsDlgButtonChecked(IDC_VS2010)) toVS[VS2010]=1;
		if(IsDlgButtonChecked(IDC_VS2012)) toVS[VS2012]=1;
		
		
		if(memcmp(toVS,empty,4)==0)
		{
			MessageBox(_T("请先指定目标VS"),_T("错误"),MB_OK|MB_ICONSTOP);
			return 0;
		}

		if(GetFileAttributes(_T("DuiEngineWizard.vsdir"))==INVALID_FILE_ATTRIBUTES)
		{
			MessageBox(_T("当前目录下没有找到DuiEngine的向导数据"),_T("错误"),MB_OK|MB_ICONSTOP);
			return 0;
		}
		TCHAR szDuiEngineDir[MAX_PATH]={0};
		int nLen=GetDlgItemText(IDC_DUIENGINEDIR,szDuiEngineDir,MAX_PATH);
		if(szDuiEngineDir[nLen-1]==_T('\\')) szDuiEngineDir[--nLen]=0;

		_tcscat(szDuiEngineDir,_T("\\DuiEngine"));
		if(GetFileAttributes(szDuiEngineDir)==INVALID_FILE_ATTRIBUTES)
		{
			MessageBox(_T("当前目录下没有找到DuiEngine的源代码"),_T("错误"),MB_OK|MB_ICONSTOP);
			return 0;
		}
		szDuiEngineDir[nLen]=0;
		//设置环境变量

		CRegKeyEx reg;
		if(ERROR_SUCCESS==reg.Open(HKEY_LOCAL_MACHINE,_T("System\\CurrentControlSet\\Control\\Session Manager\\Environment"),KEY_SET_VALUE))
		{
			reg.SetStringValue(_T("DUIENGINEPATH"),szDuiEngineDir);
			reg.Close();
		}else
		{
			MessageBox(_T("添加环境变量失败"),_T("错误"),MB_OK|MB_ICONSTOP);
			return 0;
		}

		//准备复制文件
		TCHAR szBuf[1024]={0};
		TCHAR szTo[1024]={0};

		TCHAR *p=szBuf;

		CString str=NAME_DUIWIZARD;
		str=CString(NAME_DUIWIZARD)+_T(".ico");
		_tcscpy(p,str);
		p+=str.GetLength()+1;
		str=CString(NAME_DUIWIZARD)+_T(".vsdir");
		_tcscpy(p,str);
		p+=str.GetLength()+1;
		str=CString(NAME_DUIWIZARD);
		_tcscpy(p,str);
		p+=str.GetLength()+1;

		TCHAR *pEnd=p;

		TCHAR szVSName[][30]={
			_T("VS2005"),
			_T("VS2008"),
			_T("VS2010"),
			_T("VS2012")
		};

		TCHAR szVSZ[][30]=
		{
			_T("DuiEngineWizard2005.vsz"),
			_T("DuiEngineWizard2008.vsz"),
			_T("DuiEngineWizard2010.vsz"),
			_T("DuiEngineWizard2012.vsz")
		};
		TCHAR szScript[][50]=
		{
			_T("scripts\\vs2008\\default.js"),
			_T("scripts\\vs2008\\default.js"),
			_T("scripts\\vs2012\\default.js"),
			_T("scripts\\vs2012\\default.js"),
		};

		for(int i=0;i<4;i++)
		{
			if(!toVS[i]) continue;
			p=pEnd;
			str=szVSZ[i];
			_tcscpy(p,str);
			p+=str.GetLength()+1;
			*p=0;//double null

			CString strDir=GetVSDir(VS2005+i);

			if(strDir.IsEmpty()) continue;
			int idx=strDir.Find(_T("Common7\\Tools"));
			if(idx==-1) continue;
			strDir=strDir.Left(idx)+_T("VC\\vcprojects\\");

			_tcscpy(szTo,strDir);
			szTo[strDir.GetLength()+1]=0;//double null
			
			SHFILEOPSTRUCT shfo;
			shfo.pFrom=szBuf;
			shfo.pTo=szTo;
			shfo.wFunc=FO_COPY;
			shfo.fFlags=FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION;

			BOOL bOK = 0==SHFileOperation(&shfo);

			if(bOK)
			{
				//重命名
				CString strFrom=strDir+szVSZ[i];
				_tcscpy(szBuf,strFrom);
				szBuf[strFrom.GetLength()+1]=0;//double null
				CString strTo=strDir+_T("DuiEngineWizard.vsz");
				_tcscpy(szTo,strTo);
				szTo[strTo.GetLength()+1]=0;//double null
				shfo.wFunc=FO_RENAME;
				bOK= 0==SHFileOperation(&shfo);
				if(bOK)
				{
					//复制脚本
					_tcscpy(szBuf,szScript[i]);
					szBuf[_tcslen(szBuf)+1]=0;//double null;
					strTo=strDir+_T("DuiEngineWizard\\Scripts\\2052");
					_tcscpy(szTo,strTo);
					szTo[strTo.GetLength()+1]=0;//double null
					shfo.wFunc=FO_COPY;
					bOK= 0==SHFileOperation(&shfo);

				}
			}
			_stprintf(szBuf,_T("为%s安装DuiEngine向导:%s"),szVSName[i],bOK?_T("成功"):_T("失败"));
			::SendMessage(GetDlgItem(IDC_LOG),LB_ADDSTRING,0,(LPARAM)szBuf);
		}
		return 0;
	}

	LRESULT OnUninstall(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		TCHAR szCurDir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurDir);

		TCHAR szVSName[][30]={
			_T("VS2005"),
			_T("VS2008"),
			_T("VS2010"),
			_T("VS2012")
		};

		for(int i=IDC_VS2005;i<=IDC_VS2012;i++)
		{
			if(!IsDlgButtonChecked(i)) continue;
			CString strDir=GetVSDir(i-IDC_VS2005);
			if(strDir.IsEmpty()) continue;
			int idx=strDir.Find(_T("Common7\\Tools"));
			if(idx==-1) continue;
			strDir=strDir.Left(idx)+_T("VC\\vcprojects\\");
			
			SetCurrentDirectory(strDir);

			TCHAR szBuf[1024]={0};
			TCHAR *p=szBuf;
			CString str;
			str=CString(NAME_DUIWIZARD)+_T(".ico");
			_tcscpy(p,str);
			p+=str.GetLength()+1;
			str=CString(NAME_DUIWIZARD)+_T(".vsdir");
			_tcscpy(p,str);
			p+=str.GetLength()+1;
			str=CString(NAME_DUIWIZARD)+_T(".vsz");
			_tcscpy(p,str);
			p+=str.GetLength()+1;

			str=CString(NAME_DUIWIZARD);
			_tcscpy(p,str);
			p+=str.GetLength()+1;

			*p=0;

			SHFILEOPSTRUCT shfo;
			shfo.pFrom=szBuf;
			shfo.pTo=NULL;
			shfo.wFunc=FO_DELETE;
			shfo.fFlags=FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION;

			BOOL bOK= 0==SHFileOperation(&shfo);
			
			_stprintf(szBuf,_T("从%s中卸载DuiEngine向导%s"),szVSName[i-IDC_VS2005],bOK?_T("成功"):_T("失败"));
			::SendMessage(GetDlgItem(IDC_LOG),LB_ADDSTRING,0,(LPARAM)szBuf);
		}
		SetCurrentDirectory(szCurDir);

		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};
