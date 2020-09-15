/* Interface to Python */


int pc_uart_dataread(u16 Offset, u16 *value);
int pc_uart_datawrite(u16 Offset, u16 value);

//GSW_return_t GSW_VersionGet(void *cdev, GSW_version_t *parm);
//GSW_return_t pyGSW_VersionGet(void *cdev, 

int init();

int r(unsigned short addr);
int w(unsigned short addr, unsigned short value);
int mdiow ( unsigned char phyid, unsigned char addr, unsigned short value);
unsigned short mdior ( unsigned char phyid, unsigned char addr);

/*
void pce_pinit(int idx, int enb);
void pce_portId(int enb, int p);
void pce_act_forwarding(int act, int portmap);
*/
int pyGSW_PceRuleWrite(int pattern_nIndex, ltq_bool_t pattern_bEnable, ltq_bool_t pattern_bPortIdEnable, \
       u8 pattern_nPortId, ltq_bool_t pattern_bDSCP_Enable, u8 pattern_nDSCP, ltq_bool_t pattern_bPCP_Enable, \
       u8 pattern_nPCP, ltq_bool_t pattern_bSTAG_PCP_DEI_Enable, u8 pattern_nSTAG_PCP_DEI, \
       ltq_bool_t pattern_bPktLngEnable, u16 pattern_nPktLng, u16 pattern_nPktLngRange, \
       ltq_bool_t pattern_bMAC_DstEnable, u8 pattern_nMAC_Dst0, u8 pattern_nMAC_Dst1, u8 pattern_nMAC_Dst2, u8 pattern_nMAC_Dst3, u8 pattern_nMAC_Dst4, u8 pattern_nMAC_Dst5, \
       u16 pattern_nMAC_DstMask, ltq_bool_t pattern_bMAC_SrcEnable, u8 pattern_nMAC_Src0, u8 pattern_nMAC_Src1, u8 pattern_nMAC_Src2, u8 pattern_nMAC_Src3, u8 pattern_nMAC_Src4, u8 pattern_nMAC_Src5, \
       u16 pattern_nMAC_SrcMask, ltq_bool_t pattern_bAppDataMSB_Enable, u16 pattern_nAppDataMSB, \
       ltq_bool_t pattern_bAppMaskRangeMSB_Select, u16 pattern_nAppMaskRangeMSB, \
       ltq_bool_t pattern_bAppDataLSB_Enable, u16 pattern_nAppDataLSB, ltq_bool_t pattern_bAppMaskRangeLSB_Select, \
       u16 pattern_nAppMaskRangeLSB, GSW_PCE_IP_t pattern_eDstIP_Select, u32 pattern_nDstIPipv4, \
       u8 pattern_nDstIPipv60, u8 pattern_nDstIPipv61, u8 pattern_nDstIPipv62, u8 pattern_nDstIPipv63, u8 pattern_nDstIPipv64, u8 pattern_nDstIPipv65, u8 pattern_nDstIPipv66, u8 pattern_nDstIPipv67, \
       u32 pattern_nDstIP_Mask, GSW_PCE_IP_t pattern_eSrcIP_Select, u32 pattern_nSrcIPipv4, \
       u8 pattern_nSrcIPipv60, u8 pattern_nSrcIPipv61, u8 pattern_nSrcIPipv62, u8 pattern_nSrcIPipv63, u8 pattern_nSrcIPipv64, u8 pattern_nSrcIPipv65, u8 pattern_nSrcIPipv66, u8 pattern_nSrcIPipv67, \
       u32 pattern_nSrcIP_Mask, ltq_bool_t pattern_bEtherTypeEnable, u16 pattern_nEtherType, \
       u16 pattern_nEtherTypeMask, ltq_bool_t pattern_bProtocolEnable, u8 pattern_nProtocol, \
       u8 pattern_nProtocolMask, ltq_bool_t pattern_bSessionIdEnable, u16 pattern_nSessionId, \
       ltq_bool_t pattern_bVid, u16 pattern_nVid, ltq_bool_t pattern_bVidRange_Select, \
       u16 pattern_nVidRange, ltq_bool_t pattern_bSLAN_Vid, u16 pattern_nSLAN_Vid, \
       GSW_PCE_ActionTrafficClass_t action_eTrafficClassAction, u8 action_nTrafficClassAlternate, \
       GSW_PCE_ActionIGMP_Snoop_t action_eSnoopingTypeAction, GSW_PCE_ActionLearning_t action_eLearningAction, \
       GSW_PCE_ActionIrq_t action_eIrqAction, GSW_PCE_ActionCrossState_t action_eCrossStateAction, \
       GSW_PCE_ActionCriticalFrame_t action_eCritFrameAction, GSW_PCE_ActionTimestamp_t action_eTimestampAction, \
       GSW_PCE_ActionPortmap_t action_ePortMapAction, u32 action_nForwardPortMap, \
       ltq_bool_t action_bRemarkAction, ltq_bool_t action_bRemarkPCP, ltq_bool_t action_bRemarkSTAG_PCP, \
       ltq_bool_t action_bRemarkSTAG_DEI, ltq_bool_t action_bRemarkDSCP, ltq_bool_t action_bRemarkClass, \
       GSW_PCE_ActionMeter_t action_eMeterAction, u8 action_nMeterId, ltq_bool_t action_bRMON_Action, \
       u8 action_nRMON_Id, GSW_PCE_ActionVLAN_t action_eVLAN_Action, u16 action_nVLAN_Id, \
       u8 action_nFId, GSW_PCE_ActionVLAN_t action_eSVLAN_Action, u16 action_nSVLAN_Id, \
       GSW_PCE_ActionCrossVLAN_t action_eVLAN_CrossAction, ltq_bool_t action_bCVLAN_Ignore_Control, \
       ltq_bool_t action_bPortBitMapMuxControl, ltq_bool_t action_bPortTrunkAction, \
       ltq_bool_t action_bPortLinkSelection, ltq_bool_t action_bFlowID_Action, u16 action_nFlowID);
int pyGSW_PceRuleRead(int idx);
/*
int pyGSW_PceRuleReadf(int idx, int enb);
*/
/**************************************************/
/*         Auto Code Generated                    */
/**************************************************/ 

int pyGSW_8021X_EAPOL_RuleGet(u8 nForwardPortId);
int pyGSW_8021X_EAPOL_RuleSet(GSW_portForward_t eForwardPort, u8 nForwardPortId);
int pyGSW_8021X_PortCfgGet(u32 nPortId);
int pyGSW_8021X_PortCfgSet(u32 nPortId, GSW_8021X_portState_t eState);
int pyGSW_MAC_TableClear();
int pyGSW_MAC_TableEntryAdd(u32 nFId, u32 nPortId, int nAgeTimer, u16 nSVLAN_Id, ltq_bool_t bStaticEntry, \
          u8 nTrafficClass, u8 nMAC0, u8 nMAC1, u8 nMAC2, u8 nMAC3, u8 nMAC4, u8 nMAC5);
int pyGSW_MAC_TableEntryQuery(u8 nMAC0, u8 nMAC1, u8 nMAC2, u8 nMAC3, u8 nMAC4, u8 nMAC5, u32 nFId);
int pyGSW_MAC_TableEntryRead(ltq_bool_t bInitial);
int pyGSW_MAC_TableEntryRemove(u32 nFId, u8 nMAC0, u8 nMAC1, u8 nMAC2, u8 nMAC3, u8 nMAC4, u8 nMAC5);
int pyGSW_STP_BPDU_RuleGet();
int pyGSW_STP_BPDU_RuleSet(GSW_portForward_t eForwardPort, u8 nForwardPortId);
int pyGSW_STP_PortCfgGet(u8 nPortId);
int pyGSW_STP_PortCfgSet(u8 nPortId, u32 nFId, GSW_STP_PortState_t ePortState);
int pyGSW_TrunkingCfgGet();
int pyGSW_TrunkingCfgSet(ltq_bool_t bIP_Src, ltq_bool_t bIP_Dst, ltq_bool_t bMAC_Src, ltq_bool_t bMAC_Dst);
int pyGSW_TrunkingPortCfgGet(u32 nPortId);
int pyGSW_TrunkingPortCfgSet(ltq_bool_t bAggregateEnable, u32 nPortId, u32 nAggrPortId);
int pyGSW_SVLAN_CfgGet();
int pyGSW_SVLAN_CfgSet(u16 nEthertype);
int pyGSW_SVLAN_PortCfgGet(u8 nPortId);
int pyGSW_SVLAN_PortCfgSet(u8 nPortId, ltq_bool_t bSVLAN_TagSupport, ltq_bool_t bSVLAN_MACbasedTag, u16 nPortVId, \
          ltq_bool_t bVLAN_ReAssign, GSW_VLAN_MemberViolation_t eVLAN_MemberViolation, GSW_VLAN_Admit_t eAdmitMode);
int pyGSW_VLAN_Member_Init(u32 nPortMemberMap, u32 nEgressTagMap);
int pyGSW_VLAN_IdCreate(u16 nVId, u32 nFId);
int pyGSW_VLAN_IdDelete(u16 nVId);
int pyGSW_VLAN_IdGet(u16 nVId);
int pyGSW_VLAN_PortCfgGet(u8 nPortId);
int pyGSW_VLAN_PortCfgSet(u8 nPortId, u16 nPortVId, ltq_bool_t bVLAN_UnknownDrop, ltq_bool_t bVLAN_ReAssign, \
          GSW_VLAN_MemberViolation_t eVLAN_MemberViolation, GSW_VLAN_Admit_t eAdmitMode, ltq_bool_t bTVM);
int pyGSW_VLAN_PortMemberAdd(u16 nVId, u32 nPortId, ltq_bool_t bVLAN_TagEgress);
int pyGSW_VLAN_PortMemberRead(ltq_bool_t bInitial);
int pyGSW_VLAN_PortMemberRemove(u16 nVId, u32 nPortId);
int pyGSW_VLAN_ReservedAdd(u16 nVId);
int pyGSW_VLAN_ReservedRemove(u16 nVId);
int pyGSW_QoS_ClassDSCP_Get();
int pyGSW_QoS_ClassDSCP_Set(u8 nTrafficClass, u8 nDSCP0, u8 nDSCP1, u8 nDSCP2, u8 nDSCP3, u8 nDSCP4, u8 nDSCP5, \
          u8 nDSCP6, u8 nDSCP7, u8 nDSCP8, u8 nDSCP9, u8 nDSCP10, u8 nDSCP11, u8 nDSCP12, u8 nDSCP13, \
          u8 nDSCP14, u8 nDSCP15);
int pyGSW_QoS_ClassPCP_Get();
int pyGSW_QoS_ClassPCP_Set(u8 nTrafficClass, u8 nPCP0, u8 nPCP1, u8 nPCP2, u8 nPCP3, u8 nPCP4, u8 nPCP5, \
          u8 nPCP6, u8 nPCP7, u8 nPCP8, u8 nPCP9, u8 nPCP10, u8 nPCP11, u8 nPCP12, u8 nPCP13, u8 nPCP14, \
          u8 nPCP15);
int pyGSW_QoS_DSCP_ClassGet();
int pyGSW_QoS_DSCP_ClassSet(u32 nDSCP, u8 nTrafficClass0, u8 nTrafficClass1, u8 nTrafficClass2, u8 nTrafficClass3, \
          u8 nTrafficClass4, u8 nTrafficClass5, u8 nTrafficClass6, u8 nTrafficClass7, u8 nTrafficClass8, \
          u8 nTrafficClass9, u8 nTrafficClass10, u8 nTrafficClass11, u8 nTrafficClass12, u8 nTrafficClass13, \
          u8 nTrafficClass14, u8 nTrafficClass15, u8 nTrafficClass16, u8 nTrafficClass17, u8 nTrafficClass18, \
          u8 nTrafficClass19, u8 nTrafficClass20, u8 nTrafficClass21, u8 nTrafficClass22, u8 nTrafficClass23, \
          u8 nTrafficClass24, u8 nTrafficClass25, u8 nTrafficClass26, u8 nTrafficClass27, u8 nTrafficClass28, \
          u8 nTrafficClass29, u8 nTrafficClass30, u8 nTrafficClass31, u8 nTrafficClass32, u8 nTrafficClass33, \
          u8 nTrafficClass34, u8 nTrafficClass35, u8 nTrafficClass36, u8 nTrafficClass37, u8 nTrafficClass38, \
          u8 nTrafficClass39, u8 nTrafficClass40, u8 nTrafficClass41, u8 nTrafficClass42, u8 nTrafficClass43, \
          u8 nTrafficClass44, u8 nTrafficClass45, u8 nTrafficClass46, u8 nTrafficClass47, u8 nTrafficClass48, \
          u8 nTrafficClass49, u8 nTrafficClass50, u8 nTrafficClass51, u8 nTrafficClass52, u8 nTrafficClass53, \
          u8 nTrafficClass54, u8 nTrafficClass55, u8 nTrafficClass56, u8 nTrafficClass57, u8 nTrafficClass58, \
          u8 nTrafficClass59, u8 nTrafficClass60, u8 nTrafficClass61, u8 nTrafficClass62, u8 nTrafficClass63);
int pyGSW_QoS_DSCP_DropPrecedenceCfgGet();
int pyGSW_QoS_DSCP_DropPrecedenceCfgSet(u8 nDSCP, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence0, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence1, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence2, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence3, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence4, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence5, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence6, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence7, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence8, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence9, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence10, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence11, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence12, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence13, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence14, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence15, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence16, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence17, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence18, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence19, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence20, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence21, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence22, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence23, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence24, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence25, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence26, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence27, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence28, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence29, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence30, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence31, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence32, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence33, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence34, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence35, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence36, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence37, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence38, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence39, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence40, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence41, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence42, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence43, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence44, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence45, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence46, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence47, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence48, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence49, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence50, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence51, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence52, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence53, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence54, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence55, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence56, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence57, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence58, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence59, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence60, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence61, \
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence62, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence63);
int pyGSW_QoS_FlowctrlCfgGet();
int pyGSW_QoS_FlowctrlCfgSet(u32 nFlowCtrlNonConform_Min, u32 nFlowCtrlNonConform_Max, u32 nFlowCtrlConform_Min, \
          u32 nFlowCtrlConform_Max);
int pyGSW_QoS_FlowctrlPortCfgGet(u32 nPortId);
int pyGSW_QoS_FlowctrlPortCfgSet(u32 nPortId, u32 nFlowCtrl_Min, u32 nFlowCtrl_Max);
int pyGSW_QoS_MeterCfgGet(u32 nMeterId);
int pyGSW_QoS_MeterCfgSet(ltq_bool_t bEnable, u32 nMeterId, u32 nCbs, u32 nEbs, u32 nRate);
int pyGSW_QoS_MeterPortAssign(u32 nMeterId, GSW_direction_t eDir, u32 nPortIngressId, u32 nPortEgressId);
int pyGSW_QoS_MeterPortDeassign(u32 nMeterId, u32 nPortIngressId, u32 nPortEgressId);
int pyGSW_QoS_MeterPortGet(ltq_bool_t bInitial);
int pyGSW_QoS_PCP_ClassGet();
int pyGSW_QoS_PCP_ClassSet(u8 nPCP, u8 nTrafficClass0, u8 nTrafficClass1, u8 nTrafficClass2, u8 nTrafficClass3, \
          u8 nTrafficClass4, u8 nTrafficClass5, u8 nTrafficClass6, u8 nTrafficClass7);
int pyGSW_QoS_PortCfgGet(u8 nPortId);
int pyGSW_QoS_PortCfgSet(u8 nPortId, GSW_QoS_ClassSelect_t eClassMode, u8 nTrafficClass);
int pyGSW_QoS_PortRemarkingCfgGet(u8 nPortId);
int pyGSW_QoS_PortRemarkingCfgSet(u8 nPortId, GSW_Qos_ingressRemarking_t eDSCP_IngressRemarkingEnable, \
          ltq_bool_t bDSCP_EgressRemarkingEnable, ltq_bool_t bPCP_IngressRemarkingEnable, ltq_bool_t bPCP_EgressRemarkingEnable, \
          ltq_bool_t bSTAG_PCP_IngressRemarkingEnable, ltq_bool_t bSTAG_DEI_IngressRemarkingEnable, \
          ltq_bool_t bSTAG_PCP_DEI_EgressRemarkingEnable);
int pyGSW_QoS_QueueBufferReserveCfgGet(u8 nQueueId);
int pyGSW_QoS_QueueBufferReserveCfgSet(u8 nQueueId, u32 nBufferReserved);
int pyGSW_QoS_QueuePortGet(u8 nPortId, u8 nTrafficClassId);
int pyGSW_QoS_QueuePortSet(u8 nPortId, u8 nTrafficClassId, u8 nQueueId);
int pyGSW_QoS_SVLAN_ClassPCP_PortGet(u8 nPortId);
int pyGSW_QoS_SVLAN_ClassPCP_PortSet(u8 nPortId, u8 nTrafficClass, u8 nCPCP0, u8 nCPCP1, u8 nCPCP2, u8 nCPCP3, \
          u8 nCPCP4, u8 nCPCP5, u8 nCPCP6, u8 nCPCP7, u8 nCPCP8, u8 nCPCP9, u8 nCPCP10, u8 nCPCP11, \
          u8 nCPCP12, u8 nCPCP13, u8 nCPCP14, u8 nCPCP15, u8 nSPCP0, u8 nSPCP1, u8 nSPCP2, u8 nSPCP3, \
          u8 nSPCP4, u8 nSPCP5, u8 nSPCP6, u8 nSPCP7, u8 nSPCP8, u8 nSPCP9, u8 nSPCP10, u8 nSPCP11, \
          u8 nSPCP12, u8 nSPCP13, u8 nSPCP14, u8 nSPCP15, u8 nDSCP0, u8 nDSCP1, u8 nDSCP2, u8 nDSCP3, \
          u8 nDSCP4, u8 nDSCP5, u8 nDSCP6, u8 nDSCP7, u8 nDSCP8, u8 nDSCP9, u8 nDSCP10, u8 nDSCP11, \
          u8 nDSCP12, u8 nDSCP13, u8 nDSCP14, u8 nDSCP15);
int pyGSW_QoS_SVLAN_PCP_ClassGet();
int pyGSW_QoS_SVLAN_PCP_ClassSet(u8 nTrafficClass0, u8 nTrafficClass1, u8 nTrafficClass2, u8 nTrafficClass3, \
          u8 nTrafficClass4, u8 nTrafficClass5, u8 nTrafficClass6, u8 nTrafficClass7, u8 nTrafficClass8, \
          u8 nTrafficClass9, u8 nTrafficClass10, u8 nTrafficClass11, u8 nTrafficClass12, u8 nTrafficClass13, \
          u8 nTrafficClass14, u8 nTrafficClass15, u8 nTrafficColor0, u8 nTrafficColor1, u8 nTrafficColor2, \
          u8 nTrafficColor3, u8 nTrafficColor4, u8 nTrafficColor5, u8 nTrafficColor6, u8 nTrafficColor7, \
          u8 nTrafficColor8, u8 nTrafficColor9, u8 nTrafficColor10, u8 nTrafficColor11, u8 nTrafficColor12, \
          u8 nTrafficColor13, u8 nTrafficColor14, u8 nTrafficColor15, u8 nPCP_Remark_Enable0, u8 nPCP_Remark_Enable1, \
          u8 nPCP_Remark_Enable2, u8 nPCP_Remark_Enable3, u8 nPCP_Remark_Enable4, u8 nPCP_Remark_Enable5, \
          u8 nPCP_Remark_Enable6, u8 nPCP_Remark_Enable7, u8 nPCP_Remark_Enable8, u8 nPCP_Remark_Enable9, \
          u8 nPCP_Remark_Enable10, u8 nPCP_Remark_Enable11, u8 nPCP_Remark_Enable12, u8 nPCP_Remark_Enable13, \
          u8 nPCP_Remark_Enable14, u8 nPCP_Remark_Enable15, u8 nDEI_Remark_Enable0, u8 nDEI_Remark_Enable1, \
          u8 nDEI_Remark_Enable2, u8 nDEI_Remark_Enable3, u8 nDEI_Remark_Enable4, u8 nDEI_Remark_Enable5, \
          u8 nDEI_Remark_Enable6, u8 nDEI_Remark_Enable7, u8 nDEI_Remark_Enable8, u8 nDEI_Remark_Enable9, \
          u8 nDEI_Remark_Enable10, u8 nDEI_Remark_Enable11, u8 nDEI_Remark_Enable12, u8 nDEI_Remark_Enable13, \
          u8 nDEI_Remark_Enable14, u8 nDEI_Remark_Enable15);
int pyGSW_QoS_SchedulerCfgGet(u8 nQueueId);
int pyGSW_QoS_SchedulerCfgSet(u8 nQueueId, GSW_QoS_Scheduler_t eType, u32 nWeight);
int pyGSW_QoS_ShaperCfgGet(u32 nRateShaperId);
int pyGSW_QoS_ShaperCfgSet(u32 nRateShaperId, ltq_bool_t bEnable, ltq_bool_t bAVB, u32 nCbs, u32 nRate);
int pyGSW_QoS_ShaperQueueAssign(u8 nRateShaperId, u8 nQueueId);
int pyGSW_QoS_ShaperQueueDeassign(u8 nRateShaperId, u8 nQueueId);
int pyGSW_QoS_ShaperQueueGet(u8 nQueueId);
int pyGSW_QoS_StormCfgGet();
int pyGSW_QoS_StormCfgSet(int nMeterId, ltq_bool_t bBroadcast, ltq_bool_t bMulticast, ltq_bool_t bUnknownUnicast);
int pyGSW_QoS_WredCfgGet();
int pyGSW_QoS_WredCfgSet(GSW_QoS_WRED_Profile_t eProfile, GSW_QoS_WRED_ThreshMode_t eThreshMode, u32 nRed_Min, \
          u32 nRed_Max, u32 nYellow_Min, u32 nYellow_Max, u32 nGreen_Min, u32 nGreen_Max);
int pyGSW_QoS_WredPortCfgGet(u32 nPortId);
int pyGSW_QoS_WredPortCfgSet(u32 nPortId, u32 nRed_Min, u32 nRed_Max, u32 nYellow_Min, u32 nYellow_Max, \
          u32 nGreen_Min, u32 nGreen_Max);
int pyGSW_QoS_WredQueueCfgGet(u32 nQueueId);
int pyGSW_QoS_WredQueueCfgSet(u32 nQueueId, u32 nRed_Min, u32 nRed_Max, u32 nYellow_Min, u32 nYellow_Max, \
          u32 nGreen_Min, u32 nGreen_Max);
int pyGSW_MulticastRouterPortAdd(u8 nPortId);
int pyGSW_MulticastRouterPortRead(ltq_bool_t bInitial);
int pyGSW_MulticastRouterPortRemove(u8 nPortId);
int pyGSW_MulticastSnoopCfgGet();
int pyGSW_MulticastSnoopCfgSet(GSW_multicastSnoopMode_t eIGMP_Mode, ltq_bool_t bIGMPv3, ltq_bool_t bCrossVLAN, \
          GSW_portForward_t eForwardPort, u8 nForwardPortId, u8 nClassOfService, u8 nRobust, u8 nQueryInterval, \
          GSW_multicastReportSuppression_t eSuppressionAggregation, ltq_bool_t bFastLeave, ltq_bool_t bLearningRouter, \
          ltq_bool_t bMulticastUnknownDrop);
int pyGSW_MulticastTableEntryAdd(u32 nPortId, GSW_IP_Select_t eIPVersion, GSW_IP_t uIP_Gda, GSW_IP_t uIP_Gsa, \
          GSW_IGMP_MemberMode_t eModeMember);
int pyGSW_MulticastTableEntryRead(ltq_bool_t bInitial);
int pyGSW_MulticastTableEntryRemove(u32 nPortId, GSW_IP_Select_t eIPVersion, GSW_IP_t uIP_Gda, GSW_IP_t uIP_Gsa, \
          GSW_IGMP_MemberMode_t eModeMember);
int pyGSW_CPU_PortCfgGet(u8 nPortId);
int pyGSW_CPU_PortCfgSet(u8 nPortId, ltq_bool_t bCPU_PortValid, ltq_bool_t bSpecialTagIngress, ltq_bool_t bSpecialTagEgress, \
          ltq_bool_t bFcsCheck, ltq_bool_t bFcsGenerate, GSW_CPU_SpecialTagEthType_t bSpecialTagEthType);
int pyGSW_CapGet(GSW_capType_t nCapType);
int pyGSW_CfgGet();
int pyGSW_CfgSet(GSW_ageTimer_t eMAC_TableAgeTimer, ltq_bool_t bVLAN_Aware, u16 nMaxPacketLen, ltq_bool_t bLearningLimitAction, \
          ltq_bool_t bMAC_SpoofingAction, ltq_bool_t bPauseMAC_ModeSrc, u8 nPauseMAC_Src0, u8 nPauseMAC_Src1, \
          u8 nPauseMAC_Src2, u8 nPauseMAC_Src3, u8 nPauseMAC_Src4, u8 nPauseMAC_Src5);
int pyGSW_Disable();
int pyGSW_Enable();
int pyGSW_HW_Init(GSW_HW_InitMode_t eInitMode);
int pyGSW_MDIO_CfgGet();
int pyGSW_MDIO_CfgSet(u32 nMDIO_Speed, ltq_bool_t bMDIO_Enable);
int pyGSW_MDIO_DataRead(u8 nAddressDev, u8 nAddressReg);
int pyGSW_MDIO_DataWrite(u8 nAddressDev, u8 nAddressReg, u16 nData);
int pyGSW_MonitorPortCfgGet(u8 nPortId);
int pyGSW_MonitorPortCfgSet(u8 nPortId, ltq_bool_t bMonitorPort);
int pyGSW_PortCfgGet(u8 nPortId);
int pyGSW_PortCfgSet(u8 nPortId, GSW_portEnable_t eEnable, ltq_bool_t bUnicastUnknownDrop, ltq_bool_t bMulticastUnknownDrop, \
          ltq_bool_t bReservedPacketDrop, ltq_bool_t bBroadcastDrop, ltq_bool_t bAging, ltq_bool_t bLearning, \
          ltq_bool_t bLearningMAC_PortLock, u16 nLearningLimit, ltq_bool_t bMAC_SpoofingDetection, \
          GSW_portFlow_t eFlowCtrl, GSW_portMonitor_t ePortMonitor);
int pyGSW_PortLinkCfgGet(u8 nPortId);
int pyGSW_PortLinkCfgSet(u8 nPortId, ltq_bool_t bDuplexForce, GSW_portDuplex_t eDuplex, ltq_bool_t bSpeedForce, \
          GSW_portSpeed_t eSpeed, ltq_bool_t bLinkForce, GSW_portLink_t eLink, GSW_MII_Mode_t eMII_Mode, \
          GSW_MII_Type_t eMII_Type, GSW_clkMode_t eClkMode, ltq_bool_t bLPI);
int pyGSW_PortPHY_AddrGet(u8 nPortId);
int pyGSW_PortPHY_Query(u8 nPortId);
int pyGSW_PortRGMII_ClkCfgGet(u8 nPortId);
int pyGSW_PortRGMII_ClkCfgSet(u8 nPortId, u8 nDelayRx, u8 nDelayTx);
int pyGSW_PortRedirectGet(u8 nPortId);
int pyGSW_PortRedirectSet(u8 nPortId, ltq_bool_t bRedirectEgress, ltq_bool_t bRedirectIngress);
int pyGSW_RMON_Clear(GSW_RMON_type_t eRmonType, u8 nRmonId);
int pyGSW_RMON_Port_Get(u8 nPortId);
int pyGSW_VersionGet(u16 nId);
int pyGSW_WoL_CfgGet();
int pyGSW_WoL_CfgSet(u8 nWolMAC0, u8 nWolMAC1, u8 nWolMAC2, u8 nWolMAC3, u8 nWolMAC4, u8 nWolMAC5, u8 nWolPassword0, \
          u8 nWolPassword1, u8 nWolPassword2, u8 nWolPassword3, u8 nWolPassword4, u8 nWolPassword5, \
          ltq_bool_t bWolPasswordEnable);
int pyGSW_WoL_PortCfgGet(u8 nPortId);
int pyGSW_WoL_PortCfgSet(u8 nPortId, ltq_bool_t bWakeOnLAN_Enable);
int pyGSW_RegisterGet(u16 nRegAddr);
int pyGSW_RegisterSet(u16 nRegAddr, u16 nData);
int pyGSW_IrqMaskGet(u32 nPortId);
int pyGSW_IrqMaskSet(u32 nPortId, GSW_irqSrc_t eIrqSrc);
int pyGSW_PceRuleDelete(u32 nIndex);
int pyGSW_RMON_ExtendGet(u8 nPortId);
int pyGSW_Reset(GSW_resetMode_t eReset);
int pyGSW_TimestampPortRead(u8 nPortId);
int pyGSW_TimestampTimerGet();
int pyGSW_TimestampTimerSet(u32 nSec, u32 nNanoSec, u32 nFractionalNanoSec);
