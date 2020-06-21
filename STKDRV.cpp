// STKDRV.cpp: implementation of the CSTKDRV class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "STKDRV.h"
#include "GetSetReg.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSTKDRV::CSTKDRV()
{
	m_pfnStock_Init = NULL;
	m_pfnStock_Quit = NULL;
	m_pfnSetupReceiver = NULL;
	m_pfnGetStockDrvInfo = NULL;

	m_pfnAskStockDay = NULL;
	m_pfnAskStockMn5 = NULL;
	m_pfnAskStockBase = NULL;
	m_pfnAskStockNews = NULL;
	m_pfnAskStockHalt = NULL;
	m_pfnAskStockMin = NULL;
	m_pfnAskStockPRP = NULL;
	m_pfnAskStockPwr = NULL;
	m_pfnAskStockFin = NULL;

	m_hSTKDrv = NULL;

	GetAdress();
}

CSTKDRV::~CSTKDRV()
{
	if( m_hSTKDrv )  
	{
		FreeLibrary(m_hSTKDrv);
		m_hSTKDrv = NULL;
	}
}

void CSTKDRV::GetAdress()
{
	//在这里先通过注册表查找驱动DLL文件的位置并装载，如果注册表中没有找到
	//那么在本地当前路径下查找驱动DLL
	GetSetReg reg;
	char ch[512];
	DWORD ncb = sizeof(ch);
	DWORD typ = REG_SZ;
	if(reg.GetValue ("software\\stockdrv","Driver",typ,(unsigned char *)ch,ncb) == ERROR_SUCCESS)
	{
		ch[511] = 0;
		m_hSTKDrv = LoadLibrary(ch);
	}
	else
	{
		CFileFind flfd;
		CString m_CurrentWorkDirectory;
 		::GetCurrentDirectory(MAX_PATH,m_CurrentWorkDirectory.GetBuffer(MAX_PATH));
		m_CurrentWorkDirectory.ReleaseBuffer();
		m_CurrentWorkDirectory.TrimRight ("\\");
		m_CurrentWorkDirectory.TrimRight ("/");
		m_CurrentWorkDirectory+="\\";
		if(flfd.FindFile (m_CurrentWorkDirectory+"StockDrv.dll" ))
			m_hSTKDrv = LoadLibrary(m_CurrentWorkDirectory+"StockDrv.dll");
	}
	//m_hSTKDrv = LoadLibrary( "StockDrv.DLL" );
	if( !m_hSTKDrv ) 
		return;
	m_pfnStock_Init = \
		    (int (WINAPI *)(HWND,UINT,int)) GetProcAddress(m_hSTKDrv,"Stock_Init");
	m_pfnStock_Quit = \
			(int (WINAPI *)(HWND)) GetProcAddress(m_hSTKDrv,"Stock_Quit");
	m_pfnSetupReceiver = \
			(int	(WINAPI *)(BOOL))GetProcAddress(m_hSTKDrv,"SetupReceiver");
	m_pfnGetStockDrvInfo = \
			(DWORD (WINAPI *)(int,void * ))GetProcAddress(m_hSTKDrv,"GetStockDrvInfo");


	m_pfnAskStockDay = \
		    (int (WINAPI *)(char*,int)) GetProcAddress(m_hSTKDrv,"AskStockDay");

	m_pfnAskStockMn5 = \
		    (int (WINAPI *)(char*,int)) GetProcAddress(m_hSTKDrv,"AskStockMn5");

	m_pfnAskStockBase = \
		    (int (WINAPI *)(char*)) GetProcAddress(m_hSTKDrv,"AskStockBase");

	m_pfnAskStockNews = \
		    (int (WINAPI *)(void)) GetProcAddress(m_hSTKDrv,"AskStockNews");

	m_pfnAskStockHalt = \
		    (int (WINAPI *)(void)) GetProcAddress(m_hSTKDrv,"AskStockHalt");

	m_pfnAskStockMin = \
		    (int (WINAPI *)(char*)) GetProcAddress(m_hSTKDrv,"AskStockMin");

	m_pfnAskStockPRP = \
		    (int (WINAPI *)(char*)) GetProcAddress(m_hSTKDrv,"AskStockPRP");

	m_pfnAskStockPwr = \
		    (int (WINAPI *)(void)) GetProcAddress(m_hSTKDrv,"AskStockPwr");

	m_pfnAskStockFin = \
		    (int (WINAPI *)(void)) GetProcAddress(m_hSTKDrv,"AskStockFin");

}

int CSTKDRV::Stock_Init(HWND hWnd, UINT uMsg, int nWorkMode)
{
	if( !m_pfnStock_Init )
		return -1;
	 return( (*m_pfnStock_Init)(hWnd,uMsg,nWorkMode));
}

int CSTKDRV::Stock_Quit(HWND hWnd)
{
	if( !m_pfnStock_Quit )
		return -1;
	return( (*m_pfnStock_Quit)(hWnd));
}


int CSTKDRV::SetupReceiver(BOOL bSetup)
{
	if( !m_pfnSetupReceiver )
		return -1;
	return( (*m_pfnSetupReceiver)(bSetup));
}

DWORD CSTKDRV::GetStockDrvInfo(int nInfo, void *pBuf)
{
	if( !m_pfnGetStockDrvInfo ) 
		return 0;
	return( (*m_pfnGetStockDrvInfo)(nInfo,pBuf));
}


int CSTKDRV::AskStockDay(char*  pszStockCode,int nTimePeriod)
{
	if( !m_pfnAskStockDay )
		return -1;
	 return( (*m_pfnAskStockDay)(pszStockCode,nTimePeriod));
}

int CSTKDRV::AskStockMn5(char*  pszStockCode,int nTimePeriod)
{
	if( !m_pfnAskStockMn5 )
		return -1;
	 return( (*m_pfnAskStockMn5)(pszStockCode,nTimePeriod));
}

int CSTKDRV::AskStockBase(char*  pszStockCode)
{
	if( !m_pfnAskStockBase )
		return -1;
	 return( (*m_pfnAskStockBase)(pszStockCode));
}

int CSTKDRV::AskStockNews()
{
	if( !m_pfnAskStockNews )
		return -1;
	 return( (*m_pfnAskStockNews)());
}

int CSTKDRV::AskStockHalt()
{
	if( !m_pfnAskStockHalt )
		return -1;
	 return( (*m_pfnAskStockHalt)());
}

int CSTKDRV::AskStockMin(char*  pszStockCode)
{
	if( !m_pfnAskStockMin )
		return -1;
	 return( (*m_pfnAskStockMin)(pszStockCode));
}

int CSTKDRV::AskStockPRP(char*  pszStockCode)
{
	if( !m_pfnAskStockPRP )
		return -1;
	 return( (*m_pfnAskStockPRP)(pszStockCode));
}

int CSTKDRV::AskStockPwr()
{
	if( !m_pfnAskStockPwr )
		return -1;
	 return( (*m_pfnAskStockPwr)());
}

int CSTKDRV::AskStockFin()
{
	if( !m_pfnAskStockFin )
		return -1;
	 return( (*m_pfnAskStockFin)());
}
