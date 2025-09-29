#pragma once


enum class EServerLogType
{
	Unknown = 0,
	Status,
	Warn,
	Error
};

enum ELogItem
{
	 ITEMLOGID_Get = 0,
	 ITEMLOGID_Put = 6,
	 ITEMLOGID_Mixing = 9,
	 ITEMLOGID_MixLost = 3,
	 ITEMLOGID_Aging = 4,
	 ITEMLOGID_AgingLost = 10,
	 ITEMLOGID_AgingUp = 12,
	 ITEMLOGID_BuyShop = 5,
	 ITEMLOGID_SellShop = 7,
	 ITEMLOGID_Trade = 8,
	 ITEMLOGID_Used = 11,
	 ITEMLOGID_Express = 13,
	 ITEMLOGID_GetWing = 14,
	 ITEMLOGID_WingLost = 15,
	 ITEMLOGID_BuyStar = 16,

	 ITEMLOGID_Aging2Up = 17,
	 ITEMLOGID_Aging2Down = 18,
	 ITEMLOGID_Aging1Down = 19,
	 ITEMLOGID_AgingKeep = 20,

	 ITEMLOGID_Present = 21,
	 ITEMLOGID_PersonalShop = 22,

	 ITEMLOGID_UseAlchmy = 24,
	 ITEMLOGID_LostAlchmy = 25,
	 ITEMLOGID_GetAlchmy = 26,

	 ITEMLOGID_GetRecon = 27,
	 ITEMLOGID_LostRecon = 28,
	 ITEMLOGID_SmeltingLost = 29,
	 ITEMLOGID_SmeltingGet = 30,
	 ITEMLOGID_ManufactureLost = 31,
	 ITEMLOGID_ManufactureGet = 32,
	 ITEMLOGID_ManufactureFail = 33,
	 ITEMLOGID_MixtureResetLost = 34,
	 ITEMLOGID_MixtureResetFail = 35,
	 ITEMLOGID_MixtureResetGet = 36,


	 ITEMLOGID_PremiumTimerOver = 1001,
	 ITEMLOGID_TradeItems = 1002,
	 ITEMLOGID_TradeItemsRemove = 1003,
	 ITEMLOGID_RewardEasterGet = 1004,
	 ITEMLOGID_RewardChristmasRudolphGet = 1005,
	 ITEMLOGID_TradeItemSuccess = 1006,
	 ITEMLOGID_TradeItemSuccessReceive = 1007,
	 ITEMLOGID_GetPerfectize = 1008,
	 ITEMLOGID_PutPerfectize = 1009,
	 ITEMLOGID_GetSwap = 1010,
	 ITEMLOGID_PutSwap = 1011,
	 ITEMLOGID_PerfectizedItem = 1050,
	 ITEMLOGID_SwappedItem = 1051,
	 ITEMLOGID_RollDiceJoin = 1060,
	 ITEMLOGID_RollDiceWon = 1061,
	 ITEMLOGID_ItemGivenToUserByGM = 1062,

	 ITEMLOGID_ItemRespec = 1063,
	 ITEMLOGID_CleanStoneSuccess = 1064,
	 ITEMLOGID_CleanStoneFail = 1065,

};


struct	_LogITEM 
{
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwCheckSum;
};

struct LogItem 
{
	int 		size;			// ����� ����ü�� ũ��
	char 		UserID[32];  		// ����� ID
	char 		CharName[24]; 		// ����� ĳ���� �̸�
	int 		IP; 			// ����� IP            <===== �߰�
	int 		Flag;			// ������ ����
	int		ItemCount;		// ó���� ������ ����
	_LogITEM	Item[32];		// ������ ����
};

struct LogItemTrade
{
	int 		size;			// ����� ����ü�� ũ��
	char 		UserID[32];  		// ����� ID
	char 		CharName[24]; 		// ����� ĳ���� �̸�
	int		IP;			// ����� IP         <========= �߰� 
	int 		Flag;			// ������ ����

	char 		TUserID[32];		// �ŷ� ���̵�
	char 		TCharName[24];		// �ŷ� ĳ���� �̸�
	int 		TIP;			// �ŷ� IP           <========= �߰� 
	int		Money;			// �ŷ��� �ݾ�
	int		ItemCount;		// �ŷ��� ������ ����
	_LogITEM 	Item[32];		// ������ ����
};

struct LogItemGift
{
	int 		size;		// ����� ����ü�� ũ��
	char 		UserID[32];  	// ����� ID
	char 		CharName[24]; 	// ����� ĳ���� �̸�
	int 		IP; 		// ����� IP
	int 		Flag;		// ������ ����    (�����۱���13)
	int		GNo;		// ������ȣ
	char 		TEL[16]; 	// ����� ��ȭ��ȣ
	_LogITEM 	Item;		// ������ ����
};


class LogServer
{
private:

	WORD										wLastHour = -1;

	int											iaUsersOnlineServers[3];

	void										SetLogString( char * pszLog, ELogItem eType );
	void										SetLogCheatString( char * pszLog, ELogCheat eType );

	void										OnLogAging( UserData * pcUserData, int iLogID, const char * pszLog );
	void										OnLogMixture( UserData * pcUserData, int iLogID, const char * pszLog );
	void										OnLogItemGeneral( UserData * pcUserData, int iLogID, const char * pszLog );

	void										OnLogItemData( LogItem * psLog );
	void										OnLogItemTradeData( LogItemTrade * psLog );
	void										OnLogItemExpressData( LogItemGift * psLog );

	static void									OnLog( const char * pszLogName, const char * pszLog );
	static void									OnLog( User * pcUser, const char * pszLogName, const char * pszLog );
	static void									OnLogEx( const char * pszLogName, const char * pszLog, ... );

public:

	enum ELogServerType
	{
		LOGTYPEID_Unknown,
		LOGTYPEID_Aging,
		LOGTYPEID_Mixture,
		LOGTYPEID_HackUser,
		LOGTYPEID_Item,
		LOGTYPEID_ClanMoney,
		LOGTYPEID_BlessCastle,
		LOGTYPEID_LogItem = 1,
		LOGTYPEID_LogItemTrade = 2,
		LOGTYPEID_LogItemExpress = 3,
	};

	enum class ELogEventType
	{
		LOGEVENTID_Unknown,
		LOGEVENTID_AgingResult			= 10,
	};

	LogServer();
	virtual ~LogServer();

	void										CleanUpOldLogsAsync ( );
	void										OnServerLog ( std::string, EServerLogType plogType );
	BOOL										OnLogCheat( UserData * pcUserData, void * pCheatLog, BOOL bDisconnect = FALSE, BOOL bBan = FALSE);

	void										OnLogWrite( UserData * pcUserData, int iLogID, const char * pszLog, ELogServerType eType );
	void										OnLogItem( int eType, int iSize, void * psLogItem );
	void										OnLogLoadItemCharacter( UserData * pcUserData );
	void										OnLogUnloadItemCharacter( UserData * pcUserData );
	static void									OnLogItemEx( User * pcUser, int iLogID, const char * pszLog, ... );

	void										LogSocketClose( SocketData * pcSocketData, const char * pszLocation, void * p = NULL );

	static void									SQLLogEvent ( User * pcUser, enum ELogEventType eEventType, int iValue1 = 0, int iValue2 = 0, int iValue3 = 0, int iValue4 = 0);
	static void									OnLogEx( User * pcUser, int iLogID, const char * pszLog, ... );

	void										OnLogUsersOnline();

	void										HandlePacket( PacketNetUsersOnline * psPacket );

	void										AddFirewallBan( const char * pszIP, const char * p_Reason);


};

