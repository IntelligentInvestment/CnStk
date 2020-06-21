// StkDemo.cpp : implementation file
//
//		������Ʊ�������ʾ������ͨ��Э�飩
//	
//	
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StkDemo.h"

#include "StockDrv.H"
#include "STKDRV.H"
#include "CnStkDemo.h"


CSTKDRV		gSTOCKDLL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStkDemo

CStkDemo::CStkDemo()
{
	int i;
	for(i=0; i<StkBufNum; i++){
		m_Stock[i] = _T("��Ʊ: ");
	}
	m_StkPtr = 0;
	m_Min = _T("��ʱ����:");
	m_File = _T("�ļ�:");
	m_bRunFlag = FALSE;
}

CStkDemo::~CStkDemo()
{
}


BEGIN_MESSAGE_MAP(CStkDemo, CWnd)
	//{{AFX_MSG_MAP(CStkDemo)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(My_Msg_StkData,OnStkDataOK)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStkDemo message handlers

typedef struct  tagPOWER_TOTAL_STRUCTEx 
{
	RCV_POWER_STRUCTEx *m_RcvPower;   
	long Power_Count;                   

}POWER_TOTAL_STRUCTEx;


void CStkDemo::OnPaint() 
{
	int i;
	int k;
	int High;
	int y;
	TEXTMETRIC tm;
	char * pTitle = "  ����     ��  ��      ����     ��     ����     ���     ���     �ɽ���   �ɽ���";
	CPaintDC dc(this); // device context for painting
	dc.GetTextMetrics(&tm);
	High = tm.tmHeight + 3;
	k = m_StkPtr;
	y = 1;
	dc.TextOut(1,y,pTitle,strlen(pTitle));
	y += High;
	for(i=0; i<StkBufNum; i++)
	{
		k = k % StkBufNum;
		dc.TextOut(1,y,m_Stock[k],m_Stock[k].GetLength());
		y += High;
		k ++;
	}
	y += High;
	dc.TextOut(1,y,m_Min,m_Min.GetLength());
	y += High;
	dc.TextOut(1,y,m_File,m_File.GetLength());
}

// ��������
LONG CStkDemo::OnStkDataOK(
		UINT wFileType,				// �ļ�����, �μ� StockDrv.H
		LONG lPara)					
{
	int i,j;
	long day;
	float open,high,low,close,vol,amount;
	long m_FileLong;
	FILE *fp;
	CString m_FileName;
	CString test;

	PBYTE pFileBuf = NULL;
	RCV_DATA *	pHeader;

	pHeader = (RCV_DATA *) lPara;

	RCV_FENBI * pFenBi;
	HLMarketType *pMarketTableHead;
	//���ڴ����������������,���齫���ݱ���,����һ�̵߳�����������������Ϻ�
	//�Ż�������һ������  

	switch( wFileType )
	{
		case RCV_REPORT:
			{
				//��ʼ�������Լ������յ�ʵʱ���鶼��������ط�����
				int nBufSize = pHeader->m_pReportV3[0].m_cbSize;
				PBYTE pBaseBuf = (PBYTE)&pHeader->m_pReportV3[0];
				for(i=0; i<pHeader->m_nPacketNum; i++)
				{
					RCV_REPORT_STRUCTExV3 & Buf = *(PRCV_REPORT_STRUCTExV3)(pBaseBuf + nBufSize*i );
					m_Stock[m_StkPtr].Format("%6s %8s N=%8.3f O=%8.3f C=%8.3f H=%8.3f L=%8.3f V=%10.0f A=%10.f",
						Buf.m_szLabel,Buf.m_szName,Buf.m_fNewPrice,Buf.m_fOpen,Buf.m_fLastClose,\
						Buf.m_fHigh,Buf.m_fLow,Buf.m_fVolume,Buf.m_fAmount);


					// ���ӵ����ݻ������
					TRACE("PB5=%8.3f VB5=%8.2f PS5=%8.3f VS5=%8.2f\n",Buf.m_fBuyPrice5,Buf.m_fBuyVolume5,Buf.m_fSellPrice5,Buf.m_fSellVolume5);

					m_StkPtr ++;
					m_StkPtr = m_StkPtr % StkBufNum;
				}
			}
			break;
	
		case RCV_FILEDATA:
			if( !pHeader->m_pData || pHeader->m_wDataType == FILE_TYPE_RES)
			{
				TRACE("MSG: CStkDemo::OnStkDataOK, Replaced data \n");
				break;
			}
			switch(pHeader->m_wDataType)
			{
				case FILE_HISTORY_EX:	// ����������
					RCV_HISTORY_STRUCTEx * pDay;
					pDay = pHeader->m_pDay;
					ASSERT(pHeader->m_pDay[0].m_head.m_dwHeadTag == EKE_HEAD_TAG);
					m_File = "���� ���룺";
					j = 0;
					for(i=0; i<pHeader->m_nPacketNum ; i++)
					{
						//��Ϊ�Ǳ����¼�ṹ,Ҫ�ж�
						if( pDay[i].m_head.m_dwHeadTag == EKE_HEAD_TAG )
						{
							//˵�����ļ�ͷ����,�õ���Ʊ����
							m_File = m_File + (const char *) pDay[i].m_head.m_szLabel + "  ";
							j ++;
						}else{
							//˵���Ǿ���K������
							day = pDay[i].m_time ;
							open = pDay[i].m_fOpen ;
							high= pDay[i].m_fHigh  ;
							low = pDay[i].m_fLow  ;
							close = pDay[i].m_fClose ;
							vol = pDay[i].m_fVolume ;
							amount = pDay[i].m_fAmount  ;
							CString test;
							test.Format("���ڣ�%d,���̼ۣ�%f,�ɽ���%f",day,close,amount); 
							//m_File = m_File + (const char *) test + "  ";
							//AfxMessageBox(m_File + (const char *) test);
						}
						if( j > 1) break;
					}
					break;

				case FILE_5MINUTE_EX:	// �������������
					RCV_HISMINUTE_STRUCTEx * p5Min;
					p5Min = pHeader->m_p5Min;
					ASSERT(pHeader->m_p5Min[0].m_head.m_dwHeadTag == EKE_HEAD_TAG);
					m_File = "������� ���룺";
					j = 0;
					for(i=0; i<pHeader->m_nPacketNum ; i++)
					{
						//��Ϊ�Ǳ����¼�ṹ,Ҫ�ж�
						if( p5Min[i].m_head.m_dwHeadTag == EKE_HEAD_TAG )
						{
							//˵�����ļ�ͷ����,�õ���Ʊ����
							m_File = m_File + (const char *) p5Min[i].m_head.m_szLabel + "  ";
							j ++;
						}else{
							//˵���Ǿ���K������
							day = p5Min[i].m_time ;
							open = p5Min[i].m_fOpen ;
							high= p5Min[i].m_fHigh  ;
							low = p5Min[i].m_fLow  ;
							close = p5Min[i].m_fClose ;
							vol = p5Min[i].m_fVolume ;
							amount = p5Min[i].m_fAmount  ;
							CString test;
							test.Format("ʱ�䣺%d,���̼ۣ�%f,�ɽ���%f",day,close,amount); 
							m_File = m_File + (const char *) test + "  ";
							//AfxMessageBox(m_File + (const char *) test);
						}
						if( j > 1) break;
					}
					break;
				case FILE_MINUTE_EX:   // �����������ݣ�����ʱ����
					RCV_MINUTE_STRUCTEx * pMin;
					pMin = pHeader->m_pMinute;
					ASSERT(pMin->m_head.m_dwHeadTag == EKE_HEAD_TAG);
					m_Min = "��ʱ����: ���룺";
					//AfxMessageBox(m_Min);
					j=0;
					for(i=0; i<pHeader->m_nPacketNum; i++)
					{
						//��Ϊ�Ǳ����¼�ṹ,Ҫ�ж�
						if( pMin[i].m_head.m_dwHeadTag == EKE_HEAD_TAG )
						{
							//˵�����ļ�ͷ����,�õ���Ʊ����
							m_Min = m_Min + (LPCSTR)pMin[i].m_head.m_szLabel + "  ";
							j++;
						}else{
							//˵���Ǿ����ʱ������,����ṹ�ɲο�.h�ļ��еĶ���˵��
							day = pMin[i].m_time ;
							close = pMin[i].m_fPrice ;
							vol = pMin[i].m_fVolume ;
							amount = pMin[i].m_fAmount  ;
							CString test;
							test.Format("ʱ�䣺%d,���¼ۣ�%f,�ɽ���%f",day,close,amount); 
							m_Min = m_Min + (const char *) test + "  ";
							//AfxMessageBox(m_Min + (const char *) test);
						}
						if( j > 1) break;
					}
					break;
				case FILE_POWER_EX:	   //��Ȩ����		
					POWER_TOTAL_STRUCTEx m_PowerData;
					m_PowerData.Power_Count=pHeader->m_nPacketNum;
					m_PowerData.m_RcvPower=pHeader->m_pPower;
					break;

				case FILE_BASE_EX:	   // Ǯ�����ݻ��������ļ�,m_szFileName�������ļ���
					//������ʾ��������������Ϣ��ʾ����,�����ǽ������������ļ��ķ�ʽ��������
					//����λ�þ��ǵ�ǰĿ¼�£��ļ���Ϊ��pHeader->m_File.m_szFileName
					m_File.Format("��������: %s",pHeader->m_File.m_szFileName);
					m_FileLong=pHeader->m_File.m_dwLen ;                
					m_FileName = pHeader->m_File.m_szFileName;
					if( (fp=fopen(m_FileName.GetBuffer(0) ,"wb+"))!=NULL) 				
					{
						fwrite(pHeader->m_pData , sizeof( char ),m_FileLong , fp );      
						fclose(fp) ;
					}
					break;

				case FILE_NEWS_EX:	   // ������,��������m_szFileName����Ŀ¼������
					m_File.Format("������Ϣ: %s",pHeader->m_File.m_szFileName);
					break;

				default:
					TRACE("Msg: CStkDemo::OnStkDataOK,Unkonw data type\n");
			}
			break;
		case RCV_FENBIDATA:
				//����ֱ�������������ط����գ���ǰ����ķֱʣ������̵�ֵ��0
				pFenBi = (RCV_FENBI *) lPara;
				test.Format("��¼����%d,�ֱʴ��룺%s,�ֱ����ڣ�%d",pFenBi->m_nCount,pFenBi->m_szLabel,pFenBi->m_lDate); 
				AfxMessageBox(test);				  
                for ( i = 0; i < pFenBi->m_nCount; i++)
                {
					//RCV_FENBI_STRUCTEx *pFenBiData=(RCV_FENBI_STRUCTEx *) (lPara+30+  sizeof(RCV_FENBI_STRUCTEx)*i );
					RCV_FENBI_STRUCTEx & Buf = *(PRCV_FENBI_STRUCTEx)(lPara+30+  sizeof(RCV_FENBI_STRUCTEx)*i );
					test.Format("����:%s,ʱ��:%d,�ɽ���:%f,�ɽ���:%f,�ɽ����:%f,��߼�:%f,���һ:%f,����һ:%f,����һ:%f,����һ:%f",pFenBi->m_szLabel,Buf.m_lTime,Buf.m_fNewPrice,Buf.m_fVolume,Buf.m_fAmount,Buf.m_fHigh,Buf.m_fBuyPrice[0],Buf.m_fBuyVolume[0],Buf.m_fSellPrice[0],Buf.m_fSellVolume[0]); 
					
					AfxMessageBox(test);							

					m_Stock[m_StkPtr].Format("%6s  N=%8.3f O=%8.3f C=%8.3f H=%8.3f L=%8.3f V=%10.0f A=%10.f",
						pFenBi->m_szLabel,Buf.m_fNewPrice,pFenBi->m_fOpen,pFenBi->m_fLastClose,\
						Buf.m_fHigh,Buf.m_fLow,Buf.m_fVolume,Buf.m_fAmount);


					m_StkPtr ++;
					m_StkPtr = m_StkPtr % StkBufNum;

					if (i > 5) break;
                }  
			break;
		case RCV_MKTTBLDATA:
			//���յ�������ݵĴ���				
			pMarketTableHead = (HLMarketType *) lPara;
			//test.Format("��ǰ����г���%hd,������¼����%hd",pMarketTableHead->m_wMarket,pMarketTableHead->m_nCount); 
			//AfxMessageBox(test);				  
            for ( i = 0; i < pMarketTableHead->m_nCount; i++)
            {
				RCV_TABLE_STRUCT & Buf = *(PRCV_TABLE_STRUCT)(lPara+54+  sizeof(RCV_TABLE_STRUCT)*i );
				test.Format("����:%s,����:%s",Buf.m_szLabel,Buf.m_szName); 
				//AfxMessageBox(test);					 

				m_Stock[m_StkPtr].Format("code=%6s  name=%12s",Buf.m_szLabel,Buf.m_szName);
						
				m_StkPtr ++;
				m_StkPtr = m_StkPtr % StkBufNum;

				if (i > 5) break;
            }  
			break;
		case RCV_FINANCEDATA:
			//���յ��������ݵĴ���			
			test.Format("�������ݰ���¼����%d",pHeader->m_nPacketNum ); 
			//AfxMessageBox(test);				  
            for ( i = 0; i < pHeader->m_nPacketNum; i++)
            {				 
				Fin_LJF_STRUCTEx & Buf = *(PFin_LJF_STRUCTEx)((int)pHeader->m_pData+  166*i );
				test.Format("�г�����:%d,��Ʊ����:%s,��������:%d,�ܹɱ�:%f,����������:%f",Buf.m_wMarket,Buf.m_szLabel,Buf.BGRQ,Buf.ZGB,Buf.JZCSYL); 
				//AfxMessageBox(test);					 

				m_Stock[m_StkPtr].Format("�г�����:%d,��Ʊ����:%s,��������:%d,�ܹɱ�:%f,����������:%f",Buf.m_wMarket,Buf.m_szLabel,Buf.BGRQ,Buf.ZGB,Buf.JZCSYL);

				m_StkPtr ++;
				m_StkPtr = m_StkPtr % StkBufNum;

				if (i > 5) break;
            }  
			break;
	}
	RedrawWindow();
	return 0L;
}

int CStkDemo::MyCreate(CWnd* pWnd)
{
	CRect rect(0, 0, 550,280);
	HBRUSH hBrush;
	if( m_bRunFlag ) return -1;
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
   	LPCTSTR lpszClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,hBrush);
	CreateEx(0,lpszClassName,"����ʦ",WS_OVERLAPPEDWINDOW,
		rect,pWnd, 0, NULL);

	ShowWindow(SW_SHOWNORMAL);
	UpdateWindow();

	int ok = gSTOCKDLL.Stock_Init(m_hWnd,My_Msg_StkData,RCV_WORK_SENDMSG);	// ���ݹ�������

	if( ok > 0 )
	{
		CString Title;
		Title.Format("����ʦ-�����ֶδ�С:%d",sizeof(RCV_REPORT_STRUCTExV3));
		SetWindowText(Title);
		m_bRunFlag = TRUE;
		return 1;
	}
	PostQuitMessage(-1);
	return -1;
}

void CStkDemo::OnDestroy() 
{
	CWnd::OnDestroy();
	m_bRunFlag = FALSE;
	gSTOCKDLL.Stock_Quit(m_hWnd);
}

void CStkDemo::TmpAskStockDay(char*  pszStockCode,int nTimePeriod) 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockDay(pszStockCode,nTimePeriod);	
}

void CStkDemo::TmpAskStockMn5(char*  pszStockCode,int nTimePeriod) 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockMn5(pszStockCode,nTimePeriod);	
}

void CStkDemo::TmpAskStockBase(char*  pszStockCode) 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockBase(pszStockCode);	
}

void CStkDemo::TmpAskStockNews() 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockNews();	
}

void CStkDemo::TmpAskStockHalt() 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockHalt();	
}

void CStkDemo::TmpAskStockMin(char*  pszStockCode) 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockMin(pszStockCode);	
}

void CStkDemo::TmpAskStockPRP(char*  pszStockCode) 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockPRP(pszStockCode);	
}

void CStkDemo::TmpAskStockPwr() 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockPwr();	
}

void CStkDemo::TmpAskStockFin() 
{
	// TODO: Add your command handler code here
	gSTOCKDLL.AskStockFin();
}
