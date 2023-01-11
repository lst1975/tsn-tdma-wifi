#include "tsn_private.h"

/* DLME     ---> Data link-layer management entity 
 * DLME-SAP ---> Data link-layer management service access point
 */

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.2, Page 59
 *                   NETWORK discovery 
 *
 * used by field equipments to find WIA-FA network
 *
 ************************************************************************************
 *
 *  FD-DMAP                         FD-DLL              FD-PHY
 *     |                              |                   |
 *     |                              |                   |
 *     |DLME_discovery_request -----> |                   | 
 *     |                              |                   |
 *     |                              |   Trigger PHY     |
 *     |                              | Channel Scanning  |
 *     |<----- DLME_discovery_confirm |                   |
 *     |                              |                   |
 ***********************************************************************************/
static tsn_boolean_e DLME_discovery_request(BitField24 bitMap)
{
}

enum{
	DLME_DISCOVERY_CONFIRM_SUCCESS=0,
	DLME_DISCOVERY_CONFIRM_NO_BEACHON,
};
struct BeaconDescription{
	Unsigned24 ChannelIndex;
	uint16_t BeaconRelativeTimeslotNum;
	uint8_t ED;
};
struct DlmeDiscoveryConfirm{
	uint8_t Status;
	uint8_t BeaconCount;
	uint16_t SuperframeLength;
	uint16_t TimeslotDuration;
	uint16_t FirstSharedTimeslotNumber;
	uint8_t SharedTimeslotNumber;
	TimeData AbsoluteTimeValue;
	struct BeaconDescription BeaconDescriptionList[0];
};
static tsn_boolean_e DLME_discovery_confirm(struct DlmeDiscoveryConfirm *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.3, Page 61
 *                   TIME synchronization 
 *
 * used by field equipments to send dual-direction time synchronization request to AD
 *
 ************************************************************************************
 *
 *  FD-DMAP                 FD-DLL              AD-DLL                    AD-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-TIME-SYNC.request|                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      |   dual-direction  |                         |
 *     |                      |    time-sync req  |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |        GACK       |                         |
 *     |                      | <-----------------|DLME-TIME-SYNC.indication|
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   | DLME-TIME-SYNC.response |
 *     |                      |   dual-direction  |<------------------------|
 *     |                      |   time-sync ack   |                         |
 *     |                      | <-----------------|                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-TIME-SYNC.confirm|                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
static tsn_boolean_e DLME_timesync_request(struct DlmeTimeSyncRequest *req)
{
}
static tsn_boolean_e DLME_timesync_response(struct DlmeTimeSyncResponse *rsp)
{
}
static tsn_boolean_e DLME_timesync_indication(struct DlmeTimeSyncIndication *ind)
{
}

static tsn_boolean_e DLME_timesync_confirm(struct DlmeTimeSyncResponse *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.4, Page 63
 *                   DEVICE join
 *
 * used by field equipments to send WIA-FA join request
 *
 ************************************************************************************
 *
 *  FD-DMAP                 FD-DLL              AD-DLL                    GW-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |   DLME-JOIN.request  |                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      | join request frame|                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |        GACK       |                         |
 *     |                      | <-----------------|  DLME-JOIN.indication   |
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   |   DLME-JOIN.response    |
 *     |                      |  dual-direction   |<------------------------|
 *     |                      |  time-sync ack    |                         |
 *     |                      | <-----------------|                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |   DLME-JOIN.confirm  |                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
static tsn_boolean_e DLME_join_request(struct DlmeJoinRequest *req)
{
}
static tsn_boolean_e DLME_join_indication(DlmeJoinIndication *ind)
{
}
static tsn_boolean_e DLME_join_response(struct DlmeJoinResponse *rsp)
{
}

static tsn_boolean_e DLME_join_confirm(struct DlmeJoinConfirm *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.5, Page 63
 *                   DEVICE status
 *
 * used by field equipments to report device status periodically
 *
 ************************************************************************************
 *
 *  FD-DMAP                 FD-DLL              AD-DLL                    GW-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-FD-STATUS.request|                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      |device status frame|                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |        NACK       |                         |
 *     |                      | <-----------------|DLME-FD-STATUS.indication|
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-FD-STATUS.confirm|                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
static tsn_boolean_e DLME_device_status_request(struct DlmeDeviceStatusRequest *req)
{
}
static tsn_boolean_e DLME_device_status_indication(struct DlmeDeviceStatusIndication *ind)
{
}
static tsn_boolean_e DLME_device_status_confirm(struct DlmeDeviceStatusConfirm *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.6, Page 68
 *                   CHANNEL condition
 *
 * used by field equipments to report WIA-FA channel condition
 *
 ************************************************************************************
 *
 *  FD-DMAP                 FD-DLL              AD-DLL                    GW-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-CHANNEL-CONDITION|                   |                         |
 *     |       .request       |                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      | channel condition |                         |
 *     |                      |       frame       |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |        NACK       |                         |
 *     |                      | <-----------------|  DLME-CHANNEL-CONDITION |
 *     |                      |                   |       .indication       |
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-CHANNEL-CONDITION|                   |                         |
 *     |       .confirm       |                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
struct ChannelConditionInfomation{
	uint8_t ChannelID;
	uint8_t LinkQuality;
	SingleFloat PacketLossRate;
	uint8_t RetryNumber;
};
struct DlmeChannelConditionRequest{
	uint8_t Count;
	struct ChannelConditionInfomation ChannelConditionInfo[0];
};
static tsn_boolean_e DLME_channel_condition_request(struct DlmeChannelConditionRequest *req)
{
}
struct DlmeChannelConditionIndication{
	uint16_t SrcAddr;
	struct ChannelConditionInfomation ChannelConditionInfo[0];
};
static tsn_boolean_e DLME_channel_condition_indication(struct DlmeChannelConditionIndication *ind)
{
}
enum{
	DLME_channel_condition_confirm_SUCCESS = 0,
	DLME_channel_condition_confirm_FAILURE,
};
struct DlmeChannelConditionConfirm{
	uint8_t Status;
};
static tsn_boolean_e DLME_device_status_confirm(struct DlmeChannelConditionConfirm *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.7, Page 69
 *                   INFORMATION get
 *
 * used by Gateway device to get attributes from field devices
 *
 ************************************************************************************
 *
 *  GW-DMAP                 AD-DLL              FD-DLL                    FD-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-INFO-GET.request |                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      | information get   |                         |
 *     |                      |  request frame    |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |                   | DLME-INFO-GET.indication|
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   |  DLME-INFO-GET.response |
 *     |                      |                   |<------------------------|
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |  information get  |                         |
 *     |                      |   response frame  |                         |
 *     |                      | <-----------------|                         |
 *     |                      |                   |                         |
 *     |                      |        GACK       |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-INFO-GET.confirm |                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
struct DlmeInformationGetRequest{
	uint8_t Handle;
	uint16_t DstAddr;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint16_t Count;
};
static tsn_boolean_e DLME_information_get_request(struct DlmeInformationGetRequest *req)
{
}
struct DlmeInformationGetIndication{
	uint16_t SrcAddr;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint16_t Count;
};
static tsn_boolean_e DLME_information_get_indication(struct DlmeInformationGetIndication *ind)
{
}
enum{
	DLME_information_get_response_SUCCESS = 0,
	DLME_information_get_response_UNSUPPORTED_ATTRIBUTE,
};
struct DlmeInformationGetResponse{
	uint16_t DstAddr;
	uint8_t Status;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint8_t AttributeValue[0];
};
static tsn_boolean_e DLME_information_get_response(struct DlmeInformationGetResponse *rsp)
{
}
enum{
	DLME_channel_condition_confirm_SUCCESS = 0,
	DLME_channel_condition_confirm_FAILURE,
};
struct DlmeInformationGetConfirm{
	uint8_t Handle;
	uint16_t SrcAddr;
	uint16_t DstAddr;
	uint8_t Status;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint16_t Count;
	uint8_t AttributeValue[0];
};
static tsn_boolean_e DLME_information_get_confirm(struct DlmeInformationGetConfirm *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.8, Page 73
 *                   INFORMATION set
 *
 * used by Gateway device to set attributes for field devices
 *
 ************************************************************************************
 *
 *  GW-DMAP                 AD-DLL              FD-DLL                    FD-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-INFO-SET.request |                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      | information set   |                         |
 *     |                      |  request frame    |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |                   | DLME-INFO-SET.indication|
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   |  DLME-INFO-SET.response |
 *     |                      |                   |<------------------------|
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |  information set  |                         |
 *     |                      |   response frame  |                         |
 *     |                      | <-----------------|                         |
 *     |                      |                   |                         |
 *     |                      |        GACK       |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |DLME-INFO-SET.confirm |                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
enum{
	DLME_information_set_option_ADD=0,
	DLME_information_set_option_DELETE,
	DLME_information_set_option_UPDATE,
};
struct DlmeInformationSetRequest{
	uint8_t Handle;
	uint16_t DstAddr;
	uint8_t AttributeOption;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint16_t Count;
	uint8_t AttributeValue[0];
};
static tsn_boolean_e DLME_information_set_request(struct DlmeInformationSetRequest *req)
{
}
struct DlmeInformationSetIndication{
	uint16_t SrcAddr;
	uint8_t AttributeOption;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint16_t Count;
	uint8_t AttributeValue[0];
};
static tsn_boolean_e DLME_information_set_indication(struct DlmeInformationSetIndication *ind)
{
}
enum{
	DLME_information_set_response_SUCCESS = 0,
	DLME_information_set_response_UNSUPPORTED_ATTRIBUTE,
	DLME_information_set_response_INVALID_PARAMETER,
};
struct DlmeInformationSetResponse{
	uint16_t SrcAddr;
	uint8_t AttributeOption;
	uint8_t AttributeID;
	uint8_t MemberID;
	uint16_t FirstStoreIndex;
	uint8_t Count;
	uint8_t Status;
};
static tsn_boolean_e DLME_information_set_response(struct DlmeInformationSetResponse *rsp)
{
}
enum{
	DLME_information_set_confirm_SUCCESS = 0,
	DLME_information_set_confirm_UNSUPPORTED_ATTRIBUTE,
	DLME_information_set_confirm_INVALID_PARAMETER,
};
struct DlmeInformationSetConfirm{
	uint8_t Handle;
	uint8_t Status;
};
static tsn_boolean_e DLME_information_set_confirm(struct DlmeInformationSetConfirm *cfm)
{
}

/***********************************************************************************
 * GB/T26790.2-2015, 8.3.9, Page 75
 *                   LEAVE
 *
 * used by Gateway device to send LEAVE request to field devices
 *
 ************************************************************************************
 *
 *  GW-DMAP                 AD-DLL              FD-DLL                    FD-DMAP
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |  DLME-LEAVE.request  |                   |                         |
 *     |   -----------------> |                   |                         |
 *     |                      |   device leave    |                         |
 *     |                      |   request frame   |                         |
 *     |                      | ----------------->|                         |
 *     |                      |                   |                         |
 *     |                      |                   |  DLME-LEAVE.indication  |
 *     |                      |                   |------------------------>|
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |DLME-LEAVE.response|                         |
 *     |                      |<------------------|                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |                      |                   |                         |
 *     |  DLME-LEAVE.confirm  |                   |                         |
 *     |<-------------------- |                   |                         |
 *     |                      |                   |                         |
 ***********************************************************************************/
struct DlmeLeaveRequest{
	union{
		uint8_t ShortAddr8;
		uint16_t ShortAddr16;
	};
};
static tsn_boolean_e DLME_leave_request(struct DlmeLeaveRequest *req)
{
}
/*
struct DlmeLeaveIndication{
};
*/
static tsn_boolean_e DLME_leave_indication(void *ind)
{
}
/*
struct DlmeLeaveResponse{
};
*/
static tsn_boolean_e DLME_leave_response(void *rsp)
{
}
enum{
	DLME_leave_confirm_SUCCESS = 0,
	DLME_leave_confirm_FAILURE
};
struct DlmeLeaveConfirm{
	uint8_t Status;
};
static tsn_boolean_e DLME_leave_confirm(struct DlmeLeaveConfirm *cfm)
{
}
	
#endif