#include "stdafx.h"
#include "progress.h"
#include "tlhelp32.h"

bool CProgress::OpenProgress( CString strPathName )
{
	STARTUPINFO si; 
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) ); 
	si.cb = sizeof(si); 
	ZeroMemory( &pi, sizeof(pi) );

	// Start the child process. 
	if( !CreateProcess( strPathName,   // No module name (use command line). 
		NULL, // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure. 
		&pi )             // Pointer to PROCESS_INFORMATION structure. 
		) 
	{ 
		return false; 
	}
	
	//等待进程结束
	::WaitForSingleObject(pi.hProcess,INFINITE);

	return true;
}

void CProgress::CloseProgress( CString strName )
{
	HANDLE handle; //定义CreateToolhelp32Snapshot系统快照句柄 
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 *info; 
	info = new PROCESSENTRY32; 
	info->dwSize = sizeof(PROCESSENTRY32); 

	Process32First(handle, info); 
	while(Process32Next(handle, info) != FALSE) 
	{   
		CString strTmp = info->szExeFile;//if(strcmp(c, info->szExeFile) == 0 )   
		if (strName.CompareNoCase(strTmp) == 0 )   
		{      
			HANDLE handleTmp = OpenProcess(PROCESS_TERMINATE, FALSE, info->th32ProcessID); 
			//结束进程    
			TerminateProcess(handleTmp, 0); 
			CloseHandle(handleTmp);
		}   
	}
	delete info;

	CloseHandle(handle);
}

DWORD CProgress::GetProcessidFromName( CString strName )
{
	PROCESSENTRY32 pe;      
	DWORD id=0;      
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize=sizeof(PROCESSENTRY32);      
	if(!Process32First(hSnapshot,&pe))
	{
		return 0;      
	}

	pe.dwSize=sizeof(PROCESSENTRY32);      
	while(Process32Next(hSnapshot,&pe) != FALSE)      
	{
		CString strTmp = pe.szExeFile;
		if (strName.CompareNoCase(strTmp) == 0)
		{
			id=pe.th32ProcessID;      
			break;     
		}
	}      
	CloseHandle(hSnapshot);      
	return id;      
}

bool CProgress::IsProgressRunning( CString strName )
{
	DWORD dwID = GetProcessidFromName(strName);
	if (dwID != 0)
	{
		return true;
	}
	return false;
}
