/**************************************************************************************
 *               TDMA Time-Sensitive-Network Wifi V1.0.1
 * Copyright (C) 2022 Songtao Liu, 980680431@qq.com.  All Rights Reserved.
 **************************************************************************************
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * THE ABOVE COPYRIGHT NOTICE AND THIS PERMISSION NOTICE SHALL BE INCLUDED IN ALL
 * COPIES OR SUBSTANTIAL PORTIONS OF THE SOFTWARE. WHAT'S MORE, A DECLARATION OF 
 * NGRTOS MUST BE DISPLAYED IN THE FINAL SOFTWARE OR PRODUCT RELEASE. NGRTOS HAS 
 * NOT ANY LIMITATION OF CONTRIBUTIONS TO IT, WITHOUT ANY LIMITATION OF CODING STYLE, 
 * DRIVERS, CORE, APPLICATIONS, LIBRARIES, TOOLS, AND ETC. ANY LICENSE IS PERMITTED 
 * UNDER THE ABOVE LICENSE. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF 
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO 
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES 
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *
 **************************************************************************************
 *                              
 *                    https://github.com/lst1975/TDMA-TSN-Wifi
 *                              
 **************************************************************************************
 */
 
#include "tsn_private.h"

enum ad_state{
  AD_STATE_init,
  AD_STATE_idle,
  AD_STATE_s1,
  AD_STATE_s2,
  AD_STATE_s3,
  AD_STATE_s4,
  AD_STATE_s5,
  AD_STATE_s6,
  AD_STATE_s7,
  AD_STATE_s8,
};

/***********************************************************************************
 * GB/T26790.2-2015, 8.5.1, Page 85 
 *                   Access Device DLL State Machine 
 *
 ************************************************************************************
 *                                           |
 *                                           |
 *                                           |
 *                                           V
 *                                        ++++++++
 *                                        +      +
 *                                        + INIT +
 *                                        +      +
 *               PHY-DATA.indication      ++++++++
 *                        \                  |
 *                         \                 |
 *                          \                |
 *                           \               |
 *                           _v              V
 *               ++++++       T1          ++++++++                      ++++++
 *               +    + <---------------- +      + -------------------->+    +          
 *               + S1 +                   + IDLE +                      + S2 +
 *               +    + ----------------> +      + <--------------------+    +
 *               ++++++   T2||T3||...T8   ++++++++    T10||T11||...T15  ++++++
 *                                         ^    |
 *                                         |    |
 *                                         |    |
 *                                         |    |
 *                                         |    |
 *                                      T17|    | T16
 *                                         |    |
 *                                         |    |
 *                                         |    v
 *                                        ++++++++
 *                                        +  S3  +
 *                                        ++++++++
 *
 *
 ***********************************************************************************/
enum{
  Trigger_type_none,
  Trigger_type_state,
  Trigger_type_slot_timeout,
};
struct access_device{
  enum gw_state State;
  int triggerType;
  int stateTrigger;
  int toBuildFrameType;
};
int gw_ad_state_change(struct access_device *ad, int state)
{
  ad->triggerType   = Trigger_type_state;
  ad->stateTrigger  = state;
  return gw_ad_state_machine(ad, NULL);
}
int gw_ad_state_machine(struct access_device *ad, void *dlpdu)
{
  int FrameType;
  
  switch (ad->State)
  {
    case AD_STATE_init:
      ad->State = AD_STATE_idle;
    case AD_STATE_idle:
      if (dlpdu == NULL && ad->triggerType != Trigger_type_none)
      {
        ad->triggerType = Trigger_type_none;
        if (ad->triggerType == Trigger_type_state)
        {
          if (ad->stateTrigger == AD_STATE_s2)
            ad->State = AD_STATE_s2;
          else
            return FALSE;
          break;
        }
        else if (ad->triggerType == Trigger_type_slot_timeout)
        {
          if (linkType == LINK_TYPE_transmit)
          {
            void *data = GetDLPDUFromQueue();
            Phy_set_RF_mode(LINK_MODE_transmit);
            PhyDataRequet(data);
          }
          else if (linkType == LINK_TYPE_receive)
          {
            Phy_set_RF_mode(LINK_MODE_receive);
          }
          else if (linkType == LINK_TYPE_shared_transmit)
          {
            PHYSendWithBackoff(dlpdu);
          }
          ad->State = AD_STATE_s3;
          break;
        }
      }
      /* ===> PhyData.indication() */
      FrameType = GetFrameType(dlpdu);
      ad->State = AD_STATE_s1;
    case AD_STATE_s1:
      if (FrameType == FRAME_TYPE_JoinRequest)
      {
        uint64_t PhyAddr;
        uint64_t SecMaterial;
        PhyAddr = DLME_JoinRequestGetPhyAddr(dlpdu);
        SecMaterial = DLME_JoinRequestGetSecurityMaterial(dlpdu);
        DLME_join_indication(PhyAddr, SecMaterial);
        ad->State = AD_STATE_idle;
      }
      else if (FrameType == FRAME_TYPE_Data)
      {
        uint16_t SrcAddr = GetSrcAddr(dlpdu);
        int PayloadLength = GetPayloadLength(dlpdu);
        uint8_t Payload = GetPayload(dlpdu);
        /********************************************************
          TODO: GENERATE new data
        ********************************************************/
        void *data = generate_dlde_data();
        DLDE_data_indication(SrcAddr, data, PayloadLength, Payload);
        ad->State = AD_STATE_idle;
      }
      else if (FrameType == FRAME_TYPE_RemoteAttributeSetResponse)
      {
        DLME_information_set_confirm(Handle, Status);
        ad->State = AD_STATE_idle;
      }
      else if (FrameType == FRAME_TYPE_DeviceStatusReport)
      {
        DLME_device_status_indication(PowerSupplyStatus);
        ad->State = AD_STATE_idle;
      }
      else if (FrameType == FRAME_TYPE_ChannelConditionReport)
      {
        DLME_channel_condition_indication(ShortAddr, Count, ChannelCondition);
        ad->State = AD_STATE_idle;
      }
      else if (FrameType == FRAME_TYPE_TwoWayTimeSynchronizationRequest)
      {
        DLME_timesync_indication(SrcAddr, FieldDeviceTimeValue);
        ad->State = AD_STATE_idle;
      }
      else
      {
        /********************************************************
          TODO: report invalid frame
        ********************************************************/
        return FALSE;
      }
      break;
    case AD_STATE_s2:
      /********************************************************
        DLME-JOIN.response()
        TODO: build_join_response
      ********************************************************/
      if (ad->toBuildFrameType == FRAME_TYPE_JoinResponse)
      {
        uint8_t *data = BuildFrame(dlpdu, ad->toBuildFrameType);
        DLME_join_response(data);
        ad->State = AD_STATE_idle;
      }
      else if (ad->toBuildFrameType == FRAME_TYPE_RemoteAttributeSetRequest)
      {
        uint8_t *data = BuildFrame(dlpdu, ad->toBuildFrameType);
        DLME_information_set_request(data);
        ad->State = AD_STATE_idle;
      }
      else if (ad->toBuildFrameType == FRAME_TYPE_RemoteAttributeGetRequest)
      {
        uint8_t *data = BuildFrame(dlpdu, ad->toBuildFrameType);
        DLME_information_get_request(data);
        ad->State = AD_STATE_idle;
      }
      else if (ad->toBuildFrameType == FRAME_TYPE_Data)
      {
        uint8_t *data = BuildFrame(dlpdu, ad->toBuildFrameType);
        DLDE_data(data);
        ad->State = AD_STATE_idle;
      }
      else if (ad->toBuildFrameType == FRAME_TYPE_TwoWayTimeSynchronizationResponse)
      {
        uint8_t *data = BuildFrame(dlpdu, ad->toBuildFrameType);
        DLME_timesync_response(data);
        ad->State = AD_STATE_idle;
      }
      else if (ad->toBuildFrameType == FRAME_TYPE_LeaveRequest)
      {
        uint8_t *data = BuildFrame(dlpdu, ad->toBuildFrameType);
        DLME_leave_request(data);
        ad->State = AD_STATE_idle;
      }
      else
      {
        /********************************************************
          TODO: report invalid frame
        ********************************************************/
        return FALSE;
      }
      break;

    /* ===> TransmitCompleteISR() || ReceiveCompleteISR() */
    case AD_STATE_s3:
      ad->State = AD_STATE_idle;
      break;
    default:      
      /********************************************************
        TODO: report invalid frame
      ********************************************************/
      return FALSE;
  }
  
  return TRUE;
}
