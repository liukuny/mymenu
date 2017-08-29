#ifndef _GCONST_H
#define _GCONST_H

//----------------------------------------------------------------------------
//-- ��������:

//�ͻ��� -> ��������: (ռ�ô����: 1 .. 10000)
const int CS_DEBUG                      = 1;        //����							
//const int CS_ACK                        = 2;        //Ӧ�������			------------------------------------	*
//const int CS_GET_USEROFFLINEFILE        = 3;        //��ȡ�û������ļ���Ϣ	------------------------------------	*
const int CS_LOGIN                      = 4;        //��¼					------------------------------------	*
const int CS_LOGOUT                     = 5;        //ע��					------------------------------------	*
const int CS_KEEP_ALIVE                 = 6;        //����					------------------------------------	*
//const int CS_USER_UPDATE                = 7;        //�û���������			------------------------------------	*
//const int CS_USER_VERSION				= 8;        //�û��汾���			------------------------------------	*
//const int CS_DEL_USEROFFLINEFILE        = 10;       //ɾ���û������ļ���Ϣ	------------------------------------	*
const int CS_REONLINE                   = 11;       //����					------------------------------------	*
const int CS_OFFLINE                    = 12;       //����					------------------------------------	*
//const int CS_GET_FRIEND_MSGS            = 13;       //��ȡ�ͺ��Ѳ�����ص���Ϣ(�类�Ӻ���֪ͨ��)
//const int CS_GET_ALL_USERS              = 14;       //��ȡ���к���/����
//const int CS_GET_ALL_ADDSELFFRIENDS     = 15;       //��ȡ���м��Լ�Ϊ���ѵ��û�
//const int CS_GET_USER_INFO              = 16;       //��ȡ�û�����
//const int CS_MODIFY_USER_INFO           = 17;       //�޸��û�����
//const int CS_GET_USER_OL_INFO           = 18;       //��ȡ�û���������Ϣ
//const int CS_GET_XIAOXINGSHI_INFO       = 19;       //��ȡС��ʹ��Ϣ
//const int CS_FIND_OL_USERS              = 20;       //����˭������
//const int CS_FIND_USERS                 = 21;       //�����û�
const int CS_SEND_GROUPMSG              = 22;       //���������ת��ȺѶϢ
const int CS_FW_PACKET                  = 23;       //���������ת��˽��ѶϢ
const int CS_GET_GROUPMSG               = 24;       //�������ط�����ȺѶϢ
const int CS_GET_PERSONALMSG            = 25;       //�������ط�����˽��ѶϢ
//const int CS_SAVE_OFFLINE_MSGS          = 26;       //����Ĵ���û�ѶϢ
//const int CS_GET_OFFLINE_MSGS           = 27;       //��ȡ�Ĵ���û�ѶϢ
//const int CS_GET_SYS_MSGS               = 28;       //��ȡϵͳ��Ϣ
//const int CS_GET_AD_DATA                = 29;       //��ȡ�������
//const int CS_GET_VERIFY_CODE            = 30;       //��ȡһ����֤��
const int CS_GET_ONLINEUSER             = 31;       //��ȡ�����û�
const int CS_DOWNLOAD_IMAGE				= 32;		//�û�����ͼƬ��Ϣ
const int CS_UPLOAD_IMAGE				= 33;		//�û��ϴ�ͼƬ��Ϣ
const int CS_GET_USER_MEMBERINFO		= 34;		//��ȡ�û���Ա����
const int CS_SET_USER_ONLINESTATE		= 35;		//�����û�����״̬
const int CS_GET_USERDISTROYMSG			= 36;		//�û���ȡ��ʷ��Ϣ
const int CS_RECVDATA					= 10;        // �յ��ͻ�������							
const int CS_GETCONTACT_ACK				= 37;		//�û�Ӧ���ȡ��ϵ��
const int CS_GROUPMSG_ACK				= 38;		//�û�Ӧ��˽����Ϣ
const int CS_USERMSG_ACK				= 39;		//�û�Ӧ��Ⱥ��Ϣ
const int CS_USEONLINENOTIFY_ACK		= 40;		//�û�Ӧ��֪ͨ��ϵ������

//
////�������� -> �ͻ���: (ռ�ô����: 10001 .. 20000)
const int SC_ACK                        = 10001;    //Ӧ��ͻ���
const int SC_LOGIN						= 10004;			//��¼					------------------------------------	*
const int SC_LOGOUT						= 10005;        //ע��					------------------------------------	*
const int SC_KEEP_ALIVE					= 10006;        //����					------------------------------------	*
const int SC_RECVMSG					= 10007;    //�����������յ��ͻ�����Ϣ
const int SC_SEND_CONTACT				= 10015;    //������������ϵ��
const int SC_ONLINENOTIFY				= 10016;    //������������ϵ������֪ͨ
const int SC_GET_USERDISTROYMSG			= 10017;	//�û���ȡ��ʷ��Ϣ
const int SC_UPLOAD_IMAGEFILE			= 10018;	//�û��ϴ�ͼƬ��Ϣ
const int SC_DOWNLOAD_IMAGEFILE			= 10019;	//�û�����ͼƬ��Ϣ
const int SC_GETGMSG_NOTIFY             = 10008;    //����������Ⱥ��Ϣ֪ͨ
const int SC_GETUMSG_NOTIFY             = 10009;    //����������˽����Ϣ֪ͨ
//const int SC_RE_KEEP_ALIVE              = 10005;    //�������յ�����󷵻ص��û�״̬�б�
//const int SC_OTHER_USER_BC              = 10006;    //�����û�����Ϣ�㲥
//const int SC_FW_SEND_MSG                = 10007;    //ת���û�ѶϢ
//const int SC_SYS_MESSAGE                = 10008;    //ϵͳ��Ϣ
//const int SC_BE_ADDED_FRIEND            = 10009;    //֪ͨ�û����Ӻ���
//const int SC_VERIFY_MSG                 = 10010;    //�����û��ύ�������֤��Ϣ
//const int SC_BE_PASSED_VERIFY           = 10011;    //֪ͨ�û��ӶԷ�Ϊ����ʱ���Է���ͨ�������֤
//const int SC_RE_GET_FLT_WORDS           = 10012;    //Ӧ�� ��ȡ���˹ؼ���
//const int SC_FW_PACKET                  = 10013;    //ת�����ݰ�
//const int SC_SEND_GROUPMSG              = 10014;    //������ת��ȺѶϢ
//
////=================================================================================================
////			C <==> C
//// �ͻ��� -> �ͻ���: (ռ�ô����: 20001 .. 30000)
////=================================================================================================
//const int CC_ACTIONCODE_BEGIN           = 20001;    // �ͻ��˶���������ʼ��
//const int CC_SHACKHAND                  = 20001;    // �ͻ�����������
//const int CC_ACK_SHACKHAND              = 20002;    // �ͻ�����������Ӧ��
//const int CC_IMMSG						= 20003;    // �ͻ��˼�ʱ��Ϣ
//const int CC_ACK     					= 20004;    // �ͻ��˼�ʱ��ϢӦ��
//const int CC_GROUPMSG					= 20005;    // �ͻ���Ⱥ��ʱ��Ϣ
//const int CC_GROUPMSG_ACK				= 20006;    // �ͻ���Ⱥ��ʱ��ϢӦ��
//const int CC_NOTIFYONLINE				= 20007;    // �ͻ�������֪ͨ
//const int CC_NOTIFYONLINE_ACK			= 20008;    // �ͻ�������֪ͨӦ��
//const int CC_SENDFILE_QUESTION			= 20009;    // �ͻ������������ļ�����
//const int CC_SENDFILE_ACK				= 20010;    // �ͻ������������ļ�����Ӧ��
//const int CC_RECVFILE_QUESTION			= 20011;    // �ͻ������������ļ�����
//const int CC_RECVFILE_ACK				= 20012;    // �ͻ������������ļ�����Ӧ��
//const int CC_REFUSEFILE_QUESTION		= 20013;    // �ͻ��˾ܾ������ļ�����
//const int CC_REFUSEFILE_ACK				= 20014;    // �ͻ��˾ܾ������ļ�����Ӧ��
//const int CC_ACTIONCODE_END             = 21000;    // �ͻ��˶������������
//


////----------------------------------------------------------------------------
////-- ����ߴ糣��:
//const int MAX_SERVERNAME_SIZE           = 20;       // �������� 
//const int MAX_SERVERKIND_SIZE           = 20;       // �������� 
//
const int MAX_USERNAME_SIZE             = 31;
//const int MAX_NICKNAME_SIZE             = 30;
//const int MAX_PASSWORD_SIZE             = 24;
//const int MAX_EMAIL_SIZE                = 24;
//const int MAX_HOMEPAGE_SIZE             = 36;
//const int MAX_TEL_SIZE                  = 20;
//const int MAX_TRUENAME_SIZE             = 15;
//const int MAX_ISPNAME_SIZE              = 11;
//const int MAX_CAREER_SIZE               = 15;
//const int MAX_COUNTRY_SIZE              = 15;
//const int MAX_PROVINCE_SIZE             = 11;
//const int MAX_CITY_SIZE                 = 9;
//const int MAX_ADDRESS_SIZE              = 36;
//const int MAX_POSTCODE_SIZE             = 8;
//const int MAX_NOTE_SIZE                 = 60;
//
//const int MAX_PWD_PROT_CERT_NO_SIZE     = 48;
//const int MAX_PWD_PROT_QUESTION_SIZE    = 48;
//const int MAX_PWD_PROT_ANSWER_SIZE      = 48;
//const int MAX_PWD_PROT_EMAIL_SIZE       = 48;
//
const int MAX_HASHED_PWD_SIZE           = 28;
//const int MAX_SEARCH_TEXT_SIZE          = 32;
//const int MAX_FILENAME_SIZE             = 96;
//const int MAX_FILE_COMM_SIZE            = 64;
//const int MAX_EXIT_KEY_SIZE             = 20;
//const int MAX_SYS_MSG_SIZE              = 300;
//const int MAX_USER_BC_MSG_SIZE          = 200;
//const int MAX_ADD_FRI_VFY_MSG_SIZE      = 50;
//const int MAX_VERSION_SIZE              = 16;
//const int MAX_AD_HINT_SIZE              = 128;
//const int MAX_AD_URL_SIZE               = 128;
//const int MAX_AD_GROUP_NOTE_SIZE        = 64;
//const int MAX_AD_NOTE_SIZE              = 64;
//const int MAX_FILTER_WORD_SIZE          = 21;
//const int MAX_IP_SIZE                   = 15;
//
////----------------------------------------------------------------------------
//// ʱ���ַ�����ʽ����󳤶�
//const int MAX_TIME_SIZE                 = 20;
////----------------------------------------------------------------------------
//// ��ȡ���ߺ��ѵ�������
//const int MAX_GETONLINEUSER_NUMBER		= 500;
////----------------------------------------------------------------------------
//// ���������Ϣ����ַ���
//const int MAX_SAVEOFFLINEMSG_NUMBER		= 1600; // 
////----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// ���ɱ��(50���ֽ�)
const int MAX_BARIDNAME_SIZE = 50;
// ������֤��(20���ֽ�)
const int MAX_BARCHECKCODE_SIZE = 20;
// ��Ϸ�б����ʱ��(20���ֽ�)
const int MAX_GAMELISTUPDATETIME_SIZE = 20;
//----------------------------------------------------------------------------
// �����������е�Ψһ���(20���ֽ�)
const int MAX_MACHINENAME_SIZE = 20;


// ���ش���
#define RESULTT_SUCESS    0    // �ɹ�
//#define LOGINRET_NOUSER    10   // �޴��û� 

// ��¼���ش���
#define LOGINRET_SUCESS    0    // �ɹ�
#define LOGINRET_NOUSER    10   // �޴��û� 
#define LOGINRET_ERRPASS   20   // �������
#define LOGINRET_NOONLINE   30   // ���û�������

// ������ش���
#define SERVERERRORCODE_NOBARID				-2   // �޴��û� 
#define SERVERERRORCODE_ERRORCHECKCODE		-3   // У������� 
#define SERVERERRORCODE_EXCEPTION			-4   // �쳣���� 
#define SERVERERRORCODE_MEMNEW  -5   // �ڴ������� 
#define SERVERERRORCODE_OTHERERR  -1   // �������� 

//// ���ҵ�񷵻ش���
//// ���ݳ���(���������Ϣҵ��)
//#define RET_WORK_ERR_LENGTHOUT	100
//
//// ��ϵ������
//#define CONTACTBASEDATA_TYPE_FRIEND		1		// ����
//#define CONTACTBASEDATA_TYPE_FRIENDED	2		// ����Ϊ���ѵ��û�
#define PROTOCOL_COMMON_SPLIT_CHAR   '\3'   // Э��ͨ�÷ָ��
#define PROTOCOL_COMMON_SPLIT_CHAR1   '|'   // Э��ͨ�÷ָ��1��
#define PROTOCOL_COMMON_SPLIT_LCHAR   '{'   // Э��ͨ�ø�����ָ��
#define PROTOCOL_COMMON_SPLIT_RCHAR   '}'   // Э��ͨ�ø����ҷָ��

//----------------------------------------------------------------------------
 
#endif
