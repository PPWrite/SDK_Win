#include <stdint.h>

#define NEBULA_VID		0x0483
#define P1_VID			0x0ED1

enum
{
	GATEWAY_PID	=	0x6001,
	T8A_PID		=	0x6002,
	T9A_PID		=	0x6003,
	DONGLE_PID  =	0x5001,
	P1_PID		=   0x7806,
};

enum eDeviceType
{
	GATEWAY = 0,
	NODE,
	DONGLE,
	P1,
	UNKNOWN,
};
////////////////////////////////////////NEBULA///////////////////////////////////////
#pragma pack(1)
//״̬
typedef struct robot_status
{
	uint8_t	 device_status;
	uint8_t  battery_level;
	uint8_t  note_num;
}ROBOT_STATUS;
//����
typedef struct robot_report
{
	uint8_t cmd_id;
	uint8_t reserved;
	uint8_t payload[60];
}ROBOT_REPORT;
//�汾
typedef struct st_version
{
	uint8_t version;
	uint8_t version2;
	uint8_t version3;
	uint8_t version4;
}ST_VERSION;
//�豸��Ϣ
typedef struct st_device_info
{
	ST_VERSION version;
	uint8_t  custom_num;
	uint8_t  class_num;
	uint8_t  device_num;
	uint8_t  mac[6];

}ST_DEVICE_INFO;

typedef struct st_option_packet
{
	uint8_t id;
	uint8_t option[6];

}ST_OPTION_PACKET;

typedef struct st_note_header_info
{
	uint16_t note_identifier;
	uint8_t note_number;
	uint8_t flash_erase_flag;
	uint16_t note_start_sector;
	uint32_t note_len;
	uint8_t note_time_year;
	uint8_t note_time_month;
	uint8_t note_time_day;
	uint8_t note_time_hour;
	uint8_t note_time_min;

} ST_NOTE_HEADER_INFO;

typedef struct st_note_plus_header_info
{
	uint16_t note_identifier;
	uint16_t note_number;
	uint8_t flash_erase_flag;
	uint8_t note_head_start;
	uint16_t note_start_sector;
	uint32_t note_len;
	uint8_t note_time_year;
	uint8_t note_time_month;
	uint8_t note_time_day;
	uint8_t note_time_hour;
	uint8_t note_time_min;

} ST_NOTE_PLUS_HEADER_INFO;

#pragma pack()

enum NEBULA_ERROR
{
	ERROR_NONE,
	ERROR_FLOW_NUM,
	ERROR_FW_LEN,
	ERROR_FW_CHECKSUM,
	ERROR_STATUS,
	ERROR_VERSION,
	ERROR_NAME_CONTENT,
	ERROR_NO_NOTE,
};

enum GATEWAY_STATUS
{
	NEBULA_STATUS_OFFLINE = 0,
	NEBULA_STATUS_STANDBY,
	NEBULA_STATUS_VOTE,
	NEBULA_STATUS_MASSDATA,
	NEBULA_STATUS_CONFIG,
	NEBULA_STATUS_DFU,
	NEBULA_STATUS_MULTI_VOTE,
	NEBULA_STATUS_END,              
};

enum NODE_STATUS
{
	DEVICE_POWER_OFF = 0,
	DEVICE_STANDBY,
	DEVICE_INIT_BTN,
	DEVICE_OFFLINE,
	DEVICE_ACTIVE,
	DEVICE_LOW_POWER_ACTIVE,
	DEVICE_OTA_MODE,//06
	DEVICE_OTA_WAIT_SWITCH,
	DEVICE_TRYING_POWER_OFF,
	DEVICE_FINISHED_PRODUCT_TEST,
	DEVICE_SYNC_MODE,
	DEVICE_DFU_MODE,
};

enum ROBOT_NEBULA_TYPE
{
	ROBOT_GATEWAY_STATUS			= 0x00,		//��ȡ״̬
	ROBOT_ENTER_VOTE,							//����ͶƱģʽ
	ROBOT_EXIT_VOTE,							//�˳�ͶƱģʽ
	ROBOT_EXIT_VOTE_MULIT,						//��ѡͶƱģʽ
	ROBOT_ENTER_BIG_DATA,						//���������ģʽ
	ROBOT_BIG_DATA_REPORT,						//�������ϱ�
	ROBOT_PAGE_NO,								//ҳ����ʾ
	ROBOT_EXIT_BIG_DATA,						//�˳�������ģʽ
	ROBOT_GATEWAY_ERROR,						//����
	ROBOT_NODE_MODE,							//�豸����ģʽ
	ROBOT_SET_DEVICE_NUM,						//�����豸�����
	ROBOT_ENTER_DFU,							//����dfuģʽ
	ROBOT_FIRMWARE_LEN,							//��ȡ�̼�����
	ROBOT_FIRMWARE_DATA,						//��ȡ�̼���Ϣ
	ROBOT_FIRMWARE_CHECK_SUM,					//��ȡУ���
	ROBOT_RAW_RESULT,							//У����
	ROBOT_GATEWAY_REBOOT,						//�豸����
	ROBOT_EXIT_DFU,								//�˳�dfuģʽ
	ROBOT_GATEWAY_VERSION,						//�豸�汾��
	ROBOT_ONLINE_STATUS,						//����״̬
	ROBOT_DEVICE_CHANGE,						//�豸�ı�
	ROBOT_NODE_INFO,							//�豸��Ϣ
	ROBOT_NODE_ERROR,							//node����
	ROBOT_USB_PACKET,							//�ϴ�����
	ROBOT_SET_RTC,								//����RTC
	ROBOT_KEY_PRESS,							//��������
	ROBOT_SHOW_PAGE,							//��ʾҳ��		
	ROBOT_ENTER_SYNC,							//����syncģʽ
	ROBOT_EXIT_SYNC,							//�˳�syncģʽ
	ROBOT_GET_SYNC_HEAD,						//��ȡ�洢�ʼǰ�ͷ
	ROBOT_SYNC_TRANS_BEGIN,						//�ʼǴ������ʼ
	ROBOT_ORIGINAL_PACKET,						//ԭʼ�ʼ����ݰ�
	ROBOT_SYNC_TRANS_END,						//�ʼǴ����������
};
// ��������Ϣ
typedef struct sPenInfo
{
	uint8_t nStatus;		// ��״̬
	uint16_t nX;			// ��x������
	uint16_t nY;			// ��y������
	uint16_t nPress;		// ��ѹ��
}PEN_INFO;  
//�豸��Ϣ
typedef struct usb_info
{
	char szDevName[260];
	unsigned short nVendorNum;    
	unsigned short nProductNum;         
}USB_INFO;

enum
{
	CLICK = 1,
	DBCLICK,
	PAGEUP,
	PAGEDOWN,
	CREATEPAGE,
};

////////////////////////////DONGLE////////////////////////////////
#pragma pack(1)
typedef struct st_ble_device
{
	uint8_t num;
	uint8_t rssi;
	uint8_t match;
	uint8_t addr[6];
	uint8_t device_name[18];
	uint8_t device_type;
}ST_BLE_DEVICE;
#pragma pack()

//����״̬
enum BLE_STATUS
{
	BLE_STANDBY				= 0,
	BLE_SCANNING			= 1,	//����ɨ��
	BLE_CONNECTING			= 2,	//������
	BLE_CONNECTED			= 3,	//���ӳɹ�
	BLE_ACTIVE_DISCONNECT	= 4,	//���ڶϿ�����
	BLE_RECONNECTING		= 5,	//��������
	BLE_LINK_BREAKOUT		= 6,	//��������������
	BLE_DFU_START			= 7,	//����dfuģʽ
};

enum DONGLE_DEVICE
{
	P7			= 1,
	ELITE		= 2,
	ELITE_PLUS	= 3,
	J0			= 8,
};

enum ROBOT_DONGLE_TYPE
{
	ROBOT_DONGLE_STATUS			= 0x00,		//dongele״̬
	ROBOT_DONGLE_VERSION,					//dongle�汾
	ROBOT_DONGLE_SCAN_RES,					//ɨ����
	ROBOT_SET_NAME,							//��������
	ROBOT_SLAVE_ERROR,						//������Ϣ
	ROBOT_DONGLE_FIRMWARE_DATA,				//����
	ROBOT_DONGLE_RAW_RESULT,				//�������
	ROBOT_SLAVE_STATUS,						//slave״̬
	ROBOT_SLAVE_VERSION,					//slave�汾
	ROBOT_DONGLE_PACKET,					//��������
	ROBOT_SLAVE_SYNC_BEGIN,					//��ȡ�洢�ʼǰ�ͷ
	ROBOT_SLAVE_SYNC_END,					//����ͬ��
};

enum UPDATE_TYPE
{
	DONGLE_BLE = 0,
	DONGLE_MCU,
	SLAVE_MCU,
};

enum SALVE_ERROR
{
	ERROR_SLAVE_NONE = 0,
	ERROR_OTA_FLOW_NUM,
	ERROR_OTA_LEN,
	ERROR_OTA_CHECKSUM,
	ERROR_OTA_STATUS,
	ERROR_OTA_VERSION,
};