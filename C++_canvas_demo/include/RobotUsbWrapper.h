#pragma once
#include <windows.h>
#include <vector>

#if defined(DLL_EXPORT)
#define DECLDIR __declspec(dllexport) 
#else 
#define DECLDIR __declspec(dllimport) 
#include "common.h"
#endif

enum eRbtType
{
	VoteBegin = 0,
	VoteEnd,
	WriteBegin,
	WriteEnd,
	SyncBegin,
	SyncEnd,
	UpdateStop,
	GetConfig,
	DongleScanStart,
	DongleScanStop,
	DongleDisconnect,
};

//�ص�����
typedef void (CALLBACK *UsbDataCallback_t)(const unsigned char*,int,void*);

class IRobotEventHandler
{
public:
	virtual ~IRobotEventHandler() {}

	virtual void onDeviceChanged(int type) {
		(void)type;
	}
	virtual void onGatewayStatus(int status) {
		(void)status;
	}
	virtual void onGatewayVersion(const ST_DEVICE_INFO &info) {
		(void)info;
	}
	virtual void onOnlineStatus(int *status) {
		(void)status;
	}
	virtual void onExitVote(int *status) {
		(void)status;
	}
	virtual void onExitVoteMulit(const ST_OPTION_PACKET &packet) {
		(void)packet;
	}
	virtual void onMassData(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	virtual void onGatewayError(int error) {
		(void)error;
	}
	virtual void onSetDeviceNum(int result,int customid, int classid, int deviceid) {
		(void)result;
		(void)customid;
		(void)classid;
		(void)deviceid;
	}
	virtual void onFirmwareData(int progress) {
		(void)progress;
	}
	virtual void onRawResult(int result) {
		(void)result;
	}
	virtual void onGatewayReboot() {
	}
	virtual void onUsbPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	virtual void onNodeMode(int mode) {
		(void)mode;
	}
	virtual void onSetRtc(int result) {
		(void)result;
	}
	virtual void onKeyPress(int result) {
		(void)result;
	}
	virtual void onShowPage(int count, int current) {
		(void)count;
		(void)current;
	}
	virtual void onOriginalPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//////////////////////////////dongle//////////////////////
	virtual void onDongleStatus(int status) {
		(void)status;
	}
	virtual void onDongleVersion() {
	}
	virtual void onDongleScanRes() {
	}
	virtual void onSlaveVersion() {
	}
	virtual void onSlaveStatus(int status) {
		(void)status;
	}
	virtual void onSetName() {
	}
	virtual void onSlaveError(int error) {
		(void)error;
	}
	virtual void onDongleFirmwareData(int progress) {
		(void)progress;
	}
	virtual void onDongleRawResult(int result) {
		(void)result;
	}
	virtual void onDonglePacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
};

class RobotPenController
{
public:
	//��ʼ���豸����
	virtual void ConnectInitialize(int nDeviceType,bool bTransform = false,UsbDataCallback_t pCallback = NULL, void *pContext = NULL) = 0;
	virtual void ConnectInitialize(eDeviceType nDeviceType,IRobotEventHandler *pEventHander = NULL) = 0;
	//�����豸���ӣ��ɹ����Զ��������ݽ���
	virtual int  ConnectOpen() = 0;
	//�ر��豸���ӣ��ɹ����Զ��ر����ݽ���
	virtual void ConnectDispose() = 0;
	//�ж��豸�Ƿ�������״̬
	virtual bool IsConnected() = 0;
	//��������
	virtual void Send(int nCmd) = 0;
	//����
	virtual bool Update(const char *fileName,const char *fileOther) = 0;
	//����
	virtual void SetConfig(int nCostumNum,int nClassNum,int nDeviceNum) = 0;
	//��ȡ�����豸����
	virtual int GetAvailableDeviceCount() = 0;
	//��ȡ�����豸
	virtual DWORD GetAvailableDevice() = 0;
	virtual bool GetAvailableDevice(int i,USB_INFO &usbInfo) = 0;
	//����PID��VID���豸
	virtual int Open(int nVid,int nPid,bool bAll = true) = 0;
	//���������豸
	virtual void ConnectSlave(int nID) = 0;
	//������������
	virtual void SetSlaveName(const char *name) = 0;
	//��ȡӲ����С
	virtual bool GetDeviceSize(int nDeviceType, int &nDeviceWidth, int &nDeviceHeight) = 0;
	//���û�����С
	virtual void SetCanvasSize(int nWidth,int nHeight) = 0;
	//��ȡ�豸��
	virtual int Width() = 0;
	//��ȡ�豸��
	virtual int Height() = 0;
	//��ת�Ƕ�
	virtual void Rotate(int nAngle = 0) = 0;
	//��������
	virtual void SetFilterWidth(int nPenWidth = 0) = 0;
	//��ʼͶƱ
	virtual void VoteMulit(bool bMulit = true) = 0;
};

//��ʼ���豸����
extern "C" DECLDIR void  ConnectInitialize(int nDeviceType, bool bTransform, IN UsbDataCallback_t pCallback, void *pContext);
//�����豸���ӣ��ɹ����Զ��������ݽ���
extern "C" DECLDIR int   ConnectOpen();
//�ر��豸���ӣ��ɹ����Զ��ر����ݽ���
extern "C" DECLDIR void  ConnectDispose();
//�ж��豸�Ƿ�������״̬
extern "C" DECLDIR bool  IsConnected();
//��������
extern "C" DECLDIR void  Send(int nCmd);
//����
extern "C" DECLDIR void  Update( const char *fileName,const char *fileOther );
//����
extern "C" DECLDIR void  SetConfig(int nCostumNum,int nClassNum,int nDeviceNum);
//��ȡ�����豸����
extern "C" DECLDIR int GetAvailableDeviceCount();
//��ȡ�����豸
extern "C" DECLDIR bool GetAvailableDevice(int i,USB_INFO &usbInfo);
//����PID��VID���豸
extern "C" DECLDIR int  Open(int nVid,int nPid,bool bAll = true);
//���������豸
extern "C" DECLDIR void ConnectSlave(int nID);
//������������
extern "C" DECLDIR void SetSlaveName(const char *name);
//��ȡӲ����С
extern "C" DECLDIR bool GetDeviceSize(int nDeviceType, int &nDeviceWidth, int &nDeviceHeight);

extern "C" 
{
	//��ȡʵ�� 
	DECLDIR RobotPenController* GetInstance();
	//����ʵ��
	DECLDIR void DestroyInstance();
};