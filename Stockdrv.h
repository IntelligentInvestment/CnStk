
/****************************************************************************************
*						���������ӿڹ淶V2.0
*							
****************************************************************************************/


/*****************************************************************************************
*	��������װ��,Ӧ����ϵͳע�����ע��������Ϣ,�������ͨ����ע����Ϣ������̬��		*
*	HKEY_LOCAL_MACHINE/SOFTWARE/StockDrv ��												* 
*	Driver  = "����DLLȫ·��"															*
****************************************************************************************/



#ifndef __STOCKDRV_H__
#define __STOCKDRV_H__


// ������ʽ���Ͷ���
#define RCV_WORK_SENDMSG			4					//��Ϣ������ʽ

/*
ָ������-����
1A0001  ��֤�ۺ�ָ��		1A0002  ��֤����ָ��		1A0003  ��֤�¹�ָ��
1B0001  ��֤��ҵָ��		1B0002  ��֤��ҵָ��		1B0004  ��֤�ز�ָ��
1B0005  ��֤������ҵ		1B0006  ��֤�ۺ�			1B0007  ��֤30ָ��


*/

/////////////////////////////////////////////////////////////////////////////////////////

// ֤ȯ�г�
#define		SH_MARKET_EX			'HS'		// �Ϻ�
#define		SZ_MARKET_EX			'ZS'		// ����
#define		HK_MARKET_EX			'KH'		// ���

// �ļ���������
// �ṹ������ʽ���ļ�����
#define		FILE_HISTORY_EX			2			// ����������
#define		FILE_MINUTE_EX			4			// ������������
#define		FILE_POWER_EX			6			// �����Ȩ����
#define     FILE_5MINUTE_EX         81 		    // ��5����������

#define		FILE_BASE_EX			0x1000		// Ǯ�����ݻ��������ļ�,m_szFileName�������ļ���
#define		FILE_NEWS_EX			0x1002		// ������,��������m_szFileName����Ŀ¼������
#define		FILE_HTML_EX			0x1004		// HTML�ļ�,m_szFileNameΪURL

#define		FILE_TYPE_RES			-1			// ����

// ��Ϣ������
#define		News_Sha_Ex				 2			// ��֤��Ϣ
#define		News_Szn_Ex				 4			// ��֤��Ϣ
#define		News_Fin_Ex				 6			// �ƾ�����
#define		News_TVSta_Ex			 8			// ����̨֪ͨ
#define		News_Unknown_Ex			 -1			// δ֪�ṩ��

//Definition For nInfo of Function GetStockDrvInfo(int nInfo,void * pBuf);
#define		RI_IDSTRING				1			// ��������,����(LPCSTR)������
#define		RI_IDCODE				2			// ����
#define		RI_VERSION				3			// ��������汾
#define		RI_V2SUPPORT			6			// ֧������SJS��ṹ

#define		STKLABEL_LEN			10			// �ɺ����ݳ���,�����г��ɺű������Ǯ��
#define		STKNAME_LEN				32			// ��������
#define     MKTNAME_LEN             16          // �����������г�����


#pragma pack(push)
#pragma pack(1)                                 // ��Ϊ���ֽڶ���


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//��������(�汾3���ݽṹRCV_WORK_SENDMSG������RCV_REPORT_STRUCTExV2�ṹ��ʹ��m_cbSize���ֲ�ͬ�ṹ)
//�汾3֧��5��������

typedef struct tagRCV_REPORT_STRUCTExV3	
{
	WORD	m_cbSize;									// �ṹ��С
	time_t	m_time;										// �ɽ�ʱ��
	WORD	m_wMarket;									// ��Ʊ�г�����
	char	m_szLabel[STKLABEL_LEN];					// ��Ʊ����,��'\0'��β
	char	m_szName[STKNAME_LEN];						// ��Ʊ����,��'\0'��β
	
	float	m_fLastClose;								// ���� �����ڻ��洢��������㣬�������������һ�ʼ۸�
	float	m_fOpen;									// ��
	float	m_fHigh;									// ���
	float	m_fLow;										// ���
	float	m_fNewPrice;								// ����
	float	m_fVolume;									// �ɽ���
	float	m_fAmount;									// �ɽ��� �����ڻ��洢���ǳֲ���

	float	m_fBuyPrice[3];								// �����1,2,3
	float	m_fBuyVolume[3];							// ������1,2,3
	float	m_fSellPrice[3];							// ������1,2,3
	float	m_fSellVolume[3];							// ������1,2,3

	float	m_fBuyPrice4;								// �����4
	float	m_fBuyVolume4;								// ������4
	float	m_fSellPrice4;								// ������4
	float	m_fSellVolume4;								// ������4

	float	m_fBuyPrice5;								// �����5
	float	m_fBuyVolume5;								// ������5
	float	m_fSellPrice5;								// ������5
	float	m_fSellVolume5;								// ������5
} RCV_REPORT_STRUCTExV3,*PRCV_REPORT_STRUCTExV3;

//////////////////////////////////////////////////////////////////////////////////


//�ֱ�����///////////////////////////////////
typedef struct tagRCV_FENBI_STRUCTEx
{
	long		m_lTime;					// hhmmss ����93056 ����9:
	float		m_fHigh;					// ���
	float		m_fLow;						// ��� 
	float		m_fNewPrice;				// ���� 
	float		m_fVolume;					// �ɽ���
	float		m_fAmount;					// �ɽ���
	long		m_lStroke;					// ����

	float		m_fBuyPrice[5];				// �����1,2,3,4,5
	float		m_fBuyVolume[5];			// ������1,2,3,4,5
	float		m_fSellPrice[5];			// ������1,2,3,4,5
	float		m_fSellVolume[5];			// ������1,2,3,4,5

}RCV_FENBI_STRUCTEx,*PRCV_FENBI_STRUCTEx;
 
typedef struct tagRCV_FENBI
{
	WORD					m_wMarket;					// ��Ʊ�г�����
	char					m_szLabel[STKLABEL_LEN];	// ��Ʊ����,��'\0'��β
	long					m_lDate;					// �ֱ����ݵ����� FORMAT:
	float					m_fLastClose;				// ����
	float					m_fOpen;					// ��
	WORD					m_nCount;					//m_Data���������ֱʱ���
	RCV_FENBI_STRUCTEx*		m_Data;						//����Ϊm_nCount
}RCV_FENBI,*PRCV_FENBI;


//��������ͷ
//����ͷ m_dwHeadTag == EKE_HEAD_TAG 
#define EKE_HEAD_TAG	0xffffffff

typedef struct	tagRCV_EKE_HEADEx
{
	DWORD	m_dwHeadTag;								// = EKE_HEAD_TAG
	WORD	m_wMarket;									// �г�����
	char	m_szLabel[STKLABEL_LEN];					// ��Ʊ����
}RCV_EKE_HEADEx;

//������������
typedef union tagRCV_HISTORY_STRUCTEx
{
	struct
	{
		time_t	m_time;				//UCT
		float	m_fOpen;			//����
		float	m_fHigh;			//���
		float	m_fLow;				//���
		float	m_fClose;			//����
		float	m_fVolume;			//��
		float	m_fAmount;			//��
		WORD	m_wAdvance;			//����,��������Ч
		WORD	m_wDecline;			//����,��������Ч
	};
	RCV_EKE_HEADEx	m_head;
}RCV_HISTORY_STRUCTEx;

//�����ʱ������
typedef union tagRCV_MINUTE_STRUCTEx
{
	struct{
		time_t	m_time;				// UCT
		float	m_fPrice;
		float	m_fVolume;
		float	m_fAmount;
	};
	RCV_EKE_HEADEx	m_head; 
}RCV_MINUTE_STRUCTEx;

//�����Ȩ����
typedef union tagRCV_POWER_STRUCTEx
{
	struct
	{
		time_t	m_time;				// UCT
		float	m_fGive;			// ÿ����
		float	m_fPei;				// ÿ����
		float	m_fPeiPrice;		// ��ɼ�,���� m_fPei!=0.0f ʱ��Ч
		float	m_fProfit;			// ÿ�ɺ���
	};
	RCV_EKE_HEADEx	m_head;
}RCV_POWER_STRUCTEx;

//������ʷ�����K������,ÿһ���ݽṹ��Ӧͨ�� m_time == EKE_HEAD_TAG,�ж��Ƿ�Ϊ m_head,Ȼ����������
typedef union tagRCV_HISMINUTE_STRUCTEx
{
	struct
    {
        time_t   m_time;         	   // UCT
        float    m_fOpen;		       //����
        float    m_fHigh;		       //���
		float    m_fLow;               //���
		float    m_fClose;             //����
		float    m_fVolume;            //��
		float    m_fAmount;            //��
		float    m_fActiveBuyVol;      //����������û�м���m_fActiveBuyVol=0
	};
    RCV_EKE_HEADEx  m_head;
}RCV_HISMINUTE_STRUCTEx;

//////////////////////////////////////////////////////////////////////////////////
// �ļ��������ݰ�ͷ
//  עһ:
//	m_wDataType == FILE_BASE_EX
//				m_dwAttrib = ��Ʊ֤ȯ�г�,m_szFileName�������ļ���
//  m_wDataType == FILE_NEWS_EX
//				m_dwAttrib = ��Ϣ��Դ,m_szFileName ����Ŀ¼���ļ���,Ŀ¼��Ϊ��Ϣ��Դ
//				��:  "�Ͻ�����Ϣ\\0501Z012.TXT","������\\XLD0001.TXT"
//  m_wDataType == FILE_HTML_EX
//				m_dwAttrib ����, m_szFileNameΪURL
//	m_wDataType	== FILE_SOFTWARE_EX
//				m_dwAttrib �����������, ���ڳ����ж�
//				m_szFileName ������� ID �����ַ��� + '\\' + �ļ���
//				�� "CnStock\\CnStock.EXE",
//				ID �����ַ���Ϊ "CnStock", "CnStock.EXE" Ϊ�ļ���
//				�����ַ��� �� �ļ������京���ɷ�������̶���
//  ע��:
//		�����ļ�ѭ������,ÿ���ļ���Ψһ�����к�,�Ա����ظ�����
typedef struct tagRCV_FILE_HEADEx
{
	DWORD	m_dwAttrib;							// �ļ�������
	DWORD	m_dwLen;							// �ļ�����
	DWORD	m_dwSerialNo;						// ���к�
	char	m_szFileName[MAX_PATH];				// �ļ��� or URL
} RCV_FILE_HEADEx;

//////////////////////////////////////////////////////////////////////////////////
//  ����֪ͨ��Ϣ
//ֱ����������֪ͨ��Ϣ
//	wParam = RCV_WPARAM;
//  lParam ָ�� RCV_DATA�ṹ;
//	���� 1 �Ѿ�����, 0 δ������ܴ���

#define RCV_REPORT			0x3f001234
#define RCV_FILEDATA		0x3f001235
#define RCV_FENBIDATA		0x3f001258 
#define RCV_MKTTBLDATA      0x3f001259           //���յ��г��������
#define RCV_FINANCEDATA     0x3f001300           //���յ������ļ�����


// עһ:
//	  ��¼����ʾ�������ݺͲ�������(���� Header)�����ݰ���,���ļ���������, = 1
// ע��:
//	  �� m_bDISK = FALSE, m_pData Ϊ���ݻ�����ָ��
//		 ******** ���ݹ���,�����޸����� **********
//		 m_bDISK = TRUE,  m_pData Ϊ���ļ��Ĵ����ļ���,һ�����ֻ��
//		 ��������ȴ��ļ��ô��̷�ʽ
typedef struct tagRCV_DATA
{
	int					m_wDataType;			// �ļ�����
	int					m_nPacketNum;			// ��¼��,�μ�עһ
	RCV_FILE_HEADEx		m_File;					// �ļ��ӿ�
	BOOL				m_bDISK;				// �ļ��Ƿ��Ѵ��̵��ļ�
	union
	{
		RCV_REPORT_STRUCTExV3*	m_pReportV3;
		RCV_HISTORY_STRUCTEx *	m_pDay;
		RCV_MINUTE_STRUCTEx  *	m_pMinute;
		RCV_POWER_STRUCTEx   *	m_pPower;
		RCV_HISMINUTE_STRUCTEx *	m_p5Min;
		void		     *	m_pData;		// �μ�ע��
	};
} RCV_DATA;


typedef struct  tagRCV_TABLE_STRUCT 
{                               // ֤ȯ
    char   m_szLabel[STKLABEL_LEN] ;                      // ��Ʊ����,��'\0'��β,�� "500500"
    char   m_szName[STKNAME_LEN];                      // ��Ʊ����,��'\0'��β,"��ָ֤��"
    WORD   m_cProperty;                            // ÿ�ֹ���
}RCV_TABLE_STRUCT,* PRCV_TABLE_STRUCT;


typedef struct  tagHLMarketType                //�г�����
{
    WORD   m_wMarket;			         //�г�����
    char   m_Name[MKTNAME_LEN];			 //�г�����,��'\0'��β
    DWORD  m_lProperty;	         //�г����ԣ�δ���壩
    DWORD  m_lDate;			         //�������ڣ�20030114��
    WORD   m_PeriodCount;			 //����ʱ�θ���
    WORD   m_OpenTime[5];		 //����ʱ�� 1,2,3,4,5
    WORD   m_CloseTime[5];	 //����ʱ�� 1,2,3,4,5
    WORD   m_nCount;                     //���г���֤ȯ����
    RCV_TABLE_STRUCT* m_Data;	//����Ϊm_nCou

}HLMarketType,*PHLMarketType;


typedef struct  tagFin_LJF_STRUCTEx
{
    WORD   m_wMarket;       // ��Ʊ�г�����
    WORD   N1;              // �����ֶ�
    char   m_szLabel[10];   // ��Ʊ����,��'\0'��β,�� "600050"  10���ֽ� ͬͨ�ӹ淶����
    long   BGRQ ;           // �������ݵ����� ����걨 ������ �� 20090630 ��ʾ 2009����걨
    float  ZGB;             // �ܹɱ�
    float  GJG;             // ���ҹ�
    float  FQFRG;           // �����˷��˹�
    float  FRG;             // ���˹�
    float  BGS;             // B��
    float  HGS;             // H��
    float  MQLT;            // Ŀǰ��ͨ
    float  ZGG;             // ְ����
    float  A2ZPG;           // A2ת���
    float  ZZC;             // ���ʲ�(ǧԪ)
    float  LDZC;            // �����ʲ�
    float  GDZC;            // �̶��ʲ�
    float  WXZC;            // �����ʲ�
    float  CQTZ;            // ����Ͷ��
    float  LDFZ;            // ������ծ
    float  CQFZ;            // ���ڸ�ծ
    float  ZBGJJ;           // �ʱ�������
    float  MGGJJ;           // ÿ�ɹ�����
    float  GDQY;            // �ɶ�Ȩ��
    float  ZYSR;            // ��Ӫ����
    float  ZYLR;            // ��Ӫ����
    float  QTLR;            // ��������
    float  YYLR;            // Ӫҵ����
    float  TZSY;            // Ͷ������
    float  BTSR;            // ��������
    float  YYWSZ;           // Ӫҵ����֧
    float  SNSYTZ;          // �����������
    float  LRZE;            // �����ܶ�
    float  SHLR;            // ˰������
    float  JLR;             // ������
    float  WFPLR;           // δ��������
    float  MGWFP;           // ÿ��δ����
    float  MGSY;            // ÿ������
    float  MGJZC;           // ÿ�ɾ��ʲ�
    float  TZMGJZC;         // ����ÿ�ɾ��ʲ�
    float  GDQYB;           // �ɶ�Ȩ���
    float  JZCSYL;          // ����������
}Fin_LJF_STRUCTEx,*PFin_LJF_STRUCTEx;


#pragma pack(pop)




/* ��Ϣ������� DEMO
LONG OnStkDataOK(UINT wParam,LONG lParam)
{
	RCV_DATA*		pHeader;
	pHeader = (RCV_DATA *)lParam;
	switch( wParam )
	{
	case RCV_REPORT:						// �����������÷�ʽ,��Ʊ����
		for(i=0; i<pHeader->m_nPacketNum; i++)
		{
			pHeader->m_pReport[i] ...
			// ���ݴ���
		}
		break;

	case RCV_FILEDATA:						// �����������÷�ʽ,�ļ�
		switch(pHeader->m_wDataType)
		{
		case FILE_HISTORY_EX:				// ����������
			break;
		case FILE_MINUTE_EX:				// ������������
			break;
		case FILE_POWER_EX:					// �����Ȩ����
			break;
		case FILE_BASE_EX:					// Ǯ�����ݻ��������ļ�,m_szFileName�������ļ���
			break;
		case FILE_NEWS_EX:					// ������,��������m_szFileName����Ŀ¼������
			break;
		case FILE_HTML_EX:					// HTML�ļ�,m_szFileNameΪURL
			break;
		case FILE_SOFTWARE_EX:				// �������
			break;
		}
		break;
	default:
		return 0;							// unknown data
	}
	return 1;
}
*/


//////////////////////////////////////////////////////////////////////////////////
//APIs
#ifdef __cplusplus
extern "C"{
#endif

//////////////////////////////////////////////////////////////////////////////////
// ע�ắ��

// ��Ʊ��ʼ��
// ��ڲ���:
//		hWnd			������Ϣ�Ĵ��ھ��
//		Msg				�û��Զ�����Ϣ
//		nWorkMode		�ӿڹ�����ʽ,�μ�������ʽ���Ͷ���
// ���ز���:
//		 1				�ɹ�	
//		-1				ʧ��
// ע:
//		ע���,��������������ڷ�����Ϣ; ����ע��,ͨ����ѯ��ʽ���ȡ������
//		����Ʊ����û����,��������Ʊ���ճ���
int WINAPI	Stock_Init(HWND hWnd,UINT Msg,int nWorkMode);

// �˳�,ֹͣ������Ϣ
// ��ڲ���:
//		hWnd			������Ϣ�Ĵ��ھ��,ͬ Stock_Init �ĵ�����ڲ���
//	���ز���:
//		 1				�ɹ�	
//		-1				ʧ��
int WINAPI 	Stock_Quit(HWND hWnd);

// ������ճ���,��������
// ��ڲ���:
//			bSetup		TRUE		��ʾ����,��������
//						FALSE		��������
// ���ز���:
//			 1			�ɹ�
//			-1			ʧ��
int	WINAPI  SetupReceiver(BOOL bSetup);

//	ȡ�ù�Ʊ������Ϣ
//	��ڲ���:
//			nInfo		����
//			pBuf		������
//	���ڲ���:
//			nInfo == RI_IDSTRING,	���������ַ�������, pBuf Ϊ�����ַ���
//									��:	"TongShi_StockDrv_1.00"
//			nInfo == RI_IDCODE,		������Ϣ�� ID ��, pBuf Ϊ�ַ�����ʽ�� ID ��
//									��:	0x78001234	  "78001234"
//			nInfo == RI_VERSION,	������Ϣ���汾��, pBuf Ϊ�ַ����汾
//									��:  1.00		  "1.00"		
//			nInfo == RI_V2SUPPORT,	�����Ƿ�֧������SJS��ṹ, pBuf��Ч
DWORD WINAPI  GetStockDrvInfo(int nInfo,void * pBuf);


void WINAPI  ReInitStockInfo();
//����ȡ�ù�Ʊ����(����)

//��չAPI����

//���ܣ�����������
//������nTimePeriod����ֵ1,2,3�ֱ��ʾ�ܡ��¡�ȫ��
//pszStockCode������Ϊ�ձ�ʾ��ȫ����Ʊ���������ݣ���Ϊ�����ʾ����ǰ��Ʊ����������
int WINAPI	AskStockDay(char*  pszStockCode,int nTimePeriod);

//���ܣ��������������
//������nTimePeriod����ֵ1,2,3�ֱ��ʾ�ܡ��¡����������
//pszStockCode������Ϊ�ձ�ʾ��ȫ����Ʊ������������ݣ���Ϊ�����ʾ����ǰ��Ʊ�������������
int WINAPI	AskStockMn5(char*  pszStockCode,int nTimePeriod);

//���ܣ�ȡ��������,Ŀǰ�汾��Ը�������F10�������ָ��ɣ���ȡ�����ݶ���ȫ������
//������pszStockCode��Ŀǰ�˲��������Ƿ��ֵ������ȡȫ����Ʊ��F10��������
int WINAPI	AskStockBase(char*  pszStockCode);

//���ܣ�ȡ�ƾ�����
int WINAPI	AskStockNews();

//���ܣ�ȡ����ֹ,�˹����൱�ڲ��������ϵ�ֹͣ������ť�Ĺ���
int WINAPI	AskStockHalt();

//���ܣ�ȡ��ʱ����
//�����������������Ϊ�գ���ȫ����Ʊ�ķ�ʱ
int WINAPI	AskStockMin(char*  pszStockCode);

//���ܣ�ȡ�ֱ�����
//�����������������Ϊ�գ���ȫ����Ʊ�ķֱ�
int WINAPI	AskStockPRP(char*  pszStockCode);

//���ܣ�ȡ��Ȩ����
int WINAPI	AskStockPwr();

//���ܣ�ȡ��������
int WINAPI	AskStockFin();


#ifdef __cplusplus
}
#endif


#endif // __STOCKDRV_H__