// STKDRV.h: interface for the CSTKDRV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STKDRV_H__4BE51F0E_A261_11D2_B30C_00C04FCCA334__INCLUDED_)
#define AFX_STKDRV_H__4BE51F0E_A261_11D2_B30C_00C04FCCA334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSTKDRV  
{
public:
	CSTKDRV();
	virtual ~CSTKDRV();
public:
	DWORD GetStockDrvInfo(int nInfo,void * pBuf);
	int SetupReceiver(BOOL bSetup);
	int Stock_Quit(HWND hWnd);
	int Stock_Init(HWND hWnd,UINT uMsg,int nWorkMode);
	int AskStockDay(char*  pszStockCode,int nTimePeriod);
	int AskStockMn5(char*  pszStockCode,int nTimePeriod);
	int AskStockBase(char*  pszStockCode);
	int AskStockNews();
	int AskStockHalt();
	int AskStockMin(char*  pszStockCode);
	int AskStockPRP(char*  pszStockCode);
	int AskStockPwr();
	int AskStockFin();

	int (WINAPI *	m_pfnStock_Init)(HWND hWnd,UINT Msg,int nWorkMode);
	int (WINAPI *	m_pfnStock_Quit)(HWND hWnd);
	int	(WINAPI *	m_pfnSetupReceiver)(BOOL bSetup);
	DWORD (WINAPI * m_pfnGetStockDrvInfo)(int nInfo,void * pBuf);

	int (WINAPI *	m_pfnAskStockDay)(char*  pszStockCode,int nTimePeriod);
	int (WINAPI *	m_pfnAskStockMn5)(char*  pszStockCode,int nTimePeriod);
	int (WINAPI *	m_pfnAskStockBase)(char*  pszStockCode);
	int (WINAPI *	m_pfnAskStockNews)();
	int (WINAPI *	m_pfnAskStockHalt)();
	int (WINAPI *	m_pfnAskStockMin)(char*  pszStockCode);
	int (WINAPI *	m_pfnAskStockPRP)(char*  pszStockCode);
	int (WINAPI *	m_pfnAskStockPwr)();
	int (WINAPI *	m_pfnAskStockFin)();
private:
	void GetAdress();
	HINSTANCE	m_hSTKDrv;
};

#endif // !defined(AFX_STKDRV_H__4BE51F0E_A261_11D2_B30C_00C04FCCA334__INCLUDED_)
