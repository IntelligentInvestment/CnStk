
/****************************************************************************************
*						龙卷风行情接口规范V2.0
*							
****************************************************************************************/


/*****************************************************************************************
*	驱动程序安装后,应该在系统注册库中注册以下信息,分析软件通过该注册信息启动动态库		*
*	HKEY_LOCAL_MACHINE/SOFTWARE/StockDrv 下												* 
*	Driver  = "驱动DLL全路径"															*
****************************************************************************************/



#ifndef __STOCKDRV_H__
#define __STOCKDRV_H__


// 工作方式类型定义
#define RCV_WORK_SENDMSG			4					//消息工作方式

/*
指数代号-名称
1A0001  上证综合指数		1A0002  上证Ａ股指数		1A0003  上证Ｂ股指数
1B0001  上证工业指数		1B0002  上证商业指数		1B0004  上证地产指数
1B0005  上证公用事业		1B0006  上证综合			1B0007  上证30指数


*/

/////////////////////////////////////////////////////////////////////////////////////////

// 证券市场
#define		SH_MARKET_EX			'HS'		// 上海
#define		SZ_MARKET_EX			'ZS'		// 深圳
#define		HK_MARKET_EX			'KH'		// 香港

// 文件数据类型
// 结构数组形式的文件数据
#define		FILE_HISTORY_EX			2			// 补日线数据
#define		FILE_MINUTE_EX			4			// 补分钟线数据
#define		FILE_POWER_EX			6			// 补充除权数据
#define     FILE_5MINUTE_EX         81 		    // 补5分钟线数据

#define		FILE_BASE_EX			0x1000		// 钱龙兼容基本资料文件,m_szFileName仅包含文件名
#define		FILE_NEWS_EX			0x1002		// 新闻类,其类型由m_szFileName中子目录名来定
#define		FILE_HTML_EX			0x1004		// HTML文件,m_szFileName为URL

#define		FILE_TYPE_RES			-1			// 保留

// 消息子类型
#define		News_Sha_Ex				 2			// 上证消息
#define		News_Szn_Ex				 4			// 深证消息
#define		News_Fin_Ex				 6			// 财经报道
#define		News_TVSta_Ex			 8			// 电视台通知
#define		News_Unknown_Ex			 -1			// 未知提供者

//Definition For nInfo of Function GetStockDrvInfo(int nInfo,void * pBuf);
#define		RI_IDSTRING				1			// 厂商名称,返回(LPCSTR)厂商名
#define		RI_IDCODE				2			// 卡号
#define		RI_VERSION				3			// 驱动程序版本
#define		RI_V2SUPPORT			6			// 支持深圳SJS库结构

#define		STKLABEL_LEN			10			// 股号数据长度,国内市场股号编码兼容钱龙
#define		STKNAME_LEN				32			// 股名长度
#define     MKTNAME_LEN             16          // 码表所代表的市场名称


#pragma pack(push)
#pragma pack(1)                                 // 改为按字节对齐


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//行情数据(版本3数据结构RCV_WORK_SENDMSG，兼容RCV_REPORT_STRUCTExV2结构，使用m_cbSize区分不同结构)
//版本3支持5档买卖盘

typedef struct tagRCV_REPORT_STRUCTExV3	
{
	WORD	m_cbSize;									// 结构大小
	time_t	m_time;										// 成交时间
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	char	m_szName[STKNAME_LEN];						// 股票名称,以'\0'结尾
	
	float	m_fLastClose;								// 昨收 对于期货存储的是昨结算，而不是昨天最后一笔价格
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额 对于期货存储的是持仓量

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3

	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4

	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5
} RCV_REPORT_STRUCTExV3,*PRCV_REPORT_STRUCTExV3;

//////////////////////////////////////////////////////////////////////////////////


//分笔数据///////////////////////////////////
typedef struct tagRCV_FENBI_STRUCTEx
{
	long		m_lTime;					// hhmmss 例：93056 表明9:
	float		m_fHigh;					// 最高
	float		m_fLow;						// 最低 
	float		m_fNewPrice;				// 最新 
	float		m_fVolume;					// 成交量
	float		m_fAmount;					// 成交额
	long		m_lStroke;					// 保留

	float		m_fBuyPrice[5];				// 申买价1,2,3,4,5
	float		m_fBuyVolume[5];			// 申买量1,2,3,4,5
	float		m_fSellPrice[5];			// 申卖价1,2,3,4,5
	float		m_fSellVolume[5];			// 申卖量1,2,3,4,5

}RCV_FENBI_STRUCTEx,*PRCV_FENBI_STRUCTEx;
 
typedef struct tagRCV_FENBI
{
	WORD					m_wMarket;					// 股票市场类型
	char					m_szLabel[STKLABEL_LEN];	// 股票代码,以'\0'结尾
	long					m_lDate;					// 分笔数据的日期 FORMAT:
	float					m_fLastClose;				// 昨收
	float					m_fOpen;					// 今开
	WORD					m_nCount;					//m_Data的数据量分笔笔数
	RCV_FENBI_STRUCTEx*		m_Data;						//长度为m_nCount
}RCV_FENBI,*PRCV_FENBI;


//补充数据头
//数据头 m_dwHeadTag == EKE_HEAD_TAG 
#define EKE_HEAD_TAG	0xffffffff

typedef struct	tagRCV_EKE_HEADEx
{
	DWORD	m_dwHeadTag;								// = EKE_HEAD_TAG
	WORD	m_wMarket;									// 市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码
}RCV_EKE_HEADEx;

//补充日线数据
typedef union tagRCV_HISTORY_STRUCTEx
{
	struct
	{
		time_t	m_time;				//UCT
		float	m_fOpen;			//开盘
		float	m_fHigh;			//最高
		float	m_fLow;				//最低
		float	m_fClose;			//收盘
		float	m_fVolume;			//量
		float	m_fAmount;			//额
		WORD	m_wAdvance;			//涨数,仅大盘有效
		WORD	m_wDecline;			//跌数,仅大盘有效
	};
	RCV_EKE_HEADEx	m_head;
}RCV_HISTORY_STRUCTEx;

//补充分时线数据
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

//补充除权数据
typedef union tagRCV_POWER_STRUCTEx
{
	struct
	{
		time_t	m_time;				// UCT
		float	m_fGive;			// 每股送
		float	m_fPei;				// 每股配
		float	m_fPeiPrice;		// 配股价,仅当 m_fPei!=0.0f 时有效
		float	m_fProfit;			// 每股红利
	};
	RCV_EKE_HEADEx	m_head;
}RCV_POWER_STRUCTEx;

//补充历史五分钟K线数据,每一数据结构都应通过 m_time == EKE_HEAD_TAG,判断是否为 m_head,然后再作解释
typedef union tagRCV_HISMINUTE_STRUCTEx
{
	struct
    {
        time_t   m_time;         	   // UCT
        float    m_fOpen;		       //开盘
        float    m_fHigh;		       //最高
		float    m_fLow;               //最低
		float    m_fClose;             //收盘
		float    m_fVolume;            //量
		float    m_fAmount;            //额
		float    m_fActiveBuyVol;      //主动买量如没有计算m_fActiveBuyVol=0
	};
    RCV_EKE_HEADEx  m_head;
}RCV_HISMINUTE_STRUCTEx;

//////////////////////////////////////////////////////////////////////////////////
// 文件类型数据包头
//  注一:
//	m_wDataType == FILE_BASE_EX
//				m_dwAttrib = 股票证券市场,m_szFileName仅包含文件名
//  m_wDataType == FILE_NEWS_EX
//				m_dwAttrib = 消息来源,m_szFileName 包含目录的文件名,目录名为消息来源
//				如:  "上交所消息\\0501Z012.TXT","新兰德\\XLD0001.TXT"
//  m_wDataType == FILE_HTML_EX
//				m_dwAttrib 保留, m_szFileName为URL
//	m_wDataType	== FILE_SOFTWARE_EX
//				m_dwAttrib 分析软件类型, 用于初步判断
//				m_szFileName 分析软件 ID 特征字符串 + '\\' + 文件名
//				如 "CnStock\\CnStock.EXE",
//				ID 特征字符串为 "CnStock", "CnStock.EXE" 为文件名
//				特征字符串 和 文件名及其含义由分析软件商定义
//  注二:
//		数据文件循环播出,每个文件有唯一的序列号,以避免重复接收
typedef struct tagRCV_FILE_HEADEx
{
	DWORD	m_dwAttrib;							// 文件子类型
	DWORD	m_dwLen;							// 文件长度
	DWORD	m_dwSerialNo;						// 序列号
	char	m_szFileName[MAX_PATH];				// 文件名 or URL
} RCV_FILE_HEADEx;

//////////////////////////////////////////////////////////////////////////////////
//  数据通知消息
//直接数据引用通知消息
//	wParam = RCV_WPARAM;
//  lParam 指向 RCV_DATA结构;
//	返回 1 已经处理, 0 未处理或不能处理

#define RCV_REPORT			0x3f001234
#define RCV_FILEDATA		0x3f001235
#define RCV_FENBIDATA		0x3f001258 
#define RCV_MKTTBLDATA      0x3f001259           //接收到市场码表数据
#define RCV_FINANCEDATA     0x3f001300           //接收到财务文件数据


// 注一:
//	  记录数表示行情数据和补充数据(包括 Header)的数据包数,对文件类型数据, = 1
// 注二:
//	  若 m_bDISK = FALSE, m_pData 为数据缓冲区指针
//		 ******** 数据共享,不能修改数据 **********
//		 m_bDISK = TRUE,  m_pData 为该文件的存盘文件名,一般情况只有
//		 升级软件等大文件用存盘方式
typedef struct tagRCV_DATA
{
	int					m_wDataType;			// 文件类型
	int					m_nPacketNum;			// 记录数,参见注一
	RCV_FILE_HEADEx		m_File;					// 文件接口
	BOOL				m_bDISK;				// 文件是否已存盘的文件
	union
	{
		RCV_REPORT_STRUCTExV3*	m_pReportV3;
		RCV_HISTORY_STRUCTEx *	m_pDay;
		RCV_MINUTE_STRUCTEx  *	m_pMinute;
		RCV_POWER_STRUCTEx   *	m_pPower;
		RCV_HISMINUTE_STRUCTEx *	m_p5Min;
		void		     *	m_pData;		// 参见注二
	};
} RCV_DATA;


typedef struct  tagRCV_TABLE_STRUCT 
{                               // 证券
    char   m_szLabel[STKLABEL_LEN] ;                      // 股票代码,以'\0'结尾,如 "500500"
    char   m_szName[STKNAME_LEN];                      // 股票名称,以'\0'结尾,"上证指数"
    WORD   m_cProperty;                            // 每手股数
}RCV_TABLE_STRUCT,* PRCV_TABLE_STRUCT;


typedef struct  tagHLMarketType                //市场内容
{
    WORD   m_wMarket;			         //市场代码
    char   m_Name[MKTNAME_LEN];			 //市场名称,以'\0'结尾
    DWORD  m_lProperty;	         //市场属性（未定义）
    DWORD  m_lDate;			         //数据日期（20030114）
    WORD   m_PeriodCount;			 //交易时段个数
    WORD   m_OpenTime[5];		 //开市时间 1,2,3,4,5
    WORD   m_CloseTime[5];	 //收市时间 1,2,3,4,5
    WORD   m_nCount;                     //该市场的证券个数
    RCV_TABLE_STRUCT* m_Data;	//长度为m_nCou

}HLMarketType,*PHLMarketType;


typedef struct  tagFin_LJF_STRUCTEx
{
    WORD   m_wMarket;       // 股票市场类型
    WORD   N1;              // 保留字段
    char   m_szLabel[10];   // 股票代码,以'\0'结尾,如 "600050"  10个字节 同通视规范定义
    long   BGRQ ;           // 财务数据的日期 如半年报 季报等 如 20090630 表示 2009年半年报
    float  ZGB;             // 总股本
    float  GJG;             // 国家股
    float  FQFRG;           // 发起人法人股
    float  FRG;             // 法人股
    float  BGS;             // B股
    float  HGS;             // H股
    float  MQLT;            // 目前流通
    float  ZGG;             // 职工股
    float  A2ZPG;           // A2转配股
    float  ZZC;             // 总资产(千元)
    float  LDZC;            // 流动资产
    float  GDZC;            // 固定资产
    float  WXZC;            // 无形资产
    float  CQTZ;            // 长期投资
    float  LDFZ;            // 流动负债
    float  CQFZ;            // 长期负债
    float  ZBGJJ;           // 资本公积金
    float  MGGJJ;           // 每股公积金
    float  GDQY;            // 股东权益
    float  ZYSR;            // 主营收入
    float  ZYLR;            // 主营利润
    float  QTLR;            // 其他利润
    float  YYLR;            // 营业利润
    float  TZSY;            // 投资收益
    float  BTSR;            // 补贴收入
    float  YYWSZ;           // 营业外收支
    float  SNSYTZ;          // 上年损益调整
    float  LRZE;            // 利润总额
    float  SHLR;            // 税后利润
    float  JLR;             // 净利润
    float  WFPLR;           // 未分配利润
    float  MGWFP;           // 每股未分配
    float  MGSY;            // 每股收益
    float  MGJZC;           // 每股净资产
    float  TZMGJZC;         // 调整每股净资产
    float  GDQYB;           // 股东权益比
    float  JZCSYL;          // 净资收益率
}Fin_LJF_STRUCTEx,*PFin_LJF_STRUCTEx;


#pragma pack(pop)




/* 消息处理程序 DEMO
LONG OnStkDataOK(UINT wParam,LONG lParam)
{
	RCV_DATA*		pHeader;
	pHeader = (RCV_DATA *)lParam;
	switch( wParam )
	{
	case RCV_REPORT:						// 共享数据引用方式,股票行情
		for(i=0; i<pHeader->m_nPacketNum; i++)
		{
			pHeader->m_pReport[i] ...
			// 数据处理
		}
		break;

	case RCV_FILEDATA:						// 共享数据引用方式,文件
		switch(pHeader->m_wDataType)
		{
		case FILE_HISTORY_EX:				// 补日线数据
			break;
		case FILE_MINUTE_EX:				// 补分钟线数据
			break;
		case FILE_POWER_EX:					// 补充除权数据
			break;
		case FILE_BASE_EX:					// 钱龙兼容基本资料文件,m_szFileName仅包含文件名
			break;
		case FILE_NEWS_EX:					// 新闻类,其类型由m_szFileName中子目录名来定
			break;
		case FILE_HTML_EX:					// HTML文件,m_szFileName为URL
			break;
		case FILE_SOFTWARE_EX:				// 升级软件
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
// 注册函数

// 股票初始化
// 入口参数:
//		hWnd			处理消息的窗口句柄
//		Msg				用户自定义消息
//		nWorkMode		接口工作方式,参见工作方式类型定义
// 返回参数:
//		 1				成功	
//		-1				失败
// 注:
//		注册后,驱动程序会向处理窗口发送消息; 若不注册,通过查询方式亦可取得数据
//		若股票接收没启动,则启动股票接收程序
int WINAPI	Stock_Init(HWND hWnd,UINT Msg,int nWorkMode);

// 退出,停止发送消息
// 入口参数:
//		hWnd			处理消息的窗口句柄,同 Stock_Init 的调用入口参数
//	返回参数:
//		 1				成功	
//		-1				失败
int WINAPI 	Stock_Quit(HWND hWnd);

// 激活接收程序,进行设置
// 入口参数:
//			bSetup		TRUE		显示窗口,进行设置
//						FALSE		隐含窗口
// 返回参数:
//			 1			成功
//			-1			失败
int	WINAPI  SetupReceiver(BOOL bSetup);

//	取得股票驱动信息
//	入口参数:
//			nInfo		索引
//			pBuf		缓冲区
//	出口参数:
//			nInfo == RI_IDSTRING,	返回特征字符串长度, pBuf 为特征字符串
//									如:	"TongShi_StockDrv_1.00"
//			nInfo == RI_IDCODE,		返回信息卡 ID 号, pBuf 为字符串形式的 ID 号
//									如:	0x78001234	  "78001234"
//			nInfo == RI_VERSION,	返回信息卡版本号, pBuf 为字符串版本
//									如:  1.00		  "1.00"		
//			nInfo == RI_V2SUPPORT,	返回是否支持深圳SJS库结构, pBuf无效
DWORD WINAPI  GetStockDrvInfo(int nInfo,void * pBuf);


void WINAPI  ReInitStockInfo();
//重新取得股票数据(保留)

//扩展API函数

//功能，补日线数据
//参数：nTimePeriod参数值1,2,3分别表示周、月、全部
//pszStockCode，参数为空表示补全部股票的日线数据，不为空则表示补当前股票的日线数据
int WINAPI	AskStockDay(char*  pszStockCode,int nTimePeriod);

//功能，补五分钟线数据
//参数：nTimePeriod参数值1,2,3分别表示周、月、最近三个月
//pszStockCode，参数为空表示补全部股票的五分钟线数据，不为空则表示补当前股票的五分钟线数据
int WINAPI	AskStockMn5(char*  pszStockCode,int nTimePeriod);

//功能，取个股资料,目前版本针对个股资料F10，不区分个股，获取的数据都是全部资料
//参数：pszStockCode，目前此参数无论是否空值，均获取全部股票的F10个股资料
int WINAPI	AskStockBase(char*  pszStockCode);

//功能，取财经新闻
int WINAPI	AskStockNews();

//功能，取数中止,此功能相当于补数界面上的停止补数按钮的功能
int WINAPI	AskStockHalt();

//功能，取分时数据
//参数：如果参数代码为空，则补全部股票的分时
int WINAPI	AskStockMin(char*  pszStockCode);

//功能，取分笔数据
//参数：如果参数代码为空，则补全部股票的分笔
int WINAPI	AskStockPRP(char*  pszStockCode);

//功能，取除权数据
int WINAPI	AskStockPwr();

//功能，取财务数据
int WINAPI	AskStockFin();


#ifdef __cplusplus
}
#endif


#endif // __STOCKDRV_H__