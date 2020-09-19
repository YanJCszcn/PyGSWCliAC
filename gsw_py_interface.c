//swig -python -py3 -castmode PySwitch.i
//python3 setup.py build_ext --inplace


#include <Python.h> 
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "gsw_sw_init.h"

extern void *ethsw_api_core_init(ethsw_core_init_t *einit);
extern void ethsw_api_core_exit(void *pdev);
static ethsw_core_init_t core_init;
static ethsw_api_dev_t *pedev0;

char fn[] = "tttttttt.txt";

int init()
{
	/* Initialized Switch API */
	memset(&core_init, 0, sizeof(core_init));
	core_init.sdev = GSW_DEV_0;
	pedev0 = ethsw_api_core_init(&core_init);
	if (pedev0 == NULL) 
	{
		printf("Failed in switch API initialization.\n");
		return 1;
	}
	pedev0->cport = 7;/* CPU port ID */
	fprintf(stdout, "Switch API initialization OK.\n");
	Py_Initialize();
	return 0;
}



int pc_uart_dataread(u16 Offset, u16 *value)
{
//	*value = 3;
//	printf("rrrr %04x %04x\r\n", Offset, *value);
//	return 0;

	PyObject * pModule = NULL;                               
	PyObject * pFunc = NULL;                                 
	PyObject *pReturn = NULL;                                
	PyObject *pArgs = NULL;                                  
                                                           
	pModule =PyImport_ImportModule("ser02");      //Test001:Pyt
	pFunc= PyObject_GetAttrString(pModule, "r");  //Add:Pytho
	pArgs = PyTuple_New(1);               //?????????????????
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", Offset));//0--
                                                           
	//pReturn = PyEval_CallObject(pFunc, pArgs);   
	pReturn = PyObject_CallObject(pFunc, pArgs);   
	if (NULL == pReturn)
	{
		//g_OutputString(_T("调用函数[%s]失败!!!!"), _T("startScan"));
		*value = 0xDEAD;
		return 0;
	}
	//PyArg_ParseTuple(pReturn, "i", value);  
   *value = (u16) PyLong_AsLong(pReturn);
	//printf("read %04x = %04x\r\n", Offset, *value);      
	Py_DECREF(pModule);
	Py_DECREF(pFunc);
	Py_DECREF(pReturn);
	Py_DECREF(pArgs);
   return 1;
}

int pc_uart_datawrite(u16 Offset, u16 value)
{
//	printf("w %04x %04x\r\n", Offset, value);
//	return 0; 

	PyObject * pModule = NULL;                            
	PyObject * pFunc = NULL;                              
	PyObject *pReturn = NULL;                             
	PyObject *pArgs = NULL;                               
                                                        
	pModule =PyImport_ImportModule("ser02");      //Test001:
	pFunc= PyObject_GetAttrString(pModule, "w");  //Add:Py
	pArgs = PyTuple_New(2);               //??????????????
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", Offset));
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", value));                                                        
	pReturn = PyEval_CallObject(pFunc, pArgs);            
	//printf("w %04x = %04x\r\n", Offset, value);      
	Py_DECREF(pModule);
	Py_DECREF(pFunc);
	Py_DECREF(pReturn);
	Py_DECREF(pArgs);
   return 1;
}


int r(unsigned short addr)
{
	GSW_register_t p;
	p.nRegAddr = addr;
	p.nData = 0xDEADBEEF;
	GSW_RegisterGet(pedev0, &p);
  return p.nData;
}

int w(unsigned short addr, unsigned short value)
{
	GSW_register_t p;
	p.nRegAddr = addr;
	p.nData = value;
	GSW_RegisterSet(pedev0, &p);	
  return 0;
}

int mdiow ( unsigned char phyid, unsigned char addr, unsigned short value)
{
	GSW_MDIO_data_t p;
	p.nAddressDev = phyid;
	p.nAddressReg = addr;
	p.nData = value;
	GSW_MDIO_DataWrite (pedev0, &p);
	return 0;
}

unsigned short mdior ( unsigned char phyid, unsigned char addr)
{
	GSW_MDIO_data_t p;
	p.nAddressDev = phyid;
	p.nAddressReg = addr;
	p.nData = 0xDEAD;
	GSW_MDIO_DataRead (pedev0, &p);
	printf("0x%04x\r\n", p.nData);
	return p.nData;
}

/*
int pyGSW_HW_Init()
{
	GSW_HW_Init_t parm;
	parm.eInitMode = GSW_HW_INIT_WR;
	GSW_HW_Init(pedev0, &parm);
  return 0;
} 
*/ 


/****************************************************************************/
/*       Manually and Automatically code of PCE functions                   */
/****************************************************************************/

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
       ltq_bool_t action_bPortLinkSelection, ltq_bool_t action_bFlowID_Action, u16 action_nFlowID)
{
    int ret;
    GSW_PCE_rule_t param;
    param.pattern.nIndex = pattern_nIndex;
    param.pattern.bEnable = pattern_bEnable;
    param.pattern.bPortIdEnable = pattern_bPortIdEnable;
    param.pattern.nPortId = pattern_nPortId;
    param.pattern.bDSCP_Enable = pattern_bDSCP_Enable;
    param.pattern.nDSCP = pattern_nDSCP;
    param.pattern.bPCP_Enable = pattern_bPCP_Enable;
    param.pattern.nPCP = pattern_nPCP;
    param.pattern.bSTAG_PCP_DEI_Enable = pattern_bSTAG_PCP_DEI_Enable;
    param.pattern.nSTAG_PCP_DEI = pattern_nSTAG_PCP_DEI;
    param.pattern.bPktLngEnable = pattern_bPktLngEnable;
    param.pattern.nPktLng = pattern_nPktLng;
    param.pattern.nPktLngRange = pattern_nPktLngRange;
    param.pattern.bMAC_DstEnable = pattern_bMAC_DstEnable;
    param.pattern.nMAC_Dst[0] = pattern_nMAC_Dst0;
    param.pattern.nMAC_Dst[1] = pattern_nMAC_Dst1;
    param.pattern.nMAC_Dst[2] = pattern_nMAC_Dst2;
    param.pattern.nMAC_Dst[3] = pattern_nMAC_Dst3;
    param.pattern.nMAC_Dst[4] = pattern_nMAC_Dst4;
    param.pattern.nMAC_Dst[5] = pattern_nMAC_Dst5;
    param.pattern.nMAC_DstMask = pattern_nMAC_DstMask;
    param.pattern.bMAC_SrcEnable = pattern_bMAC_SrcEnable;
    param.pattern.nMAC_Src[0] = pattern_nMAC_Src0;
    param.pattern.nMAC_Src[1] = pattern_nMAC_Src1;
    param.pattern.nMAC_Src[2] = pattern_nMAC_Src2;
    param.pattern.nMAC_Src[3] = pattern_nMAC_Src3;
    param.pattern.nMAC_Src[4] = pattern_nMAC_Src4;
    param.pattern.nMAC_Src[5] = pattern_nMAC_Src5;
    param.pattern.nMAC_SrcMask = pattern_nMAC_SrcMask;
    param.pattern.bAppDataMSB_Enable = pattern_bAppDataMSB_Enable;
    param.pattern.nAppDataMSB = pattern_nAppDataMSB;
    param.pattern.bAppMaskRangeMSB_Select = pattern_bAppMaskRangeMSB_Select;
    param.pattern.nAppMaskRangeMSB = pattern_nAppMaskRangeMSB;
    param.pattern.bAppDataLSB_Enable = pattern_bAppDataLSB_Enable;
    param.pattern.nAppDataLSB = pattern_nAppDataLSB;
    param.pattern.bAppMaskRangeLSB_Select = pattern_bAppMaskRangeLSB_Select;
    param.pattern.nAppMaskRangeLSB = pattern_nAppMaskRangeLSB;
    param.pattern.eDstIP_Select = pattern_eDstIP_Select;
    if (pattern_eDstIP_Select == GSW_PCE_IP_V4)
    {
        param.pattern.nDstIP.nIPv4 = pattern_nDstIPipv4;
    }
    else if (pattern_eDstIP_Select == GSW_PCE_IP_V6)
    {
        param.pattern.nDstIP.nIPv6[0] = pattern_nDstIPipv60;
        param.pattern.nDstIP.nIPv6[1] = pattern_nDstIPipv61;
        param.pattern.nDstIP.nIPv6[2] = pattern_nDstIPipv62;
        param.pattern.nDstIP.nIPv6[3] = pattern_nDstIPipv63;
        param.pattern.nDstIP.nIPv6[4] = pattern_nDstIPipv64;
        param.pattern.nDstIP.nIPv6[5] = pattern_nDstIPipv65;
        param.pattern.nDstIP.nIPv6[6] = pattern_nDstIPipv66;
        param.pattern.nDstIP.nIPv6[7] = pattern_nDstIPipv67;
    }
    param.pattern.nDstIP_Mask = pattern_nDstIP_Mask;
    param.pattern.eSrcIP_Select = pattern_eSrcIP_Select;
    if (pattern_eSrcIP_Select == GSW_PCE_IP_V4)
    {
        param.pattern.nSrcIP.nIPv4 = pattern_nSrcIPipv4;
    }
    else if (pattern_eSrcIP_Select == GSW_PCE_IP_V6)
    {
        param.pattern.nSrcIP.nIPv6[0] = pattern_nSrcIPipv60;
        param.pattern.nSrcIP.nIPv6[1] = pattern_nSrcIPipv61;
        param.pattern.nSrcIP.nIPv6[2] = pattern_nSrcIPipv62;
        param.pattern.nSrcIP.nIPv6[3] = pattern_nSrcIPipv63;
        param.pattern.nSrcIP.nIPv6[4] = pattern_nSrcIPipv64;
        param.pattern.nSrcIP.nIPv6[5] = pattern_nSrcIPipv65;
        param.pattern.nSrcIP.nIPv6[6] = pattern_nSrcIPipv66;
        param.pattern.nSrcIP.nIPv6[7] = pattern_nSrcIPipv67;
    }
    param.pattern.nSrcIP_Mask = pattern_nSrcIP_Mask;
    param.pattern.bEtherTypeEnable = pattern_bEtherTypeEnable;
    param.pattern.nEtherType = pattern_nEtherType;
    param.pattern.nEtherTypeMask = pattern_nEtherTypeMask;
    param.pattern.bProtocolEnable = pattern_bProtocolEnable;
    param.pattern.nProtocol = pattern_nProtocol;
    param.pattern.nProtocolMask = pattern_nProtocolMask;
    param.pattern.bSessionIdEnable = pattern_bSessionIdEnable;
    param.pattern.nSessionId = pattern_nSessionId;
    param.pattern.bVid = pattern_bVid;
    param.pattern.nVid = pattern_nVid;
    param.pattern.bVidRange_Select = pattern_bVidRange_Select;
    param.pattern.nVidRange = pattern_nVidRange;
    param.pattern.bSLAN_Vid = pattern_bSLAN_Vid;
    param.pattern.nSLAN_Vid = pattern_nSLAN_Vid;
    param.action.eTrafficClassAction = action_eTrafficClassAction;
    param.action.nTrafficClassAlternate = action_nTrafficClassAlternate;
    param.action.eSnoopingTypeAction = action_eSnoopingTypeAction;
    param.action.eLearningAction = action_eLearningAction;
    param.action.eIrqAction = action_eIrqAction;
    param.action.eCrossStateAction = action_eCrossStateAction;
    param.action.eCritFrameAction = action_eCritFrameAction;
    param.action.eTimestampAction = action_eTimestampAction;
    param.action.ePortMapAction = action_ePortMapAction;
    param.action.nForwardPortMap = action_nForwardPortMap;
    param.action.bRemarkAction = action_bRemarkAction;
    param.action.bRemarkPCP = action_bRemarkPCP;
    param.action.bRemarkSTAG_PCP = action_bRemarkSTAG_PCP;
    param.action.bRemarkSTAG_DEI = action_bRemarkSTAG_DEI;
    param.action.bRemarkDSCP = action_bRemarkDSCP;
    param.action.bRemarkClass = action_bRemarkClass;
    param.action.eMeterAction = action_eMeterAction;
    param.action.nMeterId = action_nMeterId;
    param.action.bRMON_Action = action_bRMON_Action;
    param.action.nRMON_Id = action_nRMON_Id;
    param.action.eVLAN_Action = action_eVLAN_Action;
    param.action.nVLAN_Id = action_nVLAN_Id;
    param.action.nFId = action_nFId;
    param.action.eSVLAN_Action = action_eSVLAN_Action;
    param.action.nSVLAN_Id = action_nSVLAN_Id;
    param.action.eVLAN_CrossAction = action_eVLAN_CrossAction;
    param.action.bCVLAN_Ignore_Control = action_bCVLAN_Ignore_Control;
    param.action.bPortBitMapMuxControl = action_bPortBitMapMuxControl;
    param.action.bPortTrunkAction = action_bPortTrunkAction;
    param.action.bPortLinkSelection = action_bPortLinkSelection;
    param.action.bFlowID_Action = action_bFlowID_Action;
    param.action.nFlowID = action_nFlowID;
    ret = 	GSW_PceRuleWrite(pedev0, &param);
    return ret;
}

int pyGSW_PceRuleRead(int idx)
{
    int ret;
    FILE *fp;
    GSW_PCE_rule_t param;
    GSW_PCE_action_t action;
    GSW_PCE_pattern_t pattern;
    param.pattern.nIndex = idx;
    ret = GSW_PceRuleRead(pedev0, &param);
    pattern = param.pattern;
    action = param.action;

    fp = fopen (fn, "w+");

    fprintf(fp, "param.pattern.nDstIP.nIPv4 = %08x, %d \r\n", pattern.nDstIP.nIPv4, pattern.nDstIP.nIPv4);

    fprintf(fp, "PCE rule index %d, enabled = %d\r\n", pattern.nIndex, pattern.bEnable);
    fprintf(fp, "pattern:\r\n");
    fprintf(fp, "   , bPortIdEnable = %d, nPortId = %d\r\n", pattern.bPortIdEnable, pattern.nPortId);
    fprintf(fp, "   , bDSCP_Enable = %d, nDSCP = %d\r\n", pattern.bDSCP_Enable, pattern.nDSCP);
    fprintf(fp, "   , bPCP_Enable = %d, nPCP = %d\r\n", pattern.bPCP_Enable, pattern.nPCP);
    fprintf(fp, "   , bSTAG_PCP_DEI_Enable = %d, nSTAG_PCP_DEI = %d\r\n", pattern.bSTAG_PCP_DEI_Enable, pattern.nSTAG_PCP_DEI);
    fprintf(fp, "   , bPktLngEnable = %d, nPktLng = %d, nPktLngRange = %d\r\n", pattern.bPktLngEnable, pattern.nPktLng, pattern.nPktLngRange);
    fprintf(fp, "   , bMAC_DstEnable = %d, nMAC_Dst = %02x:%02x:%02x:%02x:%02x:%02x, nMAC_DstMask = %d\r\n", pattern.bMAC_DstEnable, pattern.nMAC_Dst[0], pattern.nMAC_Dst[1], pattern.nMAC_Dst[2], pattern.nMAC_Dst[3], pattern.nMAC_Dst[4], pattern.nMAC_Dst[5], pattern.nMAC_DstMask);
    fprintf(fp, "   , bMAC_SrcEnable = %d, nMAC_Src = %02x:%02x:%02x:%02x:%02x:%02x, nMAC_SrcMask = %d\r\n", pattern.bMAC_SrcEnable, pattern.nMAC_Src[0], pattern.nMAC_Src[1], pattern.nMAC_Src[2], pattern.nMAC_Src[3], pattern.nMAC_Src[4], pattern.nMAC_Src[5], pattern.nMAC_SrcMask);
    fprintf(fp, "   , bAppDataMSB_Enable = %d, nAppDataMSB = %d\r\n", pattern.bAppDataMSB_Enable, pattern.nAppDataMSB);
    fprintf(fp, "   , bAppMaskRangeMSB_Select = %d, nAppMaskRangeMSB = %d\r\n", pattern.bAppMaskRangeMSB_Select, pattern.nAppMaskRangeMSB);
    fprintf(fp, "   , bAppDataLSB_Enable = %d, nAppDataLSB = %d\r\n", pattern.bAppDataLSB_Enable, pattern.nAppDataLSB);
    fprintf(fp, "   , bAppMaskRangeLSB_Select = %d, nAppMaskRangeLSB = %d\r\n", pattern.bAppMaskRangeLSB_Select, pattern.nAppMaskRangeLSB);
    fprintf(fp, "   , eDstIP_Select = %d, nDstIPipv4 = %d.%d.%d.%d, nDstIPipv6 = %02x%02x:%02x%02x:%02x%02x:%02x%02x, nDstIP_Mask = %d\r\n", pattern.eDstIP_Select, (pattern.nDstIP.nIPv4 >> 24) & 0xFF, (pattern.nDstIP.nIPv4 >> 16) & 0xFF, (pattern.nDstIP.nIPv4 >> 8) & 0xFF, pattern.nDstIP.nIPv4 & 0xFF, pattern.nDstIP.nIPv6[0], pattern.nDstIP.nIPv6[1], pattern.nDstIP.nIPv6[2], pattern.nDstIP.nIPv6[3], pattern.nDstIP.nIPv6[4], pattern.nDstIP.nIPv6[5], pattern.nDstIP.nIPv6[6], pattern.nDstIP.nIPv6[7], pattern.nDstIP_Mask);
    fprintf(fp, "   , eSrcIP_Select = %d, nSrcIPipv4 = %d.%d.%d.%d, nSrcIPipv6 = %02x%02x:%02x%02x:%02x%02x:%02x%02x, nSrcIP_Mask = %d\r\n", pattern.eSrcIP_Select, (pattern.nSrcIP.nIPv4 >> 24) & 0xFF, (pattern.nSrcIP.nIPv4 >> 16) & 0xFF, (pattern.nSrcIP.nIPv4 >> 8) & 0xFF, pattern.nSrcIP.nIPv4 & 0xFF, pattern.nSrcIP.nIPv6[0], pattern.nSrcIP.nIPv6[1], pattern.nSrcIP.nIPv6[2], pattern.nSrcIP.nIPv6[3], pattern.nSrcIP.nIPv6[4], pattern.nSrcIP.nIPv6[5], pattern.nSrcIP.nIPv6[6], pattern.nSrcIP.nIPv6[7], pattern.nSrcIP_Mask);
    fprintf(fp, "   , bEtherTypeEnable = %d, nEtherType = %d, nEtherTypeMask = %d\r\n", pattern.bEtherTypeEnable, pattern.nEtherType, pattern.nEtherTypeMask);
    fprintf(fp, "   , bProtocolEnable = %d, nProtocol = %d, nProtocolMask = %d\r\n", pattern.bProtocolEnable, pattern.nProtocol, pattern.nProtocolMask);
    fprintf(fp, "   , bSessionIdEnable = %d, nSessionId = %d, bVid = %d, nVid = %d\r\n", pattern.bSessionIdEnable, pattern.nSessionId, pattern.bVid, pattern.nVid);
    fprintf(fp, "   , bVidRange_Select = %d, nVidRange = %d, bSLAN_Vid = %d, nSLAN_Vid = %d\r\n", pattern.bVidRange_Select, pattern.nVidRange, pattern.bSLAN_Vid, pattern.nSLAN_Vid);

    fprintf(fp, "Action:\r\n");
    fprintf(fp, "   , eTrafficClassAction = %d, nTrafficClassAlternate = %d\r\n", action.eTrafficClassAction, action.nTrafficClassAlternate);
    fprintf(fp, "   , eSnoopingTypeAction = %d\r\n", action.eSnoopingTypeAction);
    fprintf(fp, "   , eLearningAction = %d\r\n", action.eLearningAction);
    fprintf(fp, "   , eIrqAction = %d\r\n", action.eIrqAction);
    fprintf(fp, "   , eCrossStateAction = %d\r\n", action.eCrossStateAction);
    fprintf(fp, "   , eCritFrameAction = %d\r\n", action.eCritFrameAction);
    fprintf(fp, "   , eTimestampAction = %d\r\n", action.eTimestampAction);
    fprintf(fp, "   , ePortMapAction = %d, nForwardPortMap = %d\r\n", action.ePortMapAction, action.nForwardPortMap);
    fprintf(fp, "   , bRemarkAction = %d, bRemarkPCP = %d, bRemarkSTAG_PCP = %d, bRemarkSTAG_DEI = %d, bRemarkDSCP = %d, bRemarkClass = %d\r\n", action.bRemarkAction, action.bRemarkPCP, action.bRemarkSTAG_PCP, action.bRemarkSTAG_DEI, action.bRemarkDSCP, action.bRemarkClass);
    fprintf(fp, "   , eMeterAction = %d, nMeterId = %d\r\n", action.eMeterAction, action.nMeterId);
    fprintf(fp, "   , bRMON_Action = %d, nRMON_Id = %d\r\n", action.bRMON_Action, action.nRMON_Id);
    fprintf(fp, "   , eVLAN_Action = %d, nVLAN_Id = %d, nFId = %d\r\n", action.eVLAN_Action, action.nVLAN_Id, action.nFId);
    fprintf(fp, "   , eSVLAN_Action = %d, nSVLAN_Id = %d\r\n", action.eSVLAN_Action, action.nSVLAN_Id);
    fprintf(fp, "   , eVLAN_CrossAction = %d, bCVLAN_Ignore_Control = %d, bPortBitMapMuxControl = %d\r\n", action.eVLAN_CrossAction, action.bCVLAN_Ignore_Control, action.bPortBitMapMuxControl);
    fprintf(fp, "   , bPortTrunkAction = %d, bPortLinkSelection = %d\r\n", action.bPortTrunkAction, action.bPortLinkSelection);
    fprintf(fp, "   , bFlowID_Action = %d, nFlowID = %d\r\n", action.bFlowID_Action, action.nFlowID);
    fclose(fp);
    return ret;

}
#if 0
GSW_PCE_rule_t p;
void pce_pinit(int idx, int enb)
{
	memset(&p, 0, sizeof(GSW_PCE_rule_t));
	p.pattern.nIndex = idx;
	p.pattern.bEnable = enb;
	printf("[PySwitch pce_rule p.nIndex = %d, p.bEnable = %d", idx, enb);
}

void pce_portId(int enb, int port)
{
	p.pattern.bPortIdEnable = enb;
	p.pattern.nPortId = port;
	printf(", p.bPortIdEnable = %d, p.nPortId = %d", enb, port);
}

/* GSW_PCE_ACTION_PORTMAP_DISABLE	= 0,
   GSW_PCE_ACTION_PORTMAP_REGULAR	= 1,
   GSW_PCE_ACTION_PORTMAP_DISCARD	= 2,
   GSW_PCE_ACTION_PORTMAP_CPU	= 3,
   GSW_PCE_ACTION_PORTMAP_ALTERNATIVE	= 4,
   GSW_PCE_ACTION_PORTMAP_MULTICAST_ROUTER	= 5,
   GSW_PCE_ACTION_PORTMAP_MULTICAST_HW_TABLE = 6,
   GSW_PCE_ACTION_PORTMAP_ALTERNATIVE_VLAN	= 7,
   GSW_PCE_ACTION_PORTMAP_ALTERNATIVE_STAG_VLAN	= 8
   port map is map, bit0 - port0, bit1 - port1 ..., only used when act is 4  */
void pce_act_forwarding(int act, int portmap)
{
	p.action.ePortMapAction = act;
	p.action.nForwardPortMap = portmap;
	printf(", p.ePortMapAction = %d, p.nForwardPortMap = %d", act, portmap);
}


int pyGSW_PceRuleWrite()
{
	printf(" -- write]\r\n");
	GSW_PceRuleWrite(pedev0, &p);       
  return 0;
}

int pyGSW_PceRuleRead()
{        
	printf(" -- read]\r\n");
	GSW_PceRuleRead(pedev0, &p);     

   printf("------------------------------------------------------------------------\r\nPCE rule index %d, enabled = %d\r\n", p.pattern.nIndex, p.pattern.bEnable);
   printf("pattern:bPortIdEnable = %d, nPortId = %d\r\n", p.pattern.bPortIdEnable, p.pattern.nPortId);
   printf("        bDSCP_Enable = %d, nDSCP = %d\r\n", p.pattern.bDSCP_Enable, p.pattern.nDSCP);
   printf("        bPCP_Enable = %d, nPCP = %d\r\n", p.pattern.bPCP_Enable, p.pattern.nPCP);
   printf("        bSTAG_PCP_DEI_Enable = %d, nSTAG_PCP_DEI = %d\r\n", p.pattern.bSTAG_PCP_DEI_Enable, p.pattern.nSTAG_PCP_DEI);
   printf("        bPktLngEnable = %d, nPktLng = %d, nPktLngRange = %d\r\n", p.pattern.bPktLngEnable, p.pattern.nPktLng, p.pattern.nPktLngRange);
   printf("        bMAC_DstEnable = %d, nMAC_Dst = %02x:%02x:%02x:%02x:%02x:%02x, nMAC_DstMask = 0x%x\r\n", p.pattern.bMAC_DstEnable, p.pattern.nMAC_Dst[0], \
   									p.pattern.nMAC_Dst[1], p.pattern.nMAC_Dst[2], p.pattern.nMAC_Dst[3], p.pattern.nMAC_Dst[4], p.pattern.nMAC_Dst[5], p.pattern.nMAC_DstMask);
   printf("        bMAC_SrcEnable = %d, nMAC_Src = %02x:%02x:%02x:%02x:%02x:%02x, nMAC_SrcMask = 0x%x\r\n", p.pattern.bMAC_SrcEnable, p.pattern.nMAC_Src[0], \
   									p.pattern.nMAC_Src[1], p.pattern.nMAC_Src[2], p.pattern.nMAC_Src[3], p.pattern.nMAC_Src[4], p.pattern.nMAC_Src[5], p.pattern.nMAC_SrcMask);
   printf("        bAppDataMSB_Enable = %d, nAppDataMSB = %d, bAppMaskRangeMSB_Select = %d, nAppMaskRangeMSB = %d\r\n", p.pattern.bAppDataMSB_Enable, \
   									p.pattern.nAppDataMSB, p.pattern.bAppMaskRangeMSB_Select, p.pattern.nAppMaskRangeMSB);
   printf("        bAppDataLSB_Enable = %d, nAppDataLSB = %d, bAppMaskRangeLSB_Select = %d, nAppMaskRangeLSB = %d\r\n", p.pattern.bAppDataLSB_Enable, \
   									p.pattern.nAppDataLSB, p.pattern.bAppMaskRangeLSB_Select, p.pattern.nAppMaskRangeLSB);
   printf("        eDstIP_Select = %d, nDstIP = %08x, nDstIP_Mask = 0x%x\r\n", p.pattern.eDstIP_Select, p.pattern.nDstIP.nIPv4, p.pattern.nDstIP_Mask);
   printf("        eSrcIP_Select = %d, nSrcIP = %08x, nSrcIP_Mask = 0x%x\r\n", p.pattern.eSrcIP_Select, p.pattern.nSrcIP.nIPv4, p.pattern.nSrcIP_Mask);

/*   ltq_bool_t	bEtherTypeEnable;
   u16	nEtherType;
   u16	nEtherTypeMask;

   ltq_bool_t	bProtocolEnable;
   u8	nProtocol;
   u8	nProtocolMask;

   ltq_bool_t	bSessionIdEnable;
   u16	nSessionId;

   ltq_bool_t	bVid;
   u16	nVid;
   ltq_bool_t	bVidRange_Select;
   u16	nVidRange;

   ltq_bool_t	bSLAN_Vid;
   u16	nSLAN_Vid;
*/
   printf("Action:\r\n");
   printf("eTrafficClassAction = %d, nTrafficClassAlternate = %d\r\n", p.action.eTrafficClassAction, p.action.nTrafficClassAlternate);
   printf("eSnoopingTypeAction = %d\r\n", p.action.eSnoopingTypeAction);
   printf("eLearningAction = %d\r\n", p.action.eLearningAction);
   printf("eIrqAction = %d\r\n", p.action.eIrqAction);
   printf("eCrossStateAction = %d\r\n", p.action.eCrossStateAction);
   printf("eCritFrameAction = %d\r\n", p.action.eCritFrameAction);
   printf("eTimestampAction = %d\r\n", p.action.eTimestampAction);
   printf("ePortMapAction = %d, nForwardPortMap = 0x%x\r\n", p.action.ePortMapAction, p.action.nForwardPortMap);
   printf("bRemarkAction = %d, bRemarkPCP = %d, bRemarkSTAG_PCP = %d, bRemarkSTAG_DEI = %d, bRemarkDSCP = %d, bRemarkClass = %d\r\n", \
   				p.action.bRemarkAction, p.action.bRemarkPCP, p.action.bRemarkSTAG_PCP, p.action.bRemarkSTAG_DEI, p.action.bRemarkDSCP, p.action.bRemarkClass);
   printf("eMeterAction = %d, nMeterId = %d\r\n", p.action.eMeterAction, p.action.nMeterId);
   printf("bRMON_Action = %d, nRMON_Id = %d\r\n", p.action.bRMON_Action, p.action.nRMON_Id);
   printf("eVLAN_Action = %d, nVLAN_Id = %d, nFId = %d\r\n", p.action.eVLAN_Action, p.action.nVLAN_Id, p.action.nFId);
   printf("eSVLAN_Action = %d, nSVLAN_Id = %d\r\n", p.action.eSVLAN_Action, p.action.nSVLAN_Id);
   printf("eVLAN_CrossAction = %d, bCVLAN_Ignore_Control = %d, bPortBitMapMuxControl = %d\r\n", \
   				p.action.eVLAN_CrossAction, p.action.bCVLAN_Ignore_Control, p.action.bPortBitMapMuxControl);
   printf("bPortTrunkAction = %d, bPortLinkSelection = %d\r\n", p.action.bPortTrunkAction, p.action.bPortLinkSelection);
   printf("bFlowID_Action = %d, nFlowID = %d\r\n------------------------------------------------------------------------\r\n", p.action.bFlowID_Action, p.action.nFlowID);
  return 0;
}                                                                       

int pyGSW_PceRuleReadf(int idx, int enb)
{        
	FILE *fp;
	memset(&p, 0, sizeof(GSW_PCE_rule_t));
	p.pattern.nIndex = idx;
	p.pattern.bEnable = enb;
	
	fp = fopen (fn, "w+");
	fprintf(fp, "[PySwitch pce_rule p.nIndex = %d, p.bEnable = %d", idx, enb);
	fprintf(fp, " -- read]\r\n");
	GSW_PceRuleRead(pedev0, &p);     

   fprintf(fp, "------------------------------------------------------------------------\r\nPCE rule index %d, enabled = %d\r\n", p.pattern.nIndex, p.pattern.bEnable);
   fprintf(fp, "pattern:bPortIdEnable = %d, nPortId = %d\r\n", p.pattern.bPortIdEnable, p.pattern.nPortId);
   fprintf(fp, "        bDSCP_Enable = %d, nDSCP = %d\r\n", p.pattern.bDSCP_Enable, p.pattern.nDSCP);
   fprintf(fp, "        bPCP_Enable = %d, nPCP = %d\r\n", p.pattern.bPCP_Enable, p.pattern.nPCP);
   fprintf(fp, "        bSTAG_PCP_DEI_Enable = %d, nSTAG_PCP_DEI = %d\r\n", p.pattern.bSTAG_PCP_DEI_Enable, p.pattern.nSTAG_PCP_DEI);
   fprintf(fp, "        bPktLngEnable = %d, nPktLng = %d, nPktLngRange = %d\r\n", p.pattern.bPktLngEnable, p.pattern.nPktLng, p.pattern.nPktLngRange);
   fprintf(fp, "        bMAC_DstEnable = %d, nMAC_Dst = %02x:%02x:%02x:%02x:%02x:%02x, nMAC_DstMask = 0x%x\r\n", p.pattern.bMAC_DstEnable, p.pattern.nMAC_Dst[0], \
   									p.pattern.nMAC_Dst[1], p.pattern.nMAC_Dst[2], p.pattern.nMAC_Dst[3], p.pattern.nMAC_Dst[4], p.pattern.nMAC_Dst[5], p.pattern.nMAC_DstMask);
   fprintf(fp, "        bMAC_SrcEnable = %d, nMAC_Src = %02x:%02x:%02x:%02x:%02x:%02x, nMAC_SrcMask = 0x%x\r\n", p.pattern.bMAC_SrcEnable, p.pattern.nMAC_Src[0], \
   									p.pattern.nMAC_Src[1], p.pattern.nMAC_Src[2], p.pattern.nMAC_Src[3], p.pattern.nMAC_Src[4], p.pattern.nMAC_Src[5], p.pattern.nMAC_SrcMask);
   fprintf(fp, "        bAppDataMSB_Enable = %d, nAppDataMSB = %d, bAppMaskRangeMSB_Select = %d, nAppMaskRangeMSB = %d\r\n", p.pattern.bAppDataMSB_Enable, \
   									p.pattern.nAppDataMSB, p.pattern.bAppMaskRangeMSB_Select, p.pattern.nAppMaskRangeMSB);
   fprintf(fp, "        bAppDataLSB_Enable = %d, nAppDataLSB = %d, bAppMaskRangeLSB_Select = %d, nAppMaskRangeLSB = %d\r\n", p.pattern.bAppDataLSB_Enable, \
   									p.pattern.nAppDataLSB, p.pattern.bAppMaskRangeLSB_Select, p.pattern.nAppMaskRangeLSB);
   fprintf(fp, "        eDstIP_Select = %d, nDstIP = %08x, nDstIP_Mask = 0x%x\r\n", p.pattern.eDstIP_Select, p.pattern.nDstIP.nIPv4, p.pattern.nDstIP_Mask);
   fprintf(fp, "        eSrcIP_Select = %d, nSrcIP = %08x, nSrcIP_Mask = 0x%x\r\n", p.pattern.eSrcIP_Select, p.pattern.nSrcIP.nIPv4, p.pattern.nSrcIP_Mask);

/*   ltq_bool_t	bEtherTypeEnable;
   u16	nEtherType;
   u16	nEtherTypeMask;

   ltq_bool_t	bProtocolEnable;
   u8	nProtocol;
   u8	nProtocolMask;

   ltq_bool_t	bSessionIdEnable;
   u16	nSessionId;

   ltq_bool_t	bVid;
   u16	nVid;
   ltq_bool_t	bVidRange_Select;
   u16	nVidRange;

   ltq_bool_t	bSLAN_Vid;
   u16	nSLAN_Vid;
*/
   fprintf(fp, "Action:\r\n");
   fprintf(fp, "eTrafficClassAction = %d, nTrafficClassAlternate = %d\r\n", p.action.eTrafficClassAction, p.action.nTrafficClassAlternate);
   fprintf(fp, "eSnoopingTypeAction = %d\r\n", p.action.eSnoopingTypeAction);
   fprintf(fp, "eLearningAction = %d\r\n", p.action.eLearningAction);
   fprintf(fp, "eIrqAction = %d\r\n", p.action.eIrqAction);
   fprintf(fp, "eCrossStateAction = %d\r\n", p.action.eCrossStateAction);
   fprintf(fp, "eCritFrameAction = %d\r\n", p.action.eCritFrameAction);
   fprintf(fp, "eTimestampAction = %d\r\n", p.action.eTimestampAction);
   fprintf(fp, "ePortMapAction = %d, nForwardPortMap = 0x%x\r\n", p.action.ePortMapAction, p.action.nForwardPortMap);
   fprintf(fp, "bRemarkAction = %d, bRemarkPCP = %d, bRemarkSTAG_PCP = %d, bRemarkSTAG_DEI = %d, bRemarkDSCP = %d, bRemarkClass = %d\r\n", \
   				p.action.bRemarkAction, p.action.bRemarkPCP, p.action.bRemarkSTAG_PCP, p.action.bRemarkSTAG_DEI, p.action.bRemarkDSCP, p.action.bRemarkClass);
   fprintf(fp, "eMeterAction = %d, nMeterId = %d\r\n", p.action.eMeterAction, p.action.nMeterId);
   fprintf(fp, "bRMON_Action = %d, nRMON_Id = %d\r\n", p.action.bRMON_Action, p.action.nRMON_Id);
   fprintf(fp, "eVLAN_Action = %d, nVLAN_Id = %d, nFId = %d\r\n", p.action.eVLAN_Action, p.action.nVLAN_Id, p.action.nFId);
   fprintf(fp, "eSVLAN_Action = %d, nSVLAN_Id = %d\r\n", p.action.eSVLAN_Action, p.action.nSVLAN_Id);
   fprintf(fp, "eVLAN_CrossAction = %d, bCVLAN_Ignore_Control = %d, bPortBitMapMuxControl = %d\r\n", \
   				p.action.eVLAN_CrossAction, p.action.bCVLAN_Ignore_Control, p.action.bPortBitMapMuxControl);
   fprintf(fp, "bPortTrunkAction = %d, bPortLinkSelection = %d\r\n", p.action.bPortTrunkAction, p.action.bPortLinkSelection);
   fprintf(fp, "bFlowID_Action = %d, nFlowID = %d\r\n------------------------------------------------------------------------\r\n", p.action.bFlowID_Action, p.action.nFlowID);
  fclose(fp);
  return 0;
}                                                                       
#endif

/**************************************************/
/*         Auto Code Generated                    */
/**************************************************/

int pyGSW_8021X_EAPOL_RuleGet(u8 nForwardPortId)
{
    FILE *fp;
    int ret;
    GSW_8021X_EAPOL_Rule_t  param;

    memset( &param, 0, sizeof(GSW_8021X_EAPOL_Rule_t));
    param.nForwardPortId = nForwardPortId;

    ret = GSW_8021X_EAPOL_RuleGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_8021X_EAPOL_RuleGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "eForwardPort", param.eForwardPort, param.eForwardPort);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nForwardPortId", param.nForwardPortId, param.nForwardPortId);
    fclose(fp);

    return ret;
}

int pyGSW_8021X_EAPOL_RuleSet(GSW_portForward_t eForwardPort, u8 nForwardPortId)
{
    int ret;
    GSW_8021X_EAPOL_Rule_t  param;

    memset( &param, 0, sizeof(GSW_8021X_EAPOL_Rule_t));
    param.eForwardPort = eForwardPort;
    param.nForwardPortId = nForwardPortId;

    ret = GSW_8021X_EAPOL_RuleSet(pedev0, &param);

    return ret;
}

int pyGSW_8021X_PortCfgGet(u32 nPortId)
{
    FILE *fp;
    int ret;
    GSW_8021X_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_8021X_portCfg_t));
    param.nPortId = nPortId;

    ret = GSW_8021X_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_8021X_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eState", param.eState, param.eState);
    fclose(fp);

    return ret;
}

int pyGSW_8021X_PortCfgSet(u32 nPortId, GSW_8021X_portState_t eState)
{
    int ret;
    GSW_8021X_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_8021X_portCfg_t));
    param.nPortId = nPortId;
    param.eState = eState;

    ret = GSW_8021X_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_MAC_TableClear()
{
    int ret;

    ret = GSW_MAC_TableClear(pedev0);

    return ret;
}

int pyGSW_MAC_TableEntryAdd(u32 nFId, u32 nPortId, int nAgeTimer, u16 nSVLAN_Id, ltq_bool_t bStaticEntry, \
          u8 nTrafficClass, u8 nMAC0, u8 nMAC1, u8 nMAC2, u8 nMAC3, u8 nMAC4, u8 nMAC5)
{
    int ret;
    GSW_MAC_tableAdd_t  param;

    memset( &param, 0, sizeof(GSW_MAC_tableAdd_t));
    param.nFId = nFId;
    param.nPortId = nPortId;
    param.nAgeTimer = nAgeTimer;
    param.nSVLAN_Id = nSVLAN_Id;
    param.bStaticEntry = bStaticEntry;
    param.nTrafficClass = nTrafficClass;
    param.nMAC[0] = nMAC0;
    param.nMAC[1] = nMAC1;
    param.nMAC[2] = nMAC2;
    param.nMAC[3] = nMAC3;
    param.nMAC[4] = nMAC4;
    param.nMAC[5] = nMAC5;

    ret = GSW_MAC_TableEntryAdd(pedev0, &param);

    return ret;
}

int pyGSW_MAC_TableEntryQuery(u8 nMAC0, u8 nMAC1, u8 nMAC2, u8 nMAC3, u8 nMAC4, u8 nMAC5, u32 nFId)
{
    FILE *fp;
    int ret;
    GSW_MAC_tableQuery_t  param;

    memset( &param, 0, sizeof(GSW_MAC_tableQuery_t));
    param.nMAC[0] = nMAC0;
    param.nMAC[1] = nMAC1;
    param.nMAC[2] = nMAC2;
    param.nMAC[3] = nMAC3;
    param.nMAC[4] = nMAC4;
    param.nMAC[5] = nMAC5;
    param.nFId = nFId;

    ret = GSW_MAC_TableEntryQuery(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MAC_TableEntryQuery");
    fprintf(fp, "%s = [", "nMAC[6]");
    fprintf(fp, " 0x%02x", param.nMAC[0]);
    fprintf(fp, " 0x%02x", param.nMAC[1]);
    fprintf(fp, " 0x%02x", param.nMAC[2]);
    fprintf(fp, " 0x%02x", param.nMAC[3]);
    fprintf(fp, " 0x%02x", param.nMAC[4]);
    fprintf(fp, " 0x%02x", param.nMAC[5]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFId", param.nFId, param.nFId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bFound", param.bFound, param.bFound);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nAgeTimer", param.nAgeTimer, param.nAgeTimer);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nSVLAN_Id", param.nSVLAN_Id, param.nSVLAN_Id);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bStaticEntry", param.bStaticEntry, param.bStaticEntry);
    fclose(fp);

    return ret;
}

int pyGSW_MAC_TableEntryRead(ltq_bool_t bInitial)
{
    FILE *fp;
    int ret;
    GSW_MAC_tableRead_t  param;

    memset( &param, 0, sizeof(GSW_MAC_tableRead_t));
    param.bInitial = bInitial;

    ret = GSW_MAC_TableEntryRead(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MAC_TableEntryRead");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bInitial", param.bInitial, param.bInitial);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLast", param.bLast, param.bLast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFId", param.nFId, param.nFId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nAgeTimer", param.nAgeTimer, param.nAgeTimer);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nSVLAN_Id", param.nSVLAN_Id, param.nSVLAN_Id);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bStaticEntry", param.bStaticEntry, param.bStaticEntry);
    fprintf(fp, "%s = [", "nMAC[6]");
    fprintf(fp, " 0x%02x", param.nMAC[0]);
    fprintf(fp, " 0x%02x", param.nMAC[1]);
    fprintf(fp, " 0x%02x", param.nMAC[2]);
    fprintf(fp, " 0x%02x", param.nMAC[3]);
    fprintf(fp, " 0x%02x", param.nMAC[4]);
    fprintf(fp, " 0x%02x", param.nMAC[5]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_MAC_TableEntryRemove(u32 nFId, u8 nMAC0, u8 nMAC1, u8 nMAC2, u8 nMAC3, u8 nMAC4, u8 nMAC5)
{
    int ret;
    GSW_MAC_tableRemove_t  param;

    memset( &param, 0, sizeof(GSW_MAC_tableRemove_t));
    param.nFId = nFId;
    param.nMAC[0] = nMAC0;
    param.nMAC[1] = nMAC1;
    param.nMAC[2] = nMAC2;
    param.nMAC[3] = nMAC3;
    param.nMAC[4] = nMAC4;
    param.nMAC[5] = nMAC5;

    ret = GSW_MAC_TableEntryRemove(pedev0, &param);

    return ret;
}

int pyGSW_STP_BPDU_RuleGet()
{
    FILE *fp;
    int ret;
    GSW_STP_BPDU_Rule_t  param;

    memset( &param, 0, sizeof(GSW_STP_BPDU_Rule_t));

    ret = GSW_STP_BPDU_RuleGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_STP_BPDU_RuleGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "eForwardPort", param.eForwardPort, param.eForwardPort);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nForwardPortId", param.nForwardPortId, param.nForwardPortId);
    fclose(fp);

    return ret;
}

int pyGSW_STP_BPDU_RuleSet(GSW_portForward_t eForwardPort, u8 nForwardPortId)
{
    int ret;
    GSW_STP_BPDU_Rule_t  param;

    memset( &param, 0, sizeof(GSW_STP_BPDU_Rule_t));
    param.eForwardPort = eForwardPort;
    param.nForwardPortId = nForwardPortId;

    ret = GSW_STP_BPDU_RuleSet(pedev0, &param);

    return ret;
}

int pyGSW_STP_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_STP_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_STP_portCfg_t));
    param.nPortId = nPortId;

    ret = GSW_STP_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_STP_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFId", param.nFId, param.nFId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "ePortState", param.ePortState, param.ePortState);
    fclose(fp);

    return ret;
}

int pyGSW_STP_PortCfgSet(u8 nPortId, u32 nFId, GSW_STP_PortState_t ePortState)
{
    int ret;
    GSW_STP_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_STP_portCfg_t));
    param.nPortId = nPortId;
    param.nFId = nFId;
    param.ePortState = ePortState;

    ret = GSW_STP_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_TrunkingCfgGet()
{
    FILE *fp;
    int ret;
    GSW_trunkingCfg_t  param;

    memset( &param, 0, sizeof(GSW_trunkingCfg_t));

    ret = GSW_TrunkingCfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_TrunkingCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bIP_Src", param.bIP_Src, param.bIP_Src);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bIP_Dst", param.bIP_Dst, param.bIP_Dst);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMAC_Src", param.bMAC_Src, param.bMAC_Src);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMAC_Dst", param.bMAC_Dst, param.bMAC_Dst);
    fclose(fp);

    return ret;
}

int pyGSW_TrunkingCfgSet(ltq_bool_t bIP_Src, ltq_bool_t bIP_Dst, ltq_bool_t bMAC_Src, ltq_bool_t bMAC_Dst)
{
    int ret;
    GSW_trunkingCfg_t  param;

    memset( &param, 0, sizeof(GSW_trunkingCfg_t));
    param.bIP_Src = bIP_Src;
    param.bIP_Dst = bIP_Dst;
    param.bMAC_Src = bMAC_Src;
    param.bMAC_Dst = bMAC_Dst;

    ret = GSW_TrunkingCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_TrunkingPortCfgGet(u32 nPortId)
{
    FILE *fp;
    int ret;
    GSW_trunkingPortCfg_t  param;

    memset( &param, 0, sizeof(GSW_trunkingPortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_TrunkingPortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_TrunkingPortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bAggregateEnable", param.bAggregateEnable, param.bAggregateEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nAggrPortId", param.nAggrPortId, param.nAggrPortId);
    fclose(fp);

    return ret;
}

int pyGSW_TrunkingPortCfgSet(ltq_bool_t bAggregateEnable, u32 nPortId, u32 nAggrPortId)
{
    int ret;
    GSW_trunkingPortCfg_t  param;

    memset( &param, 0, sizeof(GSW_trunkingPortCfg_t));
    param.bAggregateEnable = bAggregateEnable;
    param.nPortId = nPortId;
    param.nAggrPortId = nAggrPortId;

    ret = GSW_TrunkingPortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_SVLAN_CfgGet()
{
    FILE *fp;
    int ret;
    GSW_SVLAN_cfg_t  param;

    memset( &param, 0, sizeof(GSW_SVLAN_cfg_t));

    ret = GSW_SVLAN_CfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_SVLAN_CfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nEthertype", param.nEthertype, param.nEthertype);
    fclose(fp);

    return ret;
}

int pyGSW_SVLAN_CfgSet(u16 nEthertype)
{
    int ret;
    GSW_SVLAN_cfg_t  param;

    memset( &param, 0, sizeof(GSW_SVLAN_cfg_t));
    param.nEthertype = nEthertype;

    ret = GSW_SVLAN_CfgSet(pedev0, &param);

    return ret;
}

int pyGSW_SVLAN_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_SVLAN_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_SVLAN_portCfg_t));
    param.nPortId = nPortId;

    ret = GSW_SVLAN_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_SVLAN_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSVLAN_TagSupport", param.bSVLAN_TagSupport, param.bSVLAN_TagSupport);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSVLAN_MACbasedTag", param.bSVLAN_MACbasedTag, param.bSVLAN_MACbasedTag);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortVId", param.nPortVId, param.nPortVId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bVLAN_ReAssign", param.bVLAN_ReAssign, param.bVLAN_ReAssign);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eVLAN_MemberViolation", param.eVLAN_MemberViolation, param.eVLAN_MemberViolation);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eAdmitMode", param.eAdmitMode, param.eAdmitMode);
    fclose(fp);

    return ret;
}

int pyGSW_SVLAN_PortCfgSet(u8 nPortId, ltq_bool_t bSVLAN_TagSupport, ltq_bool_t bSVLAN_MACbasedTag, u16 nPortVId, \
          ltq_bool_t bVLAN_ReAssign, GSW_VLAN_MemberViolation_t eVLAN_MemberViolation, GSW_VLAN_Admit_t eAdmitMode)
{
    int ret;
    GSW_SVLAN_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_SVLAN_portCfg_t));
    param.nPortId = nPortId;
    param.bSVLAN_TagSupport = bSVLAN_TagSupport;
    param.bSVLAN_MACbasedTag = bSVLAN_MACbasedTag;
    param.nPortVId = nPortVId;
    param.bVLAN_ReAssign = bVLAN_ReAssign;
    param.eVLAN_MemberViolation = eVLAN_MemberViolation;
    param.eAdmitMode = eAdmitMode;

    ret = GSW_SVLAN_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_Member_Init(u32 nPortMemberMap, u32 nEgressTagMap)
{
    int ret;
    GSW_VLAN_memberInit_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_memberInit_t));
    param.nPortMemberMap = nPortMemberMap;
    param.nEgressTagMap = nEgressTagMap;

    ret = GSW_VLAN_Member_Init(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_IdCreate(u16 nVId, u32 nFId)
{
    int ret;
    GSW_VLAN_IdCreate_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_IdCreate_t));
    param.nVId = nVId;
    param.nFId = nFId;

    ret = GSW_VLAN_IdCreate(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_IdDelete(u16 nVId)
{
    int ret;
    GSW_VLAN_IdDelete_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_IdDelete_t));
    param.nVId = nVId;

    ret = GSW_VLAN_IdDelete(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_IdGet(u16 nVId)
{
    FILE *fp;
    int ret;
    GSW_VLAN_IdGet_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_IdGet_t));
    param.nVId = nVId;

    ret = GSW_VLAN_IdGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_VLAN_IdGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nVId", param.nVId, param.nVId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFId", param.nFId, param.nFId);
    fclose(fp);

    return ret;
}

int pyGSW_VLAN_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_VLAN_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_portCfg_t));
    param.nPortId = nPortId;

    ret = GSW_VLAN_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_VLAN_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortVId", param.nPortVId, param.nPortVId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bVLAN_UnknownDrop", param.bVLAN_UnknownDrop, param.bVLAN_UnknownDrop);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bVLAN_ReAssign", param.bVLAN_ReAssign, param.bVLAN_ReAssign);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eVLAN_MemberViolation", param.eVLAN_MemberViolation, param.eVLAN_MemberViolation);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eAdmitMode", param.eAdmitMode, param.eAdmitMode);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bTVM", param.bTVM, param.bTVM);
    fclose(fp);

    return ret;
}

int pyGSW_VLAN_PortCfgSet(u8 nPortId, u16 nPortVId, ltq_bool_t bVLAN_UnknownDrop, ltq_bool_t bVLAN_ReAssign, \
          GSW_VLAN_MemberViolation_t eVLAN_MemberViolation, GSW_VLAN_Admit_t eAdmitMode, ltq_bool_t bTVM)
{
    int ret;
    GSW_VLAN_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_portCfg_t));
    param.nPortId = nPortId;
    param.nPortVId = nPortVId;
    param.bVLAN_UnknownDrop = bVLAN_UnknownDrop;
    param.bVLAN_ReAssign = bVLAN_ReAssign;
    param.eVLAN_MemberViolation = eVLAN_MemberViolation;
    param.eAdmitMode = eAdmitMode;
    param.bTVM = bTVM;

    ret = GSW_VLAN_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_PortMemberAdd(u16 nVId, u32 nPortId, ltq_bool_t bVLAN_TagEgress)
{
    int ret;
    GSW_VLAN_portMemberAdd_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_portMemberAdd_t));
    param.nVId = nVId;
    param.nPortId = nPortId;
    param.bVLAN_TagEgress = bVLAN_TagEgress;

    ret = GSW_VLAN_PortMemberAdd(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_PortMemberRead(ltq_bool_t bInitial)
{
    FILE *fp;
    int ret;
    GSW_VLAN_portMemberRead_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_portMemberRead_t));
    param.bInitial = bInitial;

    ret = GSW_VLAN_PortMemberRead(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_VLAN_PortMemberRead");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bInitial", param.bInitial, param.bInitial);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLast", param.bLast, param.bLast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nVId", param.nVId, param.nVId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTagId", param.nTagId, param.nTagId);
    fclose(fp);

    return ret;
}

int pyGSW_VLAN_PortMemberRemove(u16 nVId, u32 nPortId)
{
    int ret;
    GSW_VLAN_portMemberRemove_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_portMemberRemove_t));
    param.nVId = nVId;
    param.nPortId = nPortId;

    ret = GSW_VLAN_PortMemberRemove(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_ReservedAdd(u16 nVId)
{
    int ret;
    GSW_VLAN_reserved_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_reserved_t));
    param.nVId = nVId;

    ret = GSW_VLAN_ReservedAdd(pedev0, &param);

    return ret;
}

int pyGSW_VLAN_ReservedRemove(u16 nVId)
{
    int ret;
    GSW_VLAN_reserved_t  param;

    memset( &param, 0, sizeof(GSW_VLAN_reserved_t));
    param.nVId = nVId;

    ret = GSW_VLAN_ReservedRemove(pedev0, &param);

    return ret;
}

int pyGSW_QoS_ClassDSCP_Get()
{
    FILE *fp;
    int ret;
    GSW_QoS_ClassDSCP_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ClassDSCP_Cfg_t));

    ret = GSW_QoS_ClassDSCP_Get(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_ClassDSCP_Get");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTrafficClass", param.nTrafficClass, param.nTrafficClass);
    fprintf(fp, "%s = [", "nDSCP[16]");
    fprintf(fp, " 0x%02x", param.nDSCP[0]);
    fprintf(fp, " 0x%02x", param.nDSCP[1]);
    fprintf(fp, " 0x%02x", param.nDSCP[2]);
    fprintf(fp, " 0x%02x", param.nDSCP[3]);
    fprintf(fp, " 0x%02x", param.nDSCP[4]);
    fprintf(fp, " 0x%02x", param.nDSCP[5]);
    fprintf(fp, " 0x%02x", param.nDSCP[6]);
    fprintf(fp, " 0x%02x", param.nDSCP[7]);
    fprintf(fp, " 0x%02x", param.nDSCP[8]);
    fprintf(fp, " 0x%02x", param.nDSCP[9]);
    fprintf(fp, " 0x%02x", param.nDSCP[10]);
    fprintf(fp, " 0x%02x", param.nDSCP[11]);
    fprintf(fp, " 0x%02x", param.nDSCP[12]);
    fprintf(fp, " 0x%02x", param.nDSCP[13]);
    fprintf(fp, " 0x%02x", param.nDSCP[14]);
    fprintf(fp, " 0x%02x", param.nDSCP[15]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_QoS_ClassDSCP_Set(u8 nTrafficClass, u8 nDSCP0, u8 nDSCP1, u8 nDSCP2, u8 nDSCP3, u8 nDSCP4, u8 nDSCP5, \
          u8 nDSCP6, u8 nDSCP7, u8 nDSCP8, u8 nDSCP9, u8 nDSCP10, u8 nDSCP11, u8 nDSCP12, u8 nDSCP13, \
          u8 nDSCP14, u8 nDSCP15)
{
    int ret;
    GSW_QoS_ClassDSCP_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ClassDSCP_Cfg_t));
    param.nTrafficClass = nTrafficClass;
    param.nDSCP[0] = nDSCP0;
    param.nDSCP[1] = nDSCP1;
    param.nDSCP[2] = nDSCP2;
    param.nDSCP[3] = nDSCP3;
    param.nDSCP[4] = nDSCP4;
    param.nDSCP[5] = nDSCP5;
    param.nDSCP[6] = nDSCP6;
    param.nDSCP[7] = nDSCP7;
    param.nDSCP[8] = nDSCP8;
    param.nDSCP[9] = nDSCP9;
    param.nDSCP[10] = nDSCP10;
    param.nDSCP[11] = nDSCP11;
    param.nDSCP[12] = nDSCP12;
    param.nDSCP[13] = nDSCP13;
    param.nDSCP[14] = nDSCP14;
    param.nDSCP[15] = nDSCP15;

    ret = GSW_QoS_ClassDSCP_Set(pedev0, &param);

    return ret;
}

int pyGSW_QoS_ClassPCP_Get()
{
    FILE *fp;
    int ret;
    GSW_QoS_ClassPCP_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ClassPCP_Cfg_t));

    ret = GSW_QoS_ClassPCP_Get(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_ClassPCP_Get");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTrafficClass", param.nTrafficClass, param.nTrafficClass);
    fprintf(fp, "%s = [", "nPCP[16]");
    fprintf(fp, " 0x%02x", param.nPCP[0]);
    fprintf(fp, " 0x%02x", param.nPCP[1]);
    fprintf(fp, " 0x%02x", param.nPCP[2]);
    fprintf(fp, " 0x%02x", param.nPCP[3]);
    fprintf(fp, " 0x%02x", param.nPCP[4]);
    fprintf(fp, " 0x%02x", param.nPCP[5]);
    fprintf(fp, " 0x%02x", param.nPCP[6]);
    fprintf(fp, " 0x%02x", param.nPCP[7]);
    fprintf(fp, " 0x%02x", param.nPCP[8]);
    fprintf(fp, " 0x%02x", param.nPCP[9]);
    fprintf(fp, " 0x%02x", param.nPCP[10]);
    fprintf(fp, " 0x%02x", param.nPCP[11]);
    fprintf(fp, " 0x%02x", param.nPCP[12]);
    fprintf(fp, " 0x%02x", param.nPCP[13]);
    fprintf(fp, " 0x%02x", param.nPCP[14]);
    fprintf(fp, " 0x%02x", param.nPCP[15]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_QoS_ClassPCP_Set(u8 nTrafficClass, u8 nPCP0, u8 nPCP1, u8 nPCP2, u8 nPCP3, u8 nPCP4, u8 nPCP5, \
          u8 nPCP6, u8 nPCP7, u8 nPCP8, u8 nPCP9, u8 nPCP10, u8 nPCP11, u8 nPCP12, u8 nPCP13, u8 nPCP14, \
          u8 nPCP15)
{
    int ret;
    GSW_QoS_ClassPCP_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ClassPCP_Cfg_t));
    param.nTrafficClass = nTrafficClass;
    param.nPCP[0] = nPCP0;
    param.nPCP[1] = nPCP1;
    param.nPCP[2] = nPCP2;
    param.nPCP[3] = nPCP3;
    param.nPCP[4] = nPCP4;
    param.nPCP[5] = nPCP5;
    param.nPCP[6] = nPCP6;
    param.nPCP[7] = nPCP7;
    param.nPCP[8] = nPCP8;
    param.nPCP[9] = nPCP9;
    param.nPCP[10] = nPCP10;
    param.nPCP[11] = nPCP11;
    param.nPCP[12] = nPCP12;
    param.nPCP[13] = nPCP13;
    param.nPCP[14] = nPCP14;
    param.nPCP[15] = nPCP15;

    ret = GSW_QoS_ClassPCP_Set(pedev0, &param);

    return ret;
}

int pyGSW_QoS_DSCP_ClassGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_DSCP_ClassCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_DSCP_ClassCfg_t));

    ret = GSW_QoS_DSCP_ClassGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_DSCP_ClassGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nDSCP", param.nDSCP, param.nDSCP);
    fprintf(fp, "%s = [", "nTrafficClass[64]");
    fprintf(fp, " 0x%02x", param.nTrafficClass[0]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[1]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[2]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[3]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[4]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[5]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[6]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[7]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[8]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[9]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[10]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[11]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[12]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[13]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[14]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[15]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[16]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[17]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[18]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[19]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[20]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[21]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[22]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[23]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[24]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[25]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[26]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[27]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[28]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[29]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[30]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[31]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[32]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[33]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[34]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[35]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[36]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[37]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[38]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[39]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[40]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[41]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[42]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[43]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[44]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[45]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[46]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[47]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[48]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[49]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[50]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[51]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[52]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[53]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[54]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[55]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[56]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[57]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[58]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[59]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[60]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[61]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[62]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[63]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

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
          u8 nTrafficClass59, u8 nTrafficClass60, u8 nTrafficClass61, u8 nTrafficClass62, u8 nTrafficClass63)
{
    int ret;
    GSW_QoS_DSCP_ClassCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_DSCP_ClassCfg_t));
    param.nDSCP = nDSCP;
    param.nTrafficClass[0] = nTrafficClass0;
    param.nTrafficClass[1] = nTrafficClass1;
    param.nTrafficClass[2] = nTrafficClass2;
    param.nTrafficClass[3] = nTrafficClass3;
    param.nTrafficClass[4] = nTrafficClass4;
    param.nTrafficClass[5] = nTrafficClass5;
    param.nTrafficClass[6] = nTrafficClass6;
    param.nTrafficClass[7] = nTrafficClass7;
    param.nTrafficClass[8] = nTrafficClass8;
    param.nTrafficClass[9] = nTrafficClass9;
    param.nTrafficClass[10] = nTrafficClass10;
    param.nTrafficClass[11] = nTrafficClass11;
    param.nTrafficClass[12] = nTrafficClass12;
    param.nTrafficClass[13] = nTrafficClass13;
    param.nTrafficClass[14] = nTrafficClass14;
    param.nTrafficClass[15] = nTrafficClass15;
    param.nTrafficClass[16] = nTrafficClass16;
    param.nTrafficClass[17] = nTrafficClass17;
    param.nTrafficClass[18] = nTrafficClass18;
    param.nTrafficClass[19] = nTrafficClass19;
    param.nTrafficClass[20] = nTrafficClass20;
    param.nTrafficClass[21] = nTrafficClass21;
    param.nTrafficClass[22] = nTrafficClass22;
    param.nTrafficClass[23] = nTrafficClass23;
    param.nTrafficClass[24] = nTrafficClass24;
    param.nTrafficClass[25] = nTrafficClass25;
    param.nTrafficClass[26] = nTrafficClass26;
    param.nTrafficClass[27] = nTrafficClass27;
    param.nTrafficClass[28] = nTrafficClass28;
    param.nTrafficClass[29] = nTrafficClass29;
    param.nTrafficClass[30] = nTrafficClass30;
    param.nTrafficClass[31] = nTrafficClass31;
    param.nTrafficClass[32] = nTrafficClass32;
    param.nTrafficClass[33] = nTrafficClass33;
    param.nTrafficClass[34] = nTrafficClass34;
    param.nTrafficClass[35] = nTrafficClass35;
    param.nTrafficClass[36] = nTrafficClass36;
    param.nTrafficClass[37] = nTrafficClass37;
    param.nTrafficClass[38] = nTrafficClass38;
    param.nTrafficClass[39] = nTrafficClass39;
    param.nTrafficClass[40] = nTrafficClass40;
    param.nTrafficClass[41] = nTrafficClass41;
    param.nTrafficClass[42] = nTrafficClass42;
    param.nTrafficClass[43] = nTrafficClass43;
    param.nTrafficClass[44] = nTrafficClass44;
    param.nTrafficClass[45] = nTrafficClass45;
    param.nTrafficClass[46] = nTrafficClass46;
    param.nTrafficClass[47] = nTrafficClass47;
    param.nTrafficClass[48] = nTrafficClass48;
    param.nTrafficClass[49] = nTrafficClass49;
    param.nTrafficClass[50] = nTrafficClass50;
    param.nTrafficClass[51] = nTrafficClass51;
    param.nTrafficClass[52] = nTrafficClass52;
    param.nTrafficClass[53] = nTrafficClass53;
    param.nTrafficClass[54] = nTrafficClass54;
    param.nTrafficClass[55] = nTrafficClass55;
    param.nTrafficClass[56] = nTrafficClass56;
    param.nTrafficClass[57] = nTrafficClass57;
    param.nTrafficClass[58] = nTrafficClass58;
    param.nTrafficClass[59] = nTrafficClass59;
    param.nTrafficClass[60] = nTrafficClass60;
    param.nTrafficClass[61] = nTrafficClass61;
    param.nTrafficClass[62] = nTrafficClass62;
    param.nTrafficClass[63] = nTrafficClass63;

    ret = GSW_QoS_DSCP_ClassSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_DSCP_DropPrecedenceCfgGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_DSCP_DropPrecedenceCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_DSCP_DropPrecedenceCfg_t));

    ret = GSW_QoS_DSCP_DropPrecedenceCfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_DSCP_DropPrecedenceCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nDSCP", param.nDSCP, param.nDSCP);
    fprintf(fp, "%s = [", "nDSCP_DropPrecedence[64]");
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[0]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[1]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[2]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[3]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[4]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[5]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[6]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[7]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[8]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[9]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[10]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[11]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[12]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[13]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[14]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[15]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[16]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[17]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[18]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[19]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[20]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[21]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[22]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[23]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[24]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[25]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[26]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[27]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[28]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[29]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[30]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[31]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[32]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[33]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[34]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[35]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[36]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[37]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[38]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[39]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[40]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[41]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[42]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[43]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[44]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[45]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[46]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[47]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[48]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[49]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[50]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[51]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[52]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[53]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[54]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[55]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[56]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[57]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[58]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[59]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[60]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[61]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[62]);
    fprintf(fp, " 0x%02x", param.nDSCP_DropPrecedence[63]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

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
          GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence62, GSW_QoS_DropPrecedence_t nDSCP_DropPrecedence63)
{
    int ret;
    GSW_QoS_DSCP_DropPrecedenceCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_DSCP_DropPrecedenceCfg_t));
    param.nDSCP = nDSCP;
    param.nDSCP_DropPrecedence[0] = nDSCP_DropPrecedence0;
    param.nDSCP_DropPrecedence[1] = nDSCP_DropPrecedence1;
    param.nDSCP_DropPrecedence[2] = nDSCP_DropPrecedence2;
    param.nDSCP_DropPrecedence[3] = nDSCP_DropPrecedence3;
    param.nDSCP_DropPrecedence[4] = nDSCP_DropPrecedence4;
    param.nDSCP_DropPrecedence[5] = nDSCP_DropPrecedence5;
    param.nDSCP_DropPrecedence[6] = nDSCP_DropPrecedence6;
    param.nDSCP_DropPrecedence[7] = nDSCP_DropPrecedence7;
    param.nDSCP_DropPrecedence[8] = nDSCP_DropPrecedence8;
    param.nDSCP_DropPrecedence[9] = nDSCP_DropPrecedence9;
    param.nDSCP_DropPrecedence[10] = nDSCP_DropPrecedence10;
    param.nDSCP_DropPrecedence[11] = nDSCP_DropPrecedence11;
    param.nDSCP_DropPrecedence[12] = nDSCP_DropPrecedence12;
    param.nDSCP_DropPrecedence[13] = nDSCP_DropPrecedence13;
    param.nDSCP_DropPrecedence[14] = nDSCP_DropPrecedence14;
    param.nDSCP_DropPrecedence[15] = nDSCP_DropPrecedence15;
    param.nDSCP_DropPrecedence[16] = nDSCP_DropPrecedence16;
    param.nDSCP_DropPrecedence[17] = nDSCP_DropPrecedence17;
    param.nDSCP_DropPrecedence[18] = nDSCP_DropPrecedence18;
    param.nDSCP_DropPrecedence[19] = nDSCP_DropPrecedence19;
    param.nDSCP_DropPrecedence[20] = nDSCP_DropPrecedence20;
    param.nDSCP_DropPrecedence[21] = nDSCP_DropPrecedence21;
    param.nDSCP_DropPrecedence[22] = nDSCP_DropPrecedence22;
    param.nDSCP_DropPrecedence[23] = nDSCP_DropPrecedence23;
    param.nDSCP_DropPrecedence[24] = nDSCP_DropPrecedence24;
    param.nDSCP_DropPrecedence[25] = nDSCP_DropPrecedence25;
    param.nDSCP_DropPrecedence[26] = nDSCP_DropPrecedence26;
    param.nDSCP_DropPrecedence[27] = nDSCP_DropPrecedence27;
    param.nDSCP_DropPrecedence[28] = nDSCP_DropPrecedence28;
    param.nDSCP_DropPrecedence[29] = nDSCP_DropPrecedence29;
    param.nDSCP_DropPrecedence[30] = nDSCP_DropPrecedence30;
    param.nDSCP_DropPrecedence[31] = nDSCP_DropPrecedence31;
    param.nDSCP_DropPrecedence[32] = nDSCP_DropPrecedence32;
    param.nDSCP_DropPrecedence[33] = nDSCP_DropPrecedence33;
    param.nDSCP_DropPrecedence[34] = nDSCP_DropPrecedence34;
    param.nDSCP_DropPrecedence[35] = nDSCP_DropPrecedence35;
    param.nDSCP_DropPrecedence[36] = nDSCP_DropPrecedence36;
    param.nDSCP_DropPrecedence[37] = nDSCP_DropPrecedence37;
    param.nDSCP_DropPrecedence[38] = nDSCP_DropPrecedence38;
    param.nDSCP_DropPrecedence[39] = nDSCP_DropPrecedence39;
    param.nDSCP_DropPrecedence[40] = nDSCP_DropPrecedence40;
    param.nDSCP_DropPrecedence[41] = nDSCP_DropPrecedence41;
    param.nDSCP_DropPrecedence[42] = nDSCP_DropPrecedence42;
    param.nDSCP_DropPrecedence[43] = nDSCP_DropPrecedence43;
    param.nDSCP_DropPrecedence[44] = nDSCP_DropPrecedence44;
    param.nDSCP_DropPrecedence[45] = nDSCP_DropPrecedence45;
    param.nDSCP_DropPrecedence[46] = nDSCP_DropPrecedence46;
    param.nDSCP_DropPrecedence[47] = nDSCP_DropPrecedence47;
    param.nDSCP_DropPrecedence[48] = nDSCP_DropPrecedence48;
    param.nDSCP_DropPrecedence[49] = nDSCP_DropPrecedence49;
    param.nDSCP_DropPrecedence[50] = nDSCP_DropPrecedence50;
    param.nDSCP_DropPrecedence[51] = nDSCP_DropPrecedence51;
    param.nDSCP_DropPrecedence[52] = nDSCP_DropPrecedence52;
    param.nDSCP_DropPrecedence[53] = nDSCP_DropPrecedence53;
    param.nDSCP_DropPrecedence[54] = nDSCP_DropPrecedence54;
    param.nDSCP_DropPrecedence[55] = nDSCP_DropPrecedence55;
    param.nDSCP_DropPrecedence[56] = nDSCP_DropPrecedence56;
    param.nDSCP_DropPrecedence[57] = nDSCP_DropPrecedence57;
    param.nDSCP_DropPrecedence[58] = nDSCP_DropPrecedence58;
    param.nDSCP_DropPrecedence[59] = nDSCP_DropPrecedence59;
    param.nDSCP_DropPrecedence[60] = nDSCP_DropPrecedence60;
    param.nDSCP_DropPrecedence[61] = nDSCP_DropPrecedence61;
    param.nDSCP_DropPrecedence[62] = nDSCP_DropPrecedence62;
    param.nDSCP_DropPrecedence[63] = nDSCP_DropPrecedence63;

    ret = GSW_QoS_DSCP_DropPrecedenceCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_FlowctrlCfgGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_FlowCtrlCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_FlowCtrlCfg_t));

    ret = GSW_QoS_FlowctrlCfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_FlowctrlCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFlowCtrlNonConform_Min", param.nFlowCtrlNonConform_Min, param.nFlowCtrlNonConform_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFlowCtrlNonConform_Max", param.nFlowCtrlNonConform_Max, param.nFlowCtrlNonConform_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFlowCtrlConform_Min", param.nFlowCtrlConform_Min, param.nFlowCtrlConform_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFlowCtrlConform_Max", param.nFlowCtrlConform_Max, param.nFlowCtrlConform_Max);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_FlowctrlCfgSet(u32 nFlowCtrlNonConform_Min, u32 nFlowCtrlNonConform_Max, u32 nFlowCtrlConform_Min, \
          u32 nFlowCtrlConform_Max)
{
    int ret;
    GSW_QoS_FlowCtrlCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_FlowCtrlCfg_t));
    param.nFlowCtrlNonConform_Min = nFlowCtrlNonConform_Min;
    param.nFlowCtrlNonConform_Max = nFlowCtrlNonConform_Max;
    param.nFlowCtrlConform_Min = nFlowCtrlConform_Min;
    param.nFlowCtrlConform_Max = nFlowCtrlConform_Max;

    ret = GSW_QoS_FlowctrlCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_FlowctrlPortCfgGet(u32 nPortId)
{
    FILE *fp;
    int ret;
    GSW_QoS_FlowCtrlPortCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_FlowCtrlPortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_QoS_FlowctrlPortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_FlowctrlPortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFlowCtrl_Min", param.nFlowCtrl_Min, param.nFlowCtrl_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFlowCtrl_Max", param.nFlowCtrl_Max, param.nFlowCtrl_Max);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_FlowctrlPortCfgSet(u32 nPortId, u32 nFlowCtrl_Min, u32 nFlowCtrl_Max)
{
    int ret;
    GSW_QoS_FlowCtrlPortCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_FlowCtrlPortCfg_t));
    param.nPortId = nPortId;
    param.nFlowCtrl_Min = nFlowCtrl_Min;
    param.nFlowCtrl_Max = nFlowCtrl_Max;

    ret = GSW_QoS_FlowctrlPortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_MeterCfgGet(u32 nMeterId)
{
    FILE *fp;
    int ret;
    GSW_QoS_meterCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_meterCfg_t));
    param.nMeterId = nMeterId;

    ret = GSW_QoS_MeterCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_MeterCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bEnable", param.bEnable, param.bEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nMeterId", param.nMeterId, param.nMeterId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nCbs", param.nCbs, param.nCbs);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nEbs", param.nEbs, param.nEbs);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRate", param.nRate, param.nRate);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_MeterCfgSet(ltq_bool_t bEnable, u32 nMeterId, u32 nCbs, u32 nEbs, u32 nRate)
{
    int ret;
    GSW_QoS_meterCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_meterCfg_t));
    param.bEnable = bEnable;
    param.nMeterId = nMeterId;
    param.nCbs = nCbs;
    param.nEbs = nEbs;
    param.nRate = nRate;

    ret = GSW_QoS_MeterCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_MeterPortAssign(u32 nMeterId, GSW_direction_t eDir, u32 nPortIngressId, u32 nPortEgressId)
{
    int ret;
    GSW_QoS_meterPort_t  param;

    memset( &param, 0, sizeof(GSW_QoS_meterPort_t));
    param.nMeterId = nMeterId;
    param.eDir = eDir;
    param.nPortIngressId = nPortIngressId;
    param.nPortEgressId = nPortEgressId;

    ret = GSW_QoS_MeterPortAssign(pedev0, &param);

    return ret;
}

int pyGSW_QoS_MeterPortDeassign(u32 nMeterId, u32 nPortIngressId, u32 nPortEgressId)
{
    FILE *fp;
    int ret;
    GSW_QoS_meterPort_t  param;

    memset( &param, 0, sizeof(GSW_QoS_meterPort_t));
    param.nMeterId = nMeterId;
    param.nPortIngressId = nPortIngressId;
    param.nPortEgressId = nPortEgressId;

    ret = GSW_QoS_MeterPortDeassign(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_MeterPortDeassign");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nMeterId", param.nMeterId, param.nMeterId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eDir", param.eDir, param.eDir);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortIngressId", param.nPortIngressId, param.nPortIngressId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortEgressId", param.nPortEgressId, param.nPortEgressId);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_MeterPortGet(ltq_bool_t bInitial)
{
    FILE *fp;
    int ret;
    GSW_QoS_meterPortGet_t  param;

    memset( &param, 0, sizeof(GSW_QoS_meterPortGet_t));
    param.bInitial = bInitial;

    ret = GSW_QoS_MeterPortGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_MeterPortGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bInitial", param.bInitial, param.bInitial);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLast", param.bLast, param.bLast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eDir", param.eDir, param.eDir);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nMeterId", param.nMeterId, param.nMeterId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortIngressId", param.nPortIngressId, param.nPortIngressId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortEgressId", param.nPortEgressId, param.nPortEgressId);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_PCP_ClassGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_PCP_ClassCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_PCP_ClassCfg_t));

    ret = GSW_QoS_PCP_ClassGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_PCP_ClassGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPCP", param.nPCP, param.nPCP);
    fprintf(fp, "%s = [", "nTrafficClass[8]");
    fprintf(fp, " 0x%02x", param.nTrafficClass[0]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[1]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[2]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[3]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[4]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[5]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[6]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[7]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_QoS_PCP_ClassSet(u8 nPCP, u8 nTrafficClass0, u8 nTrafficClass1, u8 nTrafficClass2, u8 nTrafficClass3, \
          u8 nTrafficClass4, u8 nTrafficClass5, u8 nTrafficClass6, u8 nTrafficClass7)
{
    int ret;
    GSW_QoS_PCP_ClassCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_PCP_ClassCfg_t));
    param.nPCP = nPCP;
    param.nTrafficClass[0] = nTrafficClass0;
    param.nTrafficClass[1] = nTrafficClass1;
    param.nTrafficClass[2] = nTrafficClass2;
    param.nTrafficClass[3] = nTrafficClass3;
    param.nTrafficClass[4] = nTrafficClass4;
    param.nTrafficClass[5] = nTrafficClass5;
    param.nTrafficClass[6] = nTrafficClass6;
    param.nTrafficClass[7] = nTrafficClass7;

    ret = GSW_QoS_PCP_ClassSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_QoS_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_portCfg_t));
    param.nPortId = nPortId;

    ret = GSW_QoS_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eClassMode", param.eClassMode, param.eClassMode);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTrafficClass", param.nTrafficClass, param.nTrafficClass);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_PortCfgSet(u8 nPortId, GSW_QoS_ClassSelect_t eClassMode, u8 nTrafficClass)
{
    int ret;
    GSW_QoS_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_portCfg_t));
    param.nPortId = nPortId;
    param.eClassMode = eClassMode;
    param.nTrafficClass = nTrafficClass;

    ret = GSW_QoS_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_PortRemarkingCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_QoS_portRemarkingCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_portRemarkingCfg_t));
    param.nPortId = nPortId;

    ret = GSW_QoS_PortRemarkingCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_PortRemarkingCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eDSCP_IngressRemarkingEnable", param.eDSCP_IngressRemarkingEnable, param.eDSCP_IngressRemarkingEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bDSCP_EgressRemarkingEnable", param.bDSCP_EgressRemarkingEnable, param.bDSCP_EgressRemarkingEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bPCP_IngressRemarkingEnable", param.bPCP_IngressRemarkingEnable, param.bPCP_IngressRemarkingEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bPCP_EgressRemarkingEnable", param.bPCP_EgressRemarkingEnable, param.bPCP_EgressRemarkingEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSTAG_PCP_IngressRemarkingEnable", param.bSTAG_PCP_IngressRemarkingEnable, param.bSTAG_PCP_IngressRemarkingEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSTAG_DEI_IngressRemarkingEnable", param.bSTAG_DEI_IngressRemarkingEnable, param.bSTAG_DEI_IngressRemarkingEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSTAG_PCP_DEI_EgressRemarkingEnable", param.bSTAG_PCP_DEI_EgressRemarkingEnable, param.bSTAG_PCP_DEI_EgressRemarkingEnable);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_PortRemarkingCfgSet(u8 nPortId, GSW_Qos_ingressRemarking_t eDSCP_IngressRemarkingEnable, \
          ltq_bool_t bDSCP_EgressRemarkingEnable, ltq_bool_t bPCP_IngressRemarkingEnable, ltq_bool_t bPCP_EgressRemarkingEnable, \
          ltq_bool_t bSTAG_PCP_IngressRemarkingEnable, ltq_bool_t bSTAG_DEI_IngressRemarkingEnable, \
          ltq_bool_t bSTAG_PCP_DEI_EgressRemarkingEnable)
{
    int ret;
    GSW_QoS_portRemarkingCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_portRemarkingCfg_t));
    param.nPortId = nPortId;
    param.eDSCP_IngressRemarkingEnable = eDSCP_IngressRemarkingEnable;
    param.bDSCP_EgressRemarkingEnable = bDSCP_EgressRemarkingEnable;
    param.bPCP_IngressRemarkingEnable = bPCP_IngressRemarkingEnable;
    param.bPCP_EgressRemarkingEnable = bPCP_EgressRemarkingEnable;
    param.bSTAG_PCP_IngressRemarkingEnable = bSTAG_PCP_IngressRemarkingEnable;
    param.bSTAG_DEI_IngressRemarkingEnable = bSTAG_DEI_IngressRemarkingEnable;
    param.bSTAG_PCP_DEI_EgressRemarkingEnable = bSTAG_PCP_DEI_EgressRemarkingEnable;

    ret = GSW_QoS_PortRemarkingCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_QueueBufferReserveCfgGet(u8 nQueueId)
{
    FILE *fp;
    int ret;
    GSW_QoS_QueueBufferReserveCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_QueueBufferReserveCfg_t));
    param.nQueueId = nQueueId;

    ret = GSW_QoS_QueueBufferReserveCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_QueueBufferReserveCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nQueueId", param.nQueueId, param.nQueueId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nBufferReserved", param.nBufferReserved, param.nBufferReserved);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_QueueBufferReserveCfgSet(u8 nQueueId, u32 nBufferReserved)
{
    int ret;
    GSW_QoS_QueueBufferReserveCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_QueueBufferReserveCfg_t));
    param.nQueueId = nQueueId;
    param.nBufferReserved = nBufferReserved;

    ret = GSW_QoS_QueueBufferReserveCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_QueuePortGet(u8 nPortId, u8 nTrafficClassId)
{
    FILE *fp;
    int ret;
    GSW_QoS_queuePort_t  param;

    memset( &param, 0, sizeof(GSW_QoS_queuePort_t));
    param.nPortId = nPortId;
    param.nTrafficClassId = nTrafficClassId;

    ret = GSW_QoS_QueuePortGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_QueuePortGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTrafficClassId", param.nTrafficClassId, param.nTrafficClassId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nQueueId", param.nQueueId, param.nQueueId);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_QueuePortSet(u8 nPortId, u8 nTrafficClassId, u8 nQueueId)
{
    int ret;
    GSW_QoS_queuePort_t  param;

    memset( &param, 0, sizeof(GSW_QoS_queuePort_t));
    param.nPortId = nPortId;
    param.nTrafficClassId = nTrafficClassId;
    param.nQueueId = nQueueId;

    ret = GSW_QoS_QueuePortSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_SVLAN_ClassPCP_PortGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_QoS_SVLAN_ClassPCP_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_SVLAN_ClassPCP_PortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_QoS_SVLAN_ClassPCP_PortGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_SVLAN_ClassPCP_PortGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTrafficClass", param.nTrafficClass, param.nTrafficClass);
    fprintf(fp, "%s = [", "nCPCP[16]");
    fprintf(fp, " 0x%02x", param.nCPCP[0]);
    fprintf(fp, " 0x%02x", param.nCPCP[1]);
    fprintf(fp, " 0x%02x", param.nCPCP[2]);
    fprintf(fp, " 0x%02x", param.nCPCP[3]);
    fprintf(fp, " 0x%02x", param.nCPCP[4]);
    fprintf(fp, " 0x%02x", param.nCPCP[5]);
    fprintf(fp, " 0x%02x", param.nCPCP[6]);
    fprintf(fp, " 0x%02x", param.nCPCP[7]);
    fprintf(fp, " 0x%02x", param.nCPCP[8]);
    fprintf(fp, " 0x%02x", param.nCPCP[9]);
    fprintf(fp, " 0x%02x", param.nCPCP[10]);
    fprintf(fp, " 0x%02x", param.nCPCP[11]);
    fprintf(fp, " 0x%02x", param.nCPCP[12]);
    fprintf(fp, " 0x%02x", param.nCPCP[13]);
    fprintf(fp, " 0x%02x", param.nCPCP[14]);
    fprintf(fp, " 0x%02x", param.nCPCP[15]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "nSPCP[16]");
    fprintf(fp, " 0x%02x", param.nSPCP[0]);
    fprintf(fp, " 0x%02x", param.nSPCP[1]);
    fprintf(fp, " 0x%02x", param.nSPCP[2]);
    fprintf(fp, " 0x%02x", param.nSPCP[3]);
    fprintf(fp, " 0x%02x", param.nSPCP[4]);
    fprintf(fp, " 0x%02x", param.nSPCP[5]);
    fprintf(fp, " 0x%02x", param.nSPCP[6]);
    fprintf(fp, " 0x%02x", param.nSPCP[7]);
    fprintf(fp, " 0x%02x", param.nSPCP[8]);
    fprintf(fp, " 0x%02x", param.nSPCP[9]);
    fprintf(fp, " 0x%02x", param.nSPCP[10]);
    fprintf(fp, " 0x%02x", param.nSPCP[11]);
    fprintf(fp, " 0x%02x", param.nSPCP[12]);
    fprintf(fp, " 0x%02x", param.nSPCP[13]);
    fprintf(fp, " 0x%02x", param.nSPCP[14]);
    fprintf(fp, " 0x%02x", param.nSPCP[15]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "nDSCP[16]");
    fprintf(fp, " 0x%02x", param.nDSCP[0]);
    fprintf(fp, " 0x%02x", param.nDSCP[1]);
    fprintf(fp, " 0x%02x", param.nDSCP[2]);
    fprintf(fp, " 0x%02x", param.nDSCP[3]);
    fprintf(fp, " 0x%02x", param.nDSCP[4]);
    fprintf(fp, " 0x%02x", param.nDSCP[5]);
    fprintf(fp, " 0x%02x", param.nDSCP[6]);
    fprintf(fp, " 0x%02x", param.nDSCP[7]);
    fprintf(fp, " 0x%02x", param.nDSCP[8]);
    fprintf(fp, " 0x%02x", param.nDSCP[9]);
    fprintf(fp, " 0x%02x", param.nDSCP[10]);
    fprintf(fp, " 0x%02x", param.nDSCP[11]);
    fprintf(fp, " 0x%02x", param.nDSCP[12]);
    fprintf(fp, " 0x%02x", param.nDSCP[13]);
    fprintf(fp, " 0x%02x", param.nDSCP[14]);
    fprintf(fp, " 0x%02x", param.nDSCP[15]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_QoS_SVLAN_ClassPCP_PortSet(u8 nPortId, u8 nTrafficClass, u8 nCPCP0, u8 nCPCP1, u8 nCPCP2, u8 nCPCP3, \
          u8 nCPCP4, u8 nCPCP5, u8 nCPCP6, u8 nCPCP7, u8 nCPCP8, u8 nCPCP9, u8 nCPCP10, u8 nCPCP11, \
          u8 nCPCP12, u8 nCPCP13, u8 nCPCP14, u8 nCPCP15, u8 nSPCP0, u8 nSPCP1, u8 nSPCP2, u8 nSPCP3, \
          u8 nSPCP4, u8 nSPCP5, u8 nSPCP6, u8 nSPCP7, u8 nSPCP8, u8 nSPCP9, u8 nSPCP10, u8 nSPCP11, \
          u8 nSPCP12, u8 nSPCP13, u8 nSPCP14, u8 nSPCP15, u8 nDSCP0, u8 nDSCP1, u8 nDSCP2, u8 nDSCP3, \
          u8 nDSCP4, u8 nDSCP5, u8 nDSCP6, u8 nDSCP7, u8 nDSCP8, u8 nDSCP9, u8 nDSCP10, u8 nDSCP11, \
          u8 nDSCP12, u8 nDSCP13, u8 nDSCP14, u8 nDSCP15)
{
    int ret;
    GSW_QoS_SVLAN_ClassPCP_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_SVLAN_ClassPCP_PortCfg_t));
    param.nPortId = nPortId;
    param.nTrafficClass = nTrafficClass;
    param.nCPCP[0] = nCPCP0;
    param.nCPCP[1] = nCPCP1;
    param.nCPCP[2] = nCPCP2;
    param.nCPCP[3] = nCPCP3;
    param.nCPCP[4] = nCPCP4;
    param.nCPCP[5] = nCPCP5;
    param.nCPCP[6] = nCPCP6;
    param.nCPCP[7] = nCPCP7;
    param.nCPCP[8] = nCPCP8;
    param.nCPCP[9] = nCPCP9;
    param.nCPCP[10] = nCPCP10;
    param.nCPCP[11] = nCPCP11;
    param.nCPCP[12] = nCPCP12;
    param.nCPCP[13] = nCPCP13;
    param.nCPCP[14] = nCPCP14;
    param.nCPCP[15] = nCPCP15;
    param.nSPCP[0] = nSPCP0;
    param.nSPCP[1] = nSPCP1;
    param.nSPCP[2] = nSPCP2;
    param.nSPCP[3] = nSPCP3;
    param.nSPCP[4] = nSPCP4;
    param.nSPCP[5] = nSPCP5;
    param.nSPCP[6] = nSPCP6;
    param.nSPCP[7] = nSPCP7;
    param.nSPCP[8] = nSPCP8;
    param.nSPCP[9] = nSPCP9;
    param.nSPCP[10] = nSPCP10;
    param.nSPCP[11] = nSPCP11;
    param.nSPCP[12] = nSPCP12;
    param.nSPCP[13] = nSPCP13;
    param.nSPCP[14] = nSPCP14;
    param.nSPCP[15] = nSPCP15;
    param.nDSCP[0] = nDSCP0;
    param.nDSCP[1] = nDSCP1;
    param.nDSCP[2] = nDSCP2;
    param.nDSCP[3] = nDSCP3;
    param.nDSCP[4] = nDSCP4;
    param.nDSCP[5] = nDSCP5;
    param.nDSCP[6] = nDSCP6;
    param.nDSCP[7] = nDSCP7;
    param.nDSCP[8] = nDSCP8;
    param.nDSCP[9] = nDSCP9;
    param.nDSCP[10] = nDSCP10;
    param.nDSCP[11] = nDSCP11;
    param.nDSCP[12] = nDSCP12;
    param.nDSCP[13] = nDSCP13;
    param.nDSCP[14] = nDSCP14;
    param.nDSCP[15] = nDSCP15;

    ret = GSW_QoS_SVLAN_ClassPCP_PortSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_SVLAN_PCP_ClassGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_SVLAN_PCP_ClassCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_SVLAN_PCP_ClassCfg_t));

    ret = GSW_QoS_SVLAN_PCP_ClassGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_SVLAN_PCP_ClassGet");
    fprintf(fp, "%s = [", "nTrafficClass[16]");
    fprintf(fp, " 0x%02x", param.nTrafficClass[0]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[1]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[2]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[3]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[4]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[5]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[6]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[7]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[8]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[9]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[10]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[11]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[12]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[13]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[14]);
    fprintf(fp, " 0x%02x", param.nTrafficClass[15]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "nTrafficColor[16]");
    fprintf(fp, " 0x%02x", param.nTrafficColor[0]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[1]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[2]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[3]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[4]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[5]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[6]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[7]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[8]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[9]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[10]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[11]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[12]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[13]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[14]);
    fprintf(fp, " 0x%02x", param.nTrafficColor[15]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "nPCP_Remark_Enable[16]");
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[0]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[1]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[2]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[3]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[4]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[5]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[6]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[7]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[8]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[9]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[10]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[11]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[12]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[13]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[14]);
    fprintf(fp, " 0x%02x", param.nPCP_Remark_Enable[15]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "nDEI_Remark_Enable[16]");
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[0]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[1]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[2]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[3]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[4]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[5]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[6]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[7]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[8]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[9]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[10]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[11]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[12]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[13]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[14]);
    fprintf(fp, " 0x%02x", param.nDEI_Remark_Enable[15]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

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
          u8 nDEI_Remark_Enable14, u8 nDEI_Remark_Enable15)
{
    int ret;
    GSW_QoS_SVLAN_PCP_ClassCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_SVLAN_PCP_ClassCfg_t));
    param.nTrafficClass[0] = nTrafficClass0;
    param.nTrafficClass[1] = nTrafficClass1;
    param.nTrafficClass[2] = nTrafficClass2;
    param.nTrafficClass[3] = nTrafficClass3;
    param.nTrafficClass[4] = nTrafficClass4;
    param.nTrafficClass[5] = nTrafficClass5;
    param.nTrafficClass[6] = nTrafficClass6;
    param.nTrafficClass[7] = nTrafficClass7;
    param.nTrafficClass[8] = nTrafficClass8;
    param.nTrafficClass[9] = nTrafficClass9;
    param.nTrafficClass[10] = nTrafficClass10;
    param.nTrafficClass[11] = nTrafficClass11;
    param.nTrafficClass[12] = nTrafficClass12;
    param.nTrafficClass[13] = nTrafficClass13;
    param.nTrafficClass[14] = nTrafficClass14;
    param.nTrafficClass[15] = nTrafficClass15;
    param.nTrafficColor[0] = nTrafficColor0;
    param.nTrafficColor[1] = nTrafficColor1;
    param.nTrafficColor[2] = nTrafficColor2;
    param.nTrafficColor[3] = nTrafficColor3;
    param.nTrafficColor[4] = nTrafficColor4;
    param.nTrafficColor[5] = nTrafficColor5;
    param.nTrafficColor[6] = nTrafficColor6;
    param.nTrafficColor[7] = nTrafficColor7;
    param.nTrafficColor[8] = nTrafficColor8;
    param.nTrafficColor[9] = nTrafficColor9;
    param.nTrafficColor[10] = nTrafficColor10;
    param.nTrafficColor[11] = nTrafficColor11;
    param.nTrafficColor[12] = nTrafficColor12;
    param.nTrafficColor[13] = nTrafficColor13;
    param.nTrafficColor[14] = nTrafficColor14;
    param.nTrafficColor[15] = nTrafficColor15;
    param.nPCP_Remark_Enable[0] = nPCP_Remark_Enable0;
    param.nPCP_Remark_Enable[1] = nPCP_Remark_Enable1;
    param.nPCP_Remark_Enable[2] = nPCP_Remark_Enable2;
    param.nPCP_Remark_Enable[3] = nPCP_Remark_Enable3;
    param.nPCP_Remark_Enable[4] = nPCP_Remark_Enable4;
    param.nPCP_Remark_Enable[5] = nPCP_Remark_Enable5;
    param.nPCP_Remark_Enable[6] = nPCP_Remark_Enable6;
    param.nPCP_Remark_Enable[7] = nPCP_Remark_Enable7;
    param.nPCP_Remark_Enable[8] = nPCP_Remark_Enable8;
    param.nPCP_Remark_Enable[9] = nPCP_Remark_Enable9;
    param.nPCP_Remark_Enable[10] = nPCP_Remark_Enable10;
    param.nPCP_Remark_Enable[11] = nPCP_Remark_Enable11;
    param.nPCP_Remark_Enable[12] = nPCP_Remark_Enable12;
    param.nPCP_Remark_Enable[13] = nPCP_Remark_Enable13;
    param.nPCP_Remark_Enable[14] = nPCP_Remark_Enable14;
    param.nPCP_Remark_Enable[15] = nPCP_Remark_Enable15;
    param.nDEI_Remark_Enable[0] = nDEI_Remark_Enable0;
    param.nDEI_Remark_Enable[1] = nDEI_Remark_Enable1;
    param.nDEI_Remark_Enable[2] = nDEI_Remark_Enable2;
    param.nDEI_Remark_Enable[3] = nDEI_Remark_Enable3;
    param.nDEI_Remark_Enable[4] = nDEI_Remark_Enable4;
    param.nDEI_Remark_Enable[5] = nDEI_Remark_Enable5;
    param.nDEI_Remark_Enable[6] = nDEI_Remark_Enable6;
    param.nDEI_Remark_Enable[7] = nDEI_Remark_Enable7;
    param.nDEI_Remark_Enable[8] = nDEI_Remark_Enable8;
    param.nDEI_Remark_Enable[9] = nDEI_Remark_Enable9;
    param.nDEI_Remark_Enable[10] = nDEI_Remark_Enable10;
    param.nDEI_Remark_Enable[11] = nDEI_Remark_Enable11;
    param.nDEI_Remark_Enable[12] = nDEI_Remark_Enable12;
    param.nDEI_Remark_Enable[13] = nDEI_Remark_Enable13;
    param.nDEI_Remark_Enable[14] = nDEI_Remark_Enable14;
    param.nDEI_Remark_Enable[15] = nDEI_Remark_Enable15;

    ret = GSW_QoS_SVLAN_PCP_ClassSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_SchedulerCfgGet(u8 nQueueId)
{
    FILE *fp;
    int ret;
    GSW_QoS_schedulerCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_schedulerCfg_t));
    param.nQueueId = nQueueId;

    ret = GSW_QoS_SchedulerCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_SchedulerCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nQueueId", param.nQueueId, param.nQueueId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eType", param.eType, param.eType);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nWeight", param.nWeight, param.nWeight);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_SchedulerCfgSet(u8 nQueueId, GSW_QoS_Scheduler_t eType, u32 nWeight)
{
    int ret;
    GSW_QoS_schedulerCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_schedulerCfg_t));
    param.nQueueId = nQueueId;
    param.eType = eType;
    param.nWeight = nWeight;

    ret = GSW_QoS_SchedulerCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_ShaperCfgGet(u32 nRateShaperId)
{
    FILE *fp;
    int ret;
    GSW_QoS_ShaperCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ShaperCfg_t));
    param.nRateShaperId = nRateShaperId;

    ret = GSW_QoS_ShaperCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_ShaperCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRateShaperId", param.nRateShaperId, param.nRateShaperId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bEnable", param.bEnable, param.bEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bAVB", param.bAVB, param.bAVB);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nCbs", param.nCbs, param.nCbs);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRate", param.nRate, param.nRate);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_ShaperCfgSet(u32 nRateShaperId, ltq_bool_t bEnable, ltq_bool_t bAVB, u32 nCbs, u32 nRate)
{
    int ret;
    GSW_QoS_ShaperCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ShaperCfg_t));
    param.nRateShaperId = nRateShaperId;
    param.bEnable = bEnable;
    param.bAVB = bAVB;
    param.nCbs = nCbs;
    param.nRate = nRate;

    ret = GSW_QoS_ShaperCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_ShaperQueueAssign(u8 nRateShaperId, u8 nQueueId)
{
    int ret;
    GSW_QoS_ShaperQueue_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ShaperQueue_t));
    param.nRateShaperId = nRateShaperId;
    param.nQueueId = nQueueId;

    ret = GSW_QoS_ShaperQueueAssign(pedev0, &param);

    return ret;
}

int pyGSW_QoS_ShaperQueueDeassign(u8 nRateShaperId, u8 nQueueId)
{
    int ret;
    GSW_QoS_ShaperQueue_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ShaperQueue_t));
    param.nRateShaperId = nRateShaperId;
    param.nQueueId = nQueueId;

    ret = GSW_QoS_ShaperQueueDeassign(pedev0, &param);

    return ret;
}

int pyGSW_QoS_ShaperQueueGet(u8 nQueueId)
{
    FILE *fp;
    int ret;
    GSW_QoS_ShaperQueueGet_t  param;

    memset( &param, 0, sizeof(GSW_QoS_ShaperQueueGet_t));
    param.nQueueId = nQueueId;

    ret = GSW_QoS_ShaperQueueGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_ShaperQueueGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nQueueId", param.nQueueId, param.nQueueId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bAssigned", param.bAssigned, param.bAssigned);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRateShaperId", param.nRateShaperId, param.nRateShaperId);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_StormCfgGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_stormCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_stormCfg_t));

    ret = GSW_QoS_StormCfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_StormCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nMeterId", param.nMeterId, param.nMeterId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bBroadcast", param.bBroadcast, param.bBroadcast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMulticast", param.bMulticast, param.bMulticast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bUnknownUnicast", param.bUnknownUnicast, param.bUnknownUnicast);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_StormCfgSet(int nMeterId, ltq_bool_t bBroadcast, ltq_bool_t bMulticast, ltq_bool_t bUnknownUnicast)
{
    int ret;
    GSW_QoS_stormCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_stormCfg_t));
    param.nMeterId = nMeterId;
    param.bBroadcast = bBroadcast;
    param.bMulticast = bMulticast;
    param.bUnknownUnicast = bUnknownUnicast;

    ret = GSW_QoS_StormCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_WredCfgGet()
{
    FILE *fp;
    int ret;
    GSW_QoS_WRED_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_WRED_Cfg_t));

    ret = GSW_QoS_WredCfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_WredCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "eProfile", param.eProfile, param.eProfile);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eThreshMode", param.eThreshMode, param.eThreshMode);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRed_Min", param.nRed_Min, param.nRed_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRed_Max", param.nRed_Max, param.nRed_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nYellow_Min", param.nYellow_Min, param.nYellow_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nYellow_Max", param.nYellow_Max, param.nYellow_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nGreen_Min", param.nGreen_Min, param.nGreen_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nGreen_Max", param.nGreen_Max, param.nGreen_Max);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_WredCfgSet(GSW_QoS_WRED_Profile_t eProfile, GSW_QoS_WRED_ThreshMode_t eThreshMode, u32 nRed_Min, \
          u32 nRed_Max, u32 nYellow_Min, u32 nYellow_Max, u32 nGreen_Min, u32 nGreen_Max)
{
    int ret;
    GSW_QoS_WRED_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_WRED_Cfg_t));
    param.eProfile = eProfile;
    param.eThreshMode = eThreshMode;
    param.nRed_Min = nRed_Min;
    param.nRed_Max = nRed_Max;
    param.nYellow_Min = nYellow_Min;
    param.nYellow_Max = nYellow_Max;
    param.nGreen_Min = nGreen_Min;
    param.nGreen_Max = nGreen_Max;

    ret = GSW_QoS_WredCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_WredPortCfgGet(u32 nPortId)
{
    FILE *fp;
    int ret;
    GSW_QoS_WRED_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_WRED_PortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_QoS_WredPortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_WredPortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRed_Min", param.nRed_Min, param.nRed_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRed_Max", param.nRed_Max, param.nRed_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nYellow_Min", param.nYellow_Min, param.nYellow_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nYellow_Max", param.nYellow_Max, param.nYellow_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nGreen_Min", param.nGreen_Min, param.nGreen_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nGreen_Max", param.nGreen_Max, param.nGreen_Max);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_WredPortCfgSet(u32 nPortId, u32 nRed_Min, u32 nRed_Max, u32 nYellow_Min, u32 nYellow_Max, \
          u32 nGreen_Min, u32 nGreen_Max)
{
    int ret;
    GSW_QoS_WRED_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_WRED_PortCfg_t));
    param.nPortId = nPortId;
    param.nRed_Min = nRed_Min;
    param.nRed_Max = nRed_Max;
    param.nYellow_Min = nYellow_Min;
    param.nYellow_Max = nYellow_Max;
    param.nGreen_Min = nGreen_Min;
    param.nGreen_Max = nGreen_Max;

    ret = GSW_QoS_WredPortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_QoS_WredQueueCfgGet(u32 nQueueId)
{
    FILE *fp;
    int ret;
    GSW_QoS_WRED_QueueCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_WRED_QueueCfg_t));
    param.nQueueId = nQueueId;

    ret = GSW_QoS_WredQueueCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_QoS_WredQueueCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nQueueId", param.nQueueId, param.nQueueId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRed_Min", param.nRed_Min, param.nRed_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRed_Max", param.nRed_Max, param.nRed_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nYellow_Min", param.nYellow_Min, param.nYellow_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nYellow_Max", param.nYellow_Max, param.nYellow_Max);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nGreen_Min", param.nGreen_Min, param.nGreen_Min);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nGreen_Max", param.nGreen_Max, param.nGreen_Max);
    fclose(fp);

    return ret;
}

int pyGSW_QoS_WredQueueCfgSet(u32 nQueueId, u32 nRed_Min, u32 nRed_Max, u32 nYellow_Min, u32 nYellow_Max, \
          u32 nGreen_Min, u32 nGreen_Max)
{
    int ret;
    GSW_QoS_WRED_QueueCfg_t  param;

    memset( &param, 0, sizeof(GSW_QoS_WRED_QueueCfg_t));
    param.nQueueId = nQueueId;
    param.nRed_Min = nRed_Min;
    param.nRed_Max = nRed_Max;
    param.nYellow_Min = nYellow_Min;
    param.nYellow_Max = nYellow_Max;
    param.nGreen_Min = nGreen_Min;
    param.nGreen_Max = nGreen_Max;

    ret = GSW_QoS_WredQueueCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_MulticastRouterPortAdd(u8 nPortId)
{
    int ret;
    GSW_multicastRouter_t  param;

    memset( &param, 0, sizeof(GSW_multicastRouter_t));
    param.nPortId = nPortId;

    ret = GSW_MulticastRouterPortAdd(pedev0, &param);

    return ret;
}

int pyGSW_MulticastRouterPortRead(ltq_bool_t bInitial)
{
    FILE *fp;
    int ret;
    GSW_multicastRouterRead_t  param;

    memset( &param, 0, sizeof(GSW_multicastRouterRead_t));
    param.bInitial = bInitial;

    ret = GSW_MulticastRouterPortRead(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MulticastRouterPortRead");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bInitial", param.bInitial, param.bInitial);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLast", param.bLast, param.bLast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fclose(fp);

    return ret;
}

int pyGSW_MulticastRouterPortRemove(u8 nPortId)
{
    int ret;
    GSW_multicastRouter_t  param;

    memset( &param, 0, sizeof(GSW_multicastRouter_t));
    param.nPortId = nPortId;

    ret = GSW_MulticastRouterPortRemove(pedev0, &param);

    return ret;
}

int pyGSW_MulticastSnoopCfgGet()
{
    FILE *fp;
    int ret;
    GSW_multicastSnoopCfg_t  param;

    memset( &param, 0, sizeof(GSW_multicastSnoopCfg_t));

    ret = GSW_MulticastSnoopCfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MulticastSnoopCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "eIGMP_Mode", param.eIGMP_Mode, param.eIGMP_Mode);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bIGMPv3", param.bIGMPv3, param.bIGMPv3);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bCrossVLAN", param.bCrossVLAN, param.bCrossVLAN);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eForwardPort", param.eForwardPort, param.eForwardPort);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nForwardPortId", param.nForwardPortId, param.nForwardPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nClassOfService", param.nClassOfService, param.nClassOfService);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRobust", param.nRobust, param.nRobust);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nQueryInterval", param.nQueryInterval, param.nQueryInterval);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eSuppressionAggregation", param.eSuppressionAggregation, param.eSuppressionAggregation);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bFastLeave", param.bFastLeave, param.bFastLeave);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLearningRouter", param.bLearningRouter, param.bLearningRouter);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMulticastUnknownDrop", param.bMulticastUnknownDrop, param.bMulticastUnknownDrop);
    fclose(fp);

    return ret;
}

int pyGSW_MulticastSnoopCfgSet(GSW_multicastSnoopMode_t eIGMP_Mode, ltq_bool_t bIGMPv3, ltq_bool_t bCrossVLAN, \
          GSW_portForward_t eForwardPort, u8 nForwardPortId, u8 nClassOfService, u8 nRobust, u8 nQueryInterval, \
          GSW_multicastReportSuppression_t eSuppressionAggregation, ltq_bool_t bFastLeave, ltq_bool_t bLearningRouter, \
          ltq_bool_t bMulticastUnknownDrop)
{
    int ret;
    GSW_multicastSnoopCfg_t  param;

    memset( &param, 0, sizeof(GSW_multicastSnoopCfg_t));
    param.eIGMP_Mode = eIGMP_Mode;
    param.bIGMPv3 = bIGMPv3;
    param.bCrossVLAN = bCrossVLAN;
    param.eForwardPort = eForwardPort;
    param.nForwardPortId = nForwardPortId;
    param.nClassOfService = nClassOfService;
    param.nRobust = nRobust;
    param.nQueryInterval = nQueryInterval;
    param.eSuppressionAggregation = eSuppressionAggregation;
    param.bFastLeave = bFastLeave;
    param.bLearningRouter = bLearningRouter;
    param.bMulticastUnknownDrop = bMulticastUnknownDrop;

    ret = GSW_MulticastSnoopCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_MulticastTableEntryAdd(u32 nPortId, GSW_IP_Select_t eIPVersion, GSW_IP_t uIP_Gda, GSW_IP_t uIP_Gsa, \
          GSW_IGMP_MemberMode_t eModeMember)
{
    int ret;
    GSW_multicastTable_t  param;

    memset( &param, 0, sizeof(GSW_multicastTable_t));
    param.nPortId = nPortId;
    param.eIPVersion = eIPVersion;
    param.uIP_Gda = uIP_Gda;
    param.uIP_Gsa = uIP_Gsa;
    param.eModeMember = eModeMember;

    ret = GSW_MulticastTableEntryAdd(pedev0, &param);

    return ret;
}

int pyGSW_MulticastTableEntryRead(ltq_bool_t bInitial)
{
    FILE *fp;
    int ret;
    GSW_multicastTableRead_t  param;

    memset( &param, 0, sizeof(GSW_multicastTableRead_t));
    param.bInitial = bInitial;

    ret = GSW_MulticastTableEntryRead(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MulticastTableEntryRead");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bInitial", param.bInitial, param.bInitial);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLast", param.bLast, param.bLast);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eIPVersion", param.eIPVersion, param.eIPVersion);
    fprintf(fp, "%s = 0x%x, %d\r\n", "uIP_Gda", param.uIP_Gda, param.uIP_Gda);
    fprintf(fp, "%s = 0x%x, %d\r\n", "uIP_Gsa", param.uIP_Gsa, param.uIP_Gsa);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eModeMember", param.eModeMember, param.eModeMember);
    fclose(fp);

    return ret;
}

int pyGSW_MulticastTableEntryRemove(u32 nPortId, GSW_IP_Select_t eIPVersion, GSW_IP_t uIP_Gda, GSW_IP_t uIP_Gsa, \
          GSW_IGMP_MemberMode_t eModeMember)
{
    int ret;
    GSW_multicastTable_t  param;

    memset( &param, 0, sizeof(GSW_multicastTable_t));
    param.nPortId = nPortId;
    param.eIPVersion = eIPVersion;
    param.uIP_Gda = uIP_Gda;
    param.uIP_Gsa = uIP_Gsa;
    param.eModeMember = eModeMember;

    ret = GSW_MulticastTableEntryRemove(pedev0, &param);

    return ret;
}

int pyGSW_CPU_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_CPU_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_CPU_PortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_CPU_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_CPU_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bCPU_PortValid", param.bCPU_PortValid, param.bCPU_PortValid);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSpecialTagIngress", param.bSpecialTagIngress, param.bSpecialTagIngress);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSpecialTagEgress", param.bSpecialTagEgress, param.bSpecialTagEgress);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bFcsCheck", param.bFcsCheck, param.bFcsCheck);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bFcsGenerate", param.bFcsGenerate, param.bFcsGenerate);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSpecialTagEthType", param.bSpecialTagEthType, param.bSpecialTagEthType);
    fclose(fp);

    return ret;
}

int pyGSW_CPU_PortCfgSet(u8 nPortId, ltq_bool_t bCPU_PortValid, ltq_bool_t bSpecialTagIngress, ltq_bool_t bSpecialTagEgress, \
          ltq_bool_t bFcsCheck, ltq_bool_t bFcsGenerate, GSW_CPU_SpecialTagEthType_t bSpecialTagEthType)
{
    int ret;
    GSW_CPU_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_CPU_PortCfg_t));
    param.nPortId = nPortId;
    param.bCPU_PortValid = bCPU_PortValid;
    param.bSpecialTagIngress = bSpecialTagIngress;
    param.bSpecialTagEgress = bSpecialTagEgress;
    param.bFcsCheck = bFcsCheck;
    param.bFcsGenerate = bFcsGenerate;
    param.bSpecialTagEthType = bSpecialTagEthType;

    ret = GSW_CPU_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_CapGet(GSW_capType_t nCapType)
{
    FILE *fp;
    int ret;
    GSW_cap_t  param;

    memset( &param, 0, sizeof(GSW_cap_t));
    param.nCapType = nCapType;

    ret = GSW_CapGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_CapGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nCapType", param.nCapType, param.nCapType);
    fprintf(fp, "%s = [", "cDesc[128]");
    fprintf(fp, " 0x%02x", param.cDesc[0]);
    fprintf(fp, " 0x%02x", param.cDesc[1]);
    fprintf(fp, " 0x%02x", param.cDesc[2]);
    fprintf(fp, " 0x%02x", param.cDesc[3]);
    fprintf(fp, " 0x%02x", param.cDesc[4]);
    fprintf(fp, " 0x%02x", param.cDesc[5]);
    fprintf(fp, " 0x%02x", param.cDesc[6]);
    fprintf(fp, " 0x%02x", param.cDesc[7]);
    fprintf(fp, " 0x%02x", param.cDesc[8]);
    fprintf(fp, " 0x%02x", param.cDesc[9]);
    fprintf(fp, " 0x%02x", param.cDesc[10]);
    fprintf(fp, " 0x%02x", param.cDesc[11]);
    fprintf(fp, " 0x%02x", param.cDesc[12]);
    fprintf(fp, " 0x%02x", param.cDesc[13]);
    fprintf(fp, " 0x%02x", param.cDesc[14]);
    fprintf(fp, " 0x%02x", param.cDesc[15]);
    fprintf(fp, " 0x%02x", param.cDesc[16]);
    fprintf(fp, " 0x%02x", param.cDesc[17]);
    fprintf(fp, " 0x%02x", param.cDesc[18]);
    fprintf(fp, " 0x%02x", param.cDesc[19]);
    fprintf(fp, " 0x%02x", param.cDesc[20]);
    fprintf(fp, " 0x%02x", param.cDesc[21]);
    fprintf(fp, " 0x%02x", param.cDesc[22]);
    fprintf(fp, " 0x%02x", param.cDesc[23]);
    fprintf(fp, " 0x%02x", param.cDesc[24]);
    fprintf(fp, " 0x%02x", param.cDesc[25]);
    fprintf(fp, " 0x%02x", param.cDesc[26]);
    fprintf(fp, " 0x%02x", param.cDesc[27]);
    fprintf(fp, " 0x%02x", param.cDesc[28]);
    fprintf(fp, " 0x%02x", param.cDesc[29]);
    fprintf(fp, " 0x%02x", param.cDesc[30]);
    fprintf(fp, " 0x%02x", param.cDesc[31]);
    fprintf(fp, " 0x%02x", param.cDesc[32]);
    fprintf(fp, " 0x%02x", param.cDesc[33]);
    fprintf(fp, " 0x%02x", param.cDesc[34]);
    fprintf(fp, " 0x%02x", param.cDesc[35]);
    fprintf(fp, " 0x%02x", param.cDesc[36]);
    fprintf(fp, " 0x%02x", param.cDesc[37]);
    fprintf(fp, " 0x%02x", param.cDesc[38]);
    fprintf(fp, " 0x%02x", param.cDesc[39]);
    fprintf(fp, " 0x%02x", param.cDesc[40]);
    fprintf(fp, " 0x%02x", param.cDesc[41]);
    fprintf(fp, " 0x%02x", param.cDesc[42]);
    fprintf(fp, " 0x%02x", param.cDesc[43]);
    fprintf(fp, " 0x%02x", param.cDesc[44]);
    fprintf(fp, " 0x%02x", param.cDesc[45]);
    fprintf(fp, " 0x%02x", param.cDesc[46]);
    fprintf(fp, " 0x%02x", param.cDesc[47]);
    fprintf(fp, " 0x%02x", param.cDesc[48]);
    fprintf(fp, " 0x%02x", param.cDesc[49]);
    fprintf(fp, " 0x%02x", param.cDesc[50]);
    fprintf(fp, " 0x%02x", param.cDesc[51]);
    fprintf(fp, " 0x%02x", param.cDesc[52]);
    fprintf(fp, " 0x%02x", param.cDesc[53]);
    fprintf(fp, " 0x%02x", param.cDesc[54]);
    fprintf(fp, " 0x%02x", param.cDesc[55]);
    fprintf(fp, " 0x%02x", param.cDesc[56]);
    fprintf(fp, " 0x%02x", param.cDesc[57]);
    fprintf(fp, " 0x%02x", param.cDesc[58]);
    fprintf(fp, " 0x%02x", param.cDesc[59]);
    fprintf(fp, " 0x%02x", param.cDesc[60]);
    fprintf(fp, " 0x%02x", param.cDesc[61]);
    fprintf(fp, " 0x%02x", param.cDesc[62]);
    fprintf(fp, " 0x%02x", param.cDesc[63]);
    fprintf(fp, " 0x%02x", param.cDesc[64]);
    fprintf(fp, " 0x%02x", param.cDesc[65]);
    fprintf(fp, " 0x%02x", param.cDesc[66]);
    fprintf(fp, " 0x%02x", param.cDesc[67]);
    fprintf(fp, " 0x%02x", param.cDesc[68]);
    fprintf(fp, " 0x%02x", param.cDesc[69]);
    fprintf(fp, " 0x%02x", param.cDesc[70]);
    fprintf(fp, " 0x%02x", param.cDesc[71]);
    fprintf(fp, " 0x%02x", param.cDesc[72]);
    fprintf(fp, " 0x%02x", param.cDesc[73]);
    fprintf(fp, " 0x%02x", param.cDesc[74]);
    fprintf(fp, " 0x%02x", param.cDesc[75]);
    fprintf(fp, " 0x%02x", param.cDesc[76]);
    fprintf(fp, " 0x%02x", param.cDesc[77]);
    fprintf(fp, " 0x%02x", param.cDesc[78]);
    fprintf(fp, " 0x%02x", param.cDesc[79]);
    fprintf(fp, " 0x%02x", param.cDesc[80]);
    fprintf(fp, " 0x%02x", param.cDesc[81]);
    fprintf(fp, " 0x%02x", param.cDesc[82]);
    fprintf(fp, " 0x%02x", param.cDesc[83]);
    fprintf(fp, " 0x%02x", param.cDesc[84]);
    fprintf(fp, " 0x%02x", param.cDesc[85]);
    fprintf(fp, " 0x%02x", param.cDesc[86]);
    fprintf(fp, " 0x%02x", param.cDesc[87]);
    fprintf(fp, " 0x%02x", param.cDesc[88]);
    fprintf(fp, " 0x%02x", param.cDesc[89]);
    fprintf(fp, " 0x%02x", param.cDesc[90]);
    fprintf(fp, " 0x%02x", param.cDesc[91]);
    fprintf(fp, " 0x%02x", param.cDesc[92]);
    fprintf(fp, " 0x%02x", param.cDesc[93]);
    fprintf(fp, " 0x%02x", param.cDesc[94]);
    fprintf(fp, " 0x%02x", param.cDesc[95]);
    fprintf(fp, " 0x%02x", param.cDesc[96]);
    fprintf(fp, " 0x%02x", param.cDesc[97]);
    fprintf(fp, " 0x%02x", param.cDesc[98]);
    fprintf(fp, " 0x%02x", param.cDesc[99]);
    fprintf(fp, " 0x%02x", param.cDesc[100]);
    fprintf(fp, " 0x%02x", param.cDesc[101]);
    fprintf(fp, " 0x%02x", param.cDesc[102]);
    fprintf(fp, " 0x%02x", param.cDesc[103]);
    fprintf(fp, " 0x%02x", param.cDesc[104]);
    fprintf(fp, " 0x%02x", param.cDesc[105]);
    fprintf(fp, " 0x%02x", param.cDesc[106]);
    fprintf(fp, " 0x%02x", param.cDesc[107]);
    fprintf(fp, " 0x%02x", param.cDesc[108]);
    fprintf(fp, " 0x%02x", param.cDesc[109]);
    fprintf(fp, " 0x%02x", param.cDesc[110]);
    fprintf(fp, " 0x%02x", param.cDesc[111]);
    fprintf(fp, " 0x%02x", param.cDesc[112]);
    fprintf(fp, " 0x%02x", param.cDesc[113]);
    fprintf(fp, " 0x%02x", param.cDesc[114]);
    fprintf(fp, " 0x%02x", param.cDesc[115]);
    fprintf(fp, " 0x%02x", param.cDesc[116]);
    fprintf(fp, " 0x%02x", param.cDesc[117]);
    fprintf(fp, " 0x%02x", param.cDesc[118]);
    fprintf(fp, " 0x%02x", param.cDesc[119]);
    fprintf(fp, " 0x%02x", param.cDesc[120]);
    fprintf(fp, " 0x%02x", param.cDesc[121]);
    fprintf(fp, " 0x%02x", param.cDesc[122]);
    fprintf(fp, " 0x%02x", param.cDesc[123]);
    fprintf(fp, " 0x%02x", param.cDesc[124]);
    fprintf(fp, " 0x%02x", param.cDesc[125]);
    fprintf(fp, " 0x%02x", param.cDesc[126]);
    fprintf(fp, " 0x%02x", param.cDesc[127]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nCap", param.nCap, param.nCap);
    fclose(fp);

    return ret;
}

int pyGSW_CfgGet()
{
    FILE *fp;
    int ret;
    GSW_cfg_t  param;

    memset( &param, 0, sizeof(GSW_cfg_t));

    ret = GSW_CfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_CfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "eMAC_TableAgeTimer", param.eMAC_TableAgeTimer, param.eMAC_TableAgeTimer);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bVLAN_Aware", param.bVLAN_Aware, param.bVLAN_Aware);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nMaxPacketLen", param.nMaxPacketLen, param.nMaxPacketLen);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLearningLimitAction", param.bLearningLimitAction, param.bLearningLimitAction);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMAC_SpoofingAction", param.bMAC_SpoofingAction, param.bMAC_SpoofingAction);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bPauseMAC_ModeSrc", param.bPauseMAC_ModeSrc, param.bPauseMAC_ModeSrc);
    fprintf(fp, "%s = [", "nPauseMAC_Src[6]");
    fprintf(fp, " 0x%02x", param.nPauseMAC_Src[0]);
    fprintf(fp, " 0x%02x", param.nPauseMAC_Src[1]);
    fprintf(fp, " 0x%02x", param.nPauseMAC_Src[2]);
    fprintf(fp, " 0x%02x", param.nPauseMAC_Src[3]);
    fprintf(fp, " 0x%02x", param.nPauseMAC_Src[4]);
    fprintf(fp, " 0x%02x", param.nPauseMAC_Src[5]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_CfgSet(GSW_ageTimer_t eMAC_TableAgeTimer, ltq_bool_t bVLAN_Aware, u16 nMaxPacketLen, ltq_bool_t bLearningLimitAction, \
          ltq_bool_t bMAC_SpoofingAction, ltq_bool_t bPauseMAC_ModeSrc, u8 nPauseMAC_Src0, u8 nPauseMAC_Src1, \
          u8 nPauseMAC_Src2, u8 nPauseMAC_Src3, u8 nPauseMAC_Src4, u8 nPauseMAC_Src5)
{
    int ret;
    GSW_cfg_t  param;

    memset( &param, 0, sizeof(GSW_cfg_t));
    param.eMAC_TableAgeTimer = eMAC_TableAgeTimer;
    param.bVLAN_Aware = bVLAN_Aware;
    param.nMaxPacketLen = nMaxPacketLen;
    param.bLearningLimitAction = bLearningLimitAction;
    param.bMAC_SpoofingAction = bMAC_SpoofingAction;
    param.bPauseMAC_ModeSrc = bPauseMAC_ModeSrc;
    param.nPauseMAC_Src[0] = nPauseMAC_Src0;
    param.nPauseMAC_Src[1] = nPauseMAC_Src1;
    param.nPauseMAC_Src[2] = nPauseMAC_Src2;
    param.nPauseMAC_Src[3] = nPauseMAC_Src3;
    param.nPauseMAC_Src[4] = nPauseMAC_Src4;
    param.nPauseMAC_Src[5] = nPauseMAC_Src5;

    ret = GSW_CfgSet(pedev0, &param);

    return ret;
}

int pyGSW_Disable()
{
    int ret;

    ret = GSW_Disable(pedev0);

    return ret;
}

int pyGSW_Enable()
{
    int ret;

    ret = GSW_Enable(pedev0);

    return ret;
}

int pyGSW_HW_Init(GSW_HW_InitMode_t eInitMode)
{
    int ret;
    GSW_HW_Init_t  param;

    memset( &param, 0, sizeof(GSW_HW_Init_t));
    param.eInitMode = eInitMode;

    ret = GSW_HW_Init(pedev0, &param);

    return ret;
}

int pyGSW_MDIO_CfgGet()
{
    FILE *fp;
    int ret;
    GSW_MDIO_cfg_t  param;

    memset( &param, 0, sizeof(GSW_MDIO_cfg_t));

    ret = GSW_MDIO_CfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MDIO_CfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nMDIO_Speed", param.nMDIO_Speed, param.nMDIO_Speed);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMDIO_Enable", param.bMDIO_Enable, param.bMDIO_Enable);
    fclose(fp);

    return ret;
}

int pyGSW_MDIO_CfgSet(u32 nMDIO_Speed, ltq_bool_t bMDIO_Enable)
{
    int ret;
    GSW_MDIO_cfg_t  param;

    memset( &param, 0, sizeof(GSW_MDIO_cfg_t));
    param.nMDIO_Speed = nMDIO_Speed;
    param.bMDIO_Enable = bMDIO_Enable;

    ret = GSW_MDIO_CfgSet(pedev0, &param);

    return ret;
}

int pyGSW_MDIO_DataRead(u8 nAddressDev, u8 nAddressReg)
{
    FILE *fp;
    int ret;
    GSW_MDIO_data_t  param;

    memset( &param, 0, sizeof(GSW_MDIO_data_t));
    param.nAddressDev = nAddressDev;
    param.nAddressReg = nAddressReg;

    ret = GSW_MDIO_DataRead(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MDIO_DataRead");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nAddressDev", param.nAddressDev, param.nAddressDev);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nAddressReg", param.nAddressReg, param.nAddressReg);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nData", param.nData, param.nData);
    fclose(fp);

    return ret;
}

int pyGSW_MDIO_DataWrite(u8 nAddressDev, u8 nAddressReg, u16 nData)
{
    int ret;
    GSW_MDIO_data_t  param;

    memset( &param, 0, sizeof(GSW_MDIO_data_t));
    param.nAddressDev = nAddressDev;
    param.nAddressReg = nAddressReg;
    param.nData = nData;

    ret = GSW_MDIO_DataWrite(pedev0, &param);

    return ret;
}

int pyGSW_MonitorPortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_monitorPortCfg_t  param;

    memset( &param, 0, sizeof(GSW_monitorPortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_MonitorPortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_MonitorPortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMonitorPort", param.bMonitorPort, param.bMonitorPort);
    fclose(fp);

    return ret;
}

int pyGSW_MonitorPortCfgSet(u8 nPortId, ltq_bool_t bMonitorPort)
{
    int ret;
    GSW_monitorPortCfg_t  param;

    memset( &param, 0, sizeof(GSW_monitorPortCfg_t));
    param.nPortId = nPortId;
    param.bMonitorPort = bMonitorPort;

    ret = GSW_MonitorPortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_portCfg_t));
    param.nPortId = nPortId;

    ret = GSW_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eEnable", param.eEnable, param.eEnable);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bUnicastUnknownDrop", param.bUnicastUnknownDrop, param.bUnicastUnknownDrop);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMulticastUnknownDrop", param.bMulticastUnknownDrop, param.bMulticastUnknownDrop);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bReservedPacketDrop", param.bReservedPacketDrop, param.bReservedPacketDrop);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bBroadcastDrop", param.bBroadcastDrop, param.bBroadcastDrop);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bAging", param.bAging, param.bAging);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLearning", param.bLearning, param.bLearning);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLearningMAC_PortLock", param.bLearningMAC_PortLock, param.bLearningMAC_PortLock);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nLearningLimit", param.nLearningLimit, param.nLearningLimit);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bMAC_SpoofingDetection", param.bMAC_SpoofingDetection, param.bMAC_SpoofingDetection);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eFlowCtrl", param.eFlowCtrl, param.eFlowCtrl);
    fprintf(fp, "%s = 0x%x, %d\r\n", "ePortMonitor", param.ePortMonitor, param.ePortMonitor);
    fclose(fp);

    return ret;
}

int pyGSW_PortCfgSet(u8 nPortId, GSW_portEnable_t eEnable, ltq_bool_t bUnicastUnknownDrop, ltq_bool_t bMulticastUnknownDrop, \
          ltq_bool_t bReservedPacketDrop, ltq_bool_t bBroadcastDrop, ltq_bool_t bAging, ltq_bool_t bLearning, \
          ltq_bool_t bLearningMAC_PortLock, u16 nLearningLimit, ltq_bool_t bMAC_SpoofingDetection, \
          GSW_portFlow_t eFlowCtrl, GSW_portMonitor_t ePortMonitor)
{
    int ret;
    GSW_portCfg_t  param;

    memset( &param, 0, sizeof(GSW_portCfg_t));
    param.nPortId = nPortId;
    param.eEnable = eEnable;
    param.bUnicastUnknownDrop = bUnicastUnknownDrop;
    param.bMulticastUnknownDrop = bMulticastUnknownDrop;
    param.bReservedPacketDrop = bReservedPacketDrop;
    param.bBroadcastDrop = bBroadcastDrop;
    param.bAging = bAging;
    param.bLearning = bLearning;
    param.bLearningMAC_PortLock = bLearningMAC_PortLock;
    param.nLearningLimit = nLearningLimit;
    param.bMAC_SpoofingDetection = bMAC_SpoofingDetection;
    param.eFlowCtrl = eFlowCtrl;
    param.ePortMonitor = ePortMonitor;

    ret = GSW_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_PortLinkCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_portLinkCfg_t  param;

    memset( &param, 0, sizeof(GSW_portLinkCfg_t));
    param.nPortId = nPortId;

    ret = GSW_PortLinkCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_PortLinkCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bDuplexForce", param.bDuplexForce, param.bDuplexForce);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eDuplex", param.eDuplex, param.eDuplex);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bSpeedForce", param.bSpeedForce, param.bSpeedForce);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eSpeed", param.eSpeed, param.eSpeed);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLinkForce", param.bLinkForce, param.bLinkForce);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eLink", param.eLink, param.eLink);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eMII_Mode", param.eMII_Mode, param.eMII_Mode);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eMII_Type", param.eMII_Type, param.eMII_Type);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eClkMode", param.eClkMode, param.eClkMode);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bLPI", param.bLPI, param.bLPI);
    fclose(fp);

    return ret;
}

int pyGSW_PortLinkCfgSet(u8 nPortId, ltq_bool_t bDuplexForce, GSW_portDuplex_t eDuplex, ltq_bool_t bSpeedForce, \
          GSW_portSpeed_t eSpeed, ltq_bool_t bLinkForce, GSW_portLink_t eLink, GSW_MII_Mode_t eMII_Mode, \
          GSW_MII_Type_t eMII_Type, GSW_clkMode_t eClkMode, ltq_bool_t bLPI)
{
    int ret;
    GSW_portLinkCfg_t  param;

    memset( &param, 0, sizeof(GSW_portLinkCfg_t));
    param.nPortId = nPortId;
    param.bDuplexForce = bDuplexForce;
    param.eDuplex = eDuplex;
    param.bSpeedForce = bSpeedForce;
    param.eSpeed = eSpeed;
    param.bLinkForce = bLinkForce;
    param.eLink = eLink;
    param.eMII_Mode = eMII_Mode;
    param.eMII_Type = eMII_Type;
    param.eClkMode = eClkMode;
    param.bLPI = bLPI;

    ret = GSW_PortLinkCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_PortPHY_AddrGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_portPHY_Addr_t  param;

    memset( &param, 0, sizeof(GSW_portPHY_Addr_t));
    param.nPortId = nPortId;

    ret = GSW_PortPHY_AddrGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_PortPHY_AddrGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nAddressDev", param.nAddressDev, param.nAddressDev);
    fclose(fp);

    return ret;
}

int pyGSW_PortPHY_Query(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_portPHY_Query_t  param;

    memset( &param, 0, sizeof(GSW_portPHY_Query_t));
    param.nPortId = nPortId;

    ret = GSW_PortPHY_Query(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_PortPHY_Query");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bPHY_Present", param.bPHY_Present, param.bPHY_Present);
    fclose(fp);

    return ret;
}

int pyGSW_PortRGMII_ClkCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_portRGMII_ClkCfg_t  param;

    memset( &param, 0, sizeof(GSW_portRGMII_ClkCfg_t));
    param.nPortId = nPortId;

    ret = GSW_PortRGMII_ClkCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_PortRGMII_ClkCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nDelayRx", param.nDelayRx, param.nDelayRx);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nDelayTx", param.nDelayTx, param.nDelayTx);
    fclose(fp);

    return ret;
}

int pyGSW_PortRGMII_ClkCfgSet(u8 nPortId, u8 nDelayRx, u8 nDelayTx)
{
    int ret;
    GSW_portRGMII_ClkCfg_t  param;

    memset( &param, 0, sizeof(GSW_portRGMII_ClkCfg_t));
    param.nPortId = nPortId;
    param.nDelayRx = nDelayRx;
    param.nDelayTx = nDelayTx;

    ret = GSW_PortRGMII_ClkCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_PortRedirectGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_portRedirectCfg_t  param;

    memset( &param, 0, sizeof(GSW_portRedirectCfg_t));
    param.nPortId = nPortId;

    ret = GSW_PortRedirectGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_PortRedirectGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bRedirectEgress", param.bRedirectEgress, param.bRedirectEgress);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bRedirectIngress", param.bRedirectIngress, param.bRedirectIngress);
    fclose(fp);

    return ret;
}

int pyGSW_PortRedirectSet(u8 nPortId, ltq_bool_t bRedirectEgress, ltq_bool_t bRedirectIngress)
{
    int ret;
    GSW_portRedirectCfg_t  param;

    memset( &param, 0, sizeof(GSW_portRedirectCfg_t));
    param.nPortId = nPortId;
    param.bRedirectEgress = bRedirectEgress;
    param.bRedirectIngress = bRedirectIngress;

    ret = GSW_PortRedirectSet(pedev0, &param);

    return ret;
}

int pyGSW_RMON_Clear(GSW_RMON_type_t eRmonType, u8 nRmonId)
{
    int ret;
    GSW_RMON_clear_t  param;

    memset( &param, 0, sizeof(GSW_RMON_clear_t));
    param.eRmonType = eRmonType;
    param.nRmonId = nRmonId;

    ret = GSW_RMON_Clear(pedev0, &param);

    return ret;
}

int pyGSW_RMON_Port_Get(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_RMON_Port_cnt_t  param;

    memset( &param, 0, sizeof(GSW_RMON_Port_cnt_t));
    param.nPortId = nPortId;

    ret = GSW_RMON_Port_Get(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_RMON_Port_Get");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxGoodPkts", param.nRxGoodPkts, param.nRxGoodPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxUnicastPkts", param.nRxUnicastPkts, param.nRxUnicastPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxBroadcastPkts", param.nRxBroadcastPkts, param.nRxBroadcastPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxMulticastPkts", param.nRxMulticastPkts, param.nRxMulticastPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxFCSErrorPkts", param.nRxFCSErrorPkts, param.nRxFCSErrorPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxUnderSizeGoodPkts", param.nRxUnderSizeGoodPkts, param.nRxUnderSizeGoodPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxOversizeGoodPkts", param.nRxOversizeGoodPkts, param.nRxOversizeGoodPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxUnderSizeErrorPkts", param.nRxUnderSizeErrorPkts, param.nRxUnderSizeErrorPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxGoodPausePkts", param.nRxGoodPausePkts, param.nRxGoodPausePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxOversizeErrorPkts", param.nRxOversizeErrorPkts, param.nRxOversizeErrorPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxAlignErrorPkts", param.nRxAlignErrorPkts, param.nRxAlignErrorPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxFilteredPkts", param.nRxFilteredPkts, param.nRxFilteredPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRx64BytePkts", param.nRx64BytePkts, param.nRx64BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRx127BytePkts", param.nRx127BytePkts, param.nRx127BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRx255BytePkts", param.nRx255BytePkts, param.nRx255BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRx511BytePkts", param.nRx511BytePkts, param.nRx511BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRx1023BytePkts", param.nRx1023BytePkts, param.nRx1023BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxMaxBytePkts", param.nRxMaxBytePkts, param.nRxMaxBytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxGoodPkts", param.nTxGoodPkts, param.nTxGoodPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxUnicastPkts", param.nTxUnicastPkts, param.nTxUnicastPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxBroadcastPkts", param.nTxBroadcastPkts, param.nTxBroadcastPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxMulticastPkts", param.nTxMulticastPkts, param.nTxMulticastPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxSingleCollCount", param.nTxSingleCollCount, param.nTxSingleCollCount);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxMultCollCount", param.nTxMultCollCount, param.nTxMultCollCount);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxLateCollCount", param.nTxLateCollCount, param.nTxLateCollCount);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxExcessCollCount", param.nTxExcessCollCount, param.nTxExcessCollCount);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxCollCount", param.nTxCollCount, param.nTxCollCount);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxPauseCount", param.nTxPauseCount, param.nTxPauseCount);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTx64BytePkts", param.nTx64BytePkts, param.nTx64BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTx127BytePkts", param.nTx127BytePkts, param.nTx127BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTx255BytePkts", param.nTx255BytePkts, param.nTx255BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTx511BytePkts", param.nTx511BytePkts, param.nTx511BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTx1023BytePkts", param.nTx1023BytePkts, param.nTx1023BytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxMaxBytePkts", param.nTxMaxBytePkts, param.nTxMaxBytePkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxDroppedPkts", param.nTxDroppedPkts, param.nTxDroppedPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxAcmDroppedPkts", param.nTxAcmDroppedPkts, param.nTxAcmDroppedPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxDroppedPkts", param.nRxDroppedPkts, param.nRxDroppedPkts);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxGoodBytes", param.nRxGoodBytes, param.nRxGoodBytes);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRxBadBytes", param.nRxBadBytes, param.nRxBadBytes);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nTxGoodBytes", param.nTxGoodBytes, param.nTxGoodBytes);
    fclose(fp);

    return ret;
}

int pyGSW_VersionGet(u16 nId)
{
    FILE *fp;
    int ret;
    GSW_version_t  param;

    memset( &param, 0, sizeof(GSW_version_t));
    param.nId = nId;

    ret = GSW_VersionGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_VersionGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nId", param.nId, param.nId);
    fprintf(fp, "%s = [", "cName[64]");
    fprintf(fp, " 0x%02x", param.cName[0]);
    fprintf(fp, " 0x%02x", param.cName[1]);
    fprintf(fp, " 0x%02x", param.cName[2]);
    fprintf(fp, " 0x%02x", param.cName[3]);
    fprintf(fp, " 0x%02x", param.cName[4]);
    fprintf(fp, " 0x%02x", param.cName[5]);
    fprintf(fp, " 0x%02x", param.cName[6]);
    fprintf(fp, " 0x%02x", param.cName[7]);
    fprintf(fp, " 0x%02x", param.cName[8]);
    fprintf(fp, " 0x%02x", param.cName[9]);
    fprintf(fp, " 0x%02x", param.cName[10]);
    fprintf(fp, " 0x%02x", param.cName[11]);
    fprintf(fp, " 0x%02x", param.cName[12]);
    fprintf(fp, " 0x%02x", param.cName[13]);
    fprintf(fp, " 0x%02x", param.cName[14]);
    fprintf(fp, " 0x%02x", param.cName[15]);
    fprintf(fp, " 0x%02x", param.cName[16]);
    fprintf(fp, " 0x%02x", param.cName[17]);
    fprintf(fp, " 0x%02x", param.cName[18]);
    fprintf(fp, " 0x%02x", param.cName[19]);
    fprintf(fp, " 0x%02x", param.cName[20]);
    fprintf(fp, " 0x%02x", param.cName[21]);
    fprintf(fp, " 0x%02x", param.cName[22]);
    fprintf(fp, " 0x%02x", param.cName[23]);
    fprintf(fp, " 0x%02x", param.cName[24]);
    fprintf(fp, " 0x%02x", param.cName[25]);
    fprintf(fp, " 0x%02x", param.cName[26]);
    fprintf(fp, " 0x%02x", param.cName[27]);
    fprintf(fp, " 0x%02x", param.cName[28]);
    fprintf(fp, " 0x%02x", param.cName[29]);
    fprintf(fp, " 0x%02x", param.cName[30]);
    fprintf(fp, " 0x%02x", param.cName[31]);
    fprintf(fp, " 0x%02x", param.cName[32]);
    fprintf(fp, " 0x%02x", param.cName[33]);
    fprintf(fp, " 0x%02x", param.cName[34]);
    fprintf(fp, " 0x%02x", param.cName[35]);
    fprintf(fp, " 0x%02x", param.cName[36]);
    fprintf(fp, " 0x%02x", param.cName[37]);
    fprintf(fp, " 0x%02x", param.cName[38]);
    fprintf(fp, " 0x%02x", param.cName[39]);
    fprintf(fp, " 0x%02x", param.cName[40]);
    fprintf(fp, " 0x%02x", param.cName[41]);
    fprintf(fp, " 0x%02x", param.cName[42]);
    fprintf(fp, " 0x%02x", param.cName[43]);
    fprintf(fp, " 0x%02x", param.cName[44]);
    fprintf(fp, " 0x%02x", param.cName[45]);
    fprintf(fp, " 0x%02x", param.cName[46]);
    fprintf(fp, " 0x%02x", param.cName[47]);
    fprintf(fp, " 0x%02x", param.cName[48]);
    fprintf(fp, " 0x%02x", param.cName[49]);
    fprintf(fp, " 0x%02x", param.cName[50]);
    fprintf(fp, " 0x%02x", param.cName[51]);
    fprintf(fp, " 0x%02x", param.cName[52]);
    fprintf(fp, " 0x%02x", param.cName[53]);
    fprintf(fp, " 0x%02x", param.cName[54]);
    fprintf(fp, " 0x%02x", param.cName[55]);
    fprintf(fp, " 0x%02x", param.cName[56]);
    fprintf(fp, " 0x%02x", param.cName[57]);
    fprintf(fp, " 0x%02x", param.cName[58]);
    fprintf(fp, " 0x%02x", param.cName[59]);
    fprintf(fp, " 0x%02x", param.cName[60]);
    fprintf(fp, " 0x%02x", param.cName[61]);
    fprintf(fp, " 0x%02x", param.cName[62]);
    fprintf(fp, " 0x%02x", param.cName[63]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "cVersion[64]");
    fprintf(fp, " 0x%02x", param.cVersion[0]);
    fprintf(fp, " 0x%02x", param.cVersion[1]);
    fprintf(fp, " 0x%02x", param.cVersion[2]);
    fprintf(fp, " 0x%02x", param.cVersion[3]);
    fprintf(fp, " 0x%02x", param.cVersion[4]);
    fprintf(fp, " 0x%02x", param.cVersion[5]);
    fprintf(fp, " 0x%02x", param.cVersion[6]);
    fprintf(fp, " 0x%02x", param.cVersion[7]);
    fprintf(fp, " 0x%02x", param.cVersion[8]);
    fprintf(fp, " 0x%02x", param.cVersion[9]);
    fprintf(fp, " 0x%02x", param.cVersion[10]);
    fprintf(fp, " 0x%02x", param.cVersion[11]);
    fprintf(fp, " 0x%02x", param.cVersion[12]);
    fprintf(fp, " 0x%02x", param.cVersion[13]);
    fprintf(fp, " 0x%02x", param.cVersion[14]);
    fprintf(fp, " 0x%02x", param.cVersion[15]);
    fprintf(fp, " 0x%02x", param.cVersion[16]);
    fprintf(fp, " 0x%02x", param.cVersion[17]);
    fprintf(fp, " 0x%02x", param.cVersion[18]);
    fprintf(fp, " 0x%02x", param.cVersion[19]);
    fprintf(fp, " 0x%02x", param.cVersion[20]);
    fprintf(fp, " 0x%02x", param.cVersion[21]);
    fprintf(fp, " 0x%02x", param.cVersion[22]);
    fprintf(fp, " 0x%02x", param.cVersion[23]);
    fprintf(fp, " 0x%02x", param.cVersion[24]);
    fprintf(fp, " 0x%02x", param.cVersion[25]);
    fprintf(fp, " 0x%02x", param.cVersion[26]);
    fprintf(fp, " 0x%02x", param.cVersion[27]);
    fprintf(fp, " 0x%02x", param.cVersion[28]);
    fprintf(fp, " 0x%02x", param.cVersion[29]);
    fprintf(fp, " 0x%02x", param.cVersion[30]);
    fprintf(fp, " 0x%02x", param.cVersion[31]);
    fprintf(fp, " 0x%02x", param.cVersion[32]);
    fprintf(fp, " 0x%02x", param.cVersion[33]);
    fprintf(fp, " 0x%02x", param.cVersion[34]);
    fprintf(fp, " 0x%02x", param.cVersion[35]);
    fprintf(fp, " 0x%02x", param.cVersion[36]);
    fprintf(fp, " 0x%02x", param.cVersion[37]);
    fprintf(fp, " 0x%02x", param.cVersion[38]);
    fprintf(fp, " 0x%02x", param.cVersion[39]);
    fprintf(fp, " 0x%02x", param.cVersion[40]);
    fprintf(fp, " 0x%02x", param.cVersion[41]);
    fprintf(fp, " 0x%02x", param.cVersion[42]);
    fprintf(fp, " 0x%02x", param.cVersion[43]);
    fprintf(fp, " 0x%02x", param.cVersion[44]);
    fprintf(fp, " 0x%02x", param.cVersion[45]);
    fprintf(fp, " 0x%02x", param.cVersion[46]);
    fprintf(fp, " 0x%02x", param.cVersion[47]);
    fprintf(fp, " 0x%02x", param.cVersion[48]);
    fprintf(fp, " 0x%02x", param.cVersion[49]);
    fprintf(fp, " 0x%02x", param.cVersion[50]);
    fprintf(fp, " 0x%02x", param.cVersion[51]);
    fprintf(fp, " 0x%02x", param.cVersion[52]);
    fprintf(fp, " 0x%02x", param.cVersion[53]);
    fprintf(fp, " 0x%02x", param.cVersion[54]);
    fprintf(fp, " 0x%02x", param.cVersion[55]);
    fprintf(fp, " 0x%02x", param.cVersion[56]);
    fprintf(fp, " 0x%02x", param.cVersion[57]);
    fprintf(fp, " 0x%02x", param.cVersion[58]);
    fprintf(fp, " 0x%02x", param.cVersion[59]);
    fprintf(fp, " 0x%02x", param.cVersion[60]);
    fprintf(fp, " 0x%02x", param.cVersion[61]);
    fprintf(fp, " 0x%02x", param.cVersion[62]);
    fprintf(fp, " 0x%02x", param.cVersion[63]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_WoL_CfgGet()
{
    FILE *fp;
    int ret;
    GSW_WoL_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_WoL_Cfg_t));

    ret = GSW_WoL_CfgGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_WoL_CfgGet");
    fprintf(fp, "%s = [", "nWolMAC[6]");
    fprintf(fp, " 0x%02x", param.nWolMAC[0]);
    fprintf(fp, " 0x%02x", param.nWolMAC[1]);
    fprintf(fp, " 0x%02x", param.nWolMAC[2]);
    fprintf(fp, " 0x%02x", param.nWolMAC[3]);
    fprintf(fp, " 0x%02x", param.nWolMAC[4]);
    fprintf(fp, " 0x%02x", param.nWolMAC[5]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = [", "nWolPassword[6]");
    fprintf(fp, " 0x%02x", param.nWolPassword[0]);
    fprintf(fp, " 0x%02x", param.nWolPassword[1]);
    fprintf(fp, " 0x%02x", param.nWolPassword[2]);
    fprintf(fp, " 0x%02x", param.nWolPassword[3]);
    fprintf(fp, " 0x%02x", param.nWolPassword[4]);
    fprintf(fp, " 0x%02x", param.nWolPassword[5]);
    fprintf(fp, "]\r\n");
    fprintf(fp, "%s = 0x%x, %d\r\n", "bWolPasswordEnable", param.bWolPasswordEnable, param.bWolPasswordEnable);
    fclose(fp);

    return ret;
}

int pyGSW_WoL_CfgSet(u8 nWolMAC0, u8 nWolMAC1, u8 nWolMAC2, u8 nWolMAC3, u8 nWolMAC4, u8 nWolMAC5, u8 nWolPassword0, \
          u8 nWolPassword1, u8 nWolPassword2, u8 nWolPassword3, u8 nWolPassword4, u8 nWolPassword5, \
          ltq_bool_t bWolPasswordEnable)
{
    int ret;
    GSW_WoL_Cfg_t  param;

    memset( &param, 0, sizeof(GSW_WoL_Cfg_t));
    param.nWolMAC[0] = nWolMAC0;
    param.nWolMAC[1] = nWolMAC1;
    param.nWolMAC[2] = nWolMAC2;
    param.nWolMAC[3] = nWolMAC3;
    param.nWolMAC[4] = nWolMAC4;
    param.nWolMAC[5] = nWolMAC5;
    param.nWolPassword[0] = nWolPassword0;
    param.nWolPassword[1] = nWolPassword1;
    param.nWolPassword[2] = nWolPassword2;
    param.nWolPassword[3] = nWolPassword3;
    param.nWolPassword[4] = nWolPassword4;
    param.nWolPassword[5] = nWolPassword5;
    param.bWolPasswordEnable = bWolPasswordEnable;

    ret = GSW_WoL_CfgSet(pedev0, &param);

    return ret;
}

int pyGSW_WoL_PortCfgGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_WoL_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_WoL_PortCfg_t));
    param.nPortId = nPortId;

    ret = GSW_WoL_PortCfgGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_WoL_PortCfgGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "bWakeOnLAN_Enable", param.bWakeOnLAN_Enable, param.bWakeOnLAN_Enable);
    fclose(fp);

    return ret;
}

int pyGSW_WoL_PortCfgSet(u8 nPortId, ltq_bool_t bWakeOnLAN_Enable)
{
    int ret;
    GSW_WoL_PortCfg_t  param;

    memset( &param, 0, sizeof(GSW_WoL_PortCfg_t));
    param.nPortId = nPortId;
    param.bWakeOnLAN_Enable = bWakeOnLAN_Enable;

    ret = GSW_WoL_PortCfgSet(pedev0, &param);

    return ret;
}

int pyGSW_RegisterGet(u16 nRegAddr)
{
    FILE *fp;
    int ret;
    GSW_register_t  param;

    memset( &param, 0, sizeof(GSW_register_t));
    param.nRegAddr = nRegAddr;

    ret = GSW_RegisterGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_RegisterGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nRegAddr", param.nRegAddr, param.nRegAddr);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nData", param.nData, param.nData);
    fclose(fp);

    return ret;
}

int pyGSW_RegisterSet(u16 nRegAddr, u16 nData)
{
    int ret;
    GSW_register_t  param;

    memset( &param, 0, sizeof(GSW_register_t));
    param.nRegAddr = nRegAddr;
    param.nData = nData;

    ret = GSW_RegisterSet(pedev0, &param);

    return ret;
}

int pyGSW_IrqMaskGet(u32 nPortId)
{
    FILE *fp;
    int ret;
    GSW_irq_t  param;

    memset( &param, 0, sizeof(GSW_irq_t));
    param.nPortId = nPortId;

    ret = GSW_IrqMaskGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_IrqMaskGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "eIrqSrc", param.eIrqSrc, param.eIrqSrc);
    fclose(fp);

    return ret;
}

int pyGSW_IrqMaskSet(u32 nPortId, GSW_irqSrc_t eIrqSrc)
{
    int ret;
    GSW_irq_t  param;

    memset( &param, 0, sizeof(GSW_irq_t));
    param.nPortId = nPortId;
    param.eIrqSrc = eIrqSrc;

    ret = GSW_IrqMaskSet(pedev0, &param);

    return ret;
}

int pyGSW_PceRuleDelete(u32 nIndex)
{
    int ret;
    GSW_PCE_ruleDelete_t  param;

    memset( &param, 0, sizeof(GSW_PCE_ruleDelete_t));
    param.nIndex = nIndex;

    ret = GSW_PceRuleDelete(pedev0, &param);

    return ret;
}

int pyGSW_RMON_ExtendGet(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_RMON_extendGet_t  param;

    memset( &param, 0, sizeof(GSW_RMON_extendGet_t));
    param.nPortId = nPortId;

    ret = GSW_RMON_ExtendGet(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_RMON_ExtendGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = [", "nTrafficFlowCnt[24]");
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[0]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[1]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[2]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[3]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[4]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[5]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[6]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[7]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[8]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[9]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[10]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[11]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[12]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[13]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[14]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[15]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[16]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[17]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[18]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[19]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[20]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[21]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[22]);
    fprintf(fp, " 0x%02x", param.nTrafficFlowCnt[23]);
    fprintf(fp, "]\r\n");
    fclose(fp);

    return ret;
}

int pyGSW_Reset(GSW_resetMode_t eReset)
{
    int ret;
    GSW_reset_t  param;

    memset( &param, 0, sizeof(GSW_reset_t));
    param.eReset = eReset;

    ret = GSW_Reset(pedev0, &param);

    return ret;
}

int pyGSW_TimestampPortRead(u8 nPortId)
{
    FILE *fp;
    int ret;
    GSW_TIMESTAMP_PortRead_t  param;

    memset( &param, 0, sizeof(GSW_TIMESTAMP_PortRead_t));
    param.nPortId = nPortId;

    ret = GSW_TimestampPortRead(pedev0, &param);

    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_TimestampPortRead");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nPortId", param.nPortId, param.nPortId);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nIngressSec", param.nIngressSec, param.nIngressSec);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nIngressNanoSec", param.nIngressNanoSec, param.nIngressNanoSec);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nEgressSec", param.nEgressSec, param.nEgressSec);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nEgressNanoSec", param.nEgressNanoSec, param.nEgressNanoSec);
    fclose(fp);

    return ret;
}

int pyGSW_TimestampTimerGet()
{
    FILE *fp;
    int ret;
    GSW_TIMESTAMP_Timer_t  param;

    memset( &param, 0, sizeof(GSW_TIMESTAMP_Timer_t));

    ret = GSW_TimestampTimerGet(pedev0, &param);
    fp = fopen (fn, "w+");
    fprintf(fp, "%s\r\n", "GSW_TimestampTimerGet");
    fprintf(fp, "%s = 0x%x, %d\r\n", "nSec", param.nSec, param.nSec);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nNanoSec", param.nNanoSec, param.nNanoSec);
    fprintf(fp, "%s = 0x%x, %d\r\n", "nFractionalNanoSec", param.nFractionalNanoSec, param.nFractionalNanoSec);
    fclose(fp);

    return ret;
}

int pyGSW_TimestampTimerSet(u32 nSec, u32 nNanoSec, u32 nFractionalNanoSec)
{
    int ret;
    GSW_TIMESTAMP_Timer_t  param;

    memset( &param, 0, sizeof(GSW_TIMESTAMP_Timer_t));
    param.nSec = nSec;
    param.nNanoSec = nNanoSec;
    param.nFractionalNanoSec = nFractionalNanoSec;

    ret = GSW_TimestampTimerSet(pedev0, &param);

    return ret;
}

