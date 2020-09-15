#to add python kernel 2.7 in jupyter notebook: 
#python -m pip install ipykernel
#python2 -m ipykernel install --user

import ser02 as s
s.list_ports()
pn = input("Please input the port name (e.g. COMx): ")
s.open_port(pn)


import PySwitchCli as sw
import Switch_struct_enum as swse
sw.init()
v = s.r(0xfa10)
print ("r(0xfa10) = 0x%04x"%v)
v = s.r(0xfa11)
print ("r(0xfa11) = 0x%04x"%v)
#Disable the default asking of HW_Init(), there is dedicated API for it.
#a = raw_input("Should we do HW_Init()? :  y/n [n]")
#if a == "y" or a == "Y" or a == "yes" or a == "Yes" or a == "YES":
#	sw.pyGSW_HW_Init()

def en_uart():
	v1 = sw.r(0xf383)
	print ("r(0xf383) = ",'%04x'%v1)
	v2 = sw.r(0xf384)
	print ("r(0xf384) = ",'%04x'%v2)

	v1 = v1 | 0x3;
	v2 = v2 | 0x3;
	print ("w(0xf383) = ",'%04x'%v1)
	print ("w(0xf384) = ",'%04x'%v2)
	sw.w(0xf383, v1)
	sw.w(0xf384, v2)

en_uart()
fn = "tttttttt.txt"

def rc():
	print (s.close_port())
	s.open_port(pn)
	en_uart();

#### Basic function manually implemented
def pc_uart_dataread(Offset, value):
    return sw.pc_uart_dataread(Offset, value)

def pc_uart_datawrite(Offset, value):
    return sw.pc_uart_datawrite(Offset, value)

def init():
    return sw.init()

def r(addr):
    return sw.r(addr)

def w(addr, value):
    return sw.w(addr, value)

def mdiow(phyid, addr, value):
    return sw.mdiow(phyid, addr, value)

def mdior(phyid, addr):
    return sw.mdior(phyid, addr)

#### manually PCE process
'''
def pce_pinit(idx, enb):
    return sw.pce_pinit(idx, enb)

def pce_portId(enb, p):
    return sw.pce_portId(enb, p)

def pce_act_forwarding(act, portmap):
    return sw.pce_act_forwarding(act, portmap)

def pyGSW_PceRuleRead():
    return sw.pyGSW_PceRuleRead()

def pyGSW_PceRuleWrite():
    return sw.pyGSW_PceRuleWrite()

def pyGSW_PceRuleReadf(idx, enb):
    ret = sw.pyGSW_PceRuleReadf(idx, enb)
    with open(fn) as f:
    	print (f.read())
'''

nRet = { 0: 'GSW_statusOk', -1: 'GSW_statusErr', -2: 'GSW_statusParam', -3: 'GSW_statusVLAN_Space', -4: 'GSW_statusVLAN_ID', -5: 'GSW_statusInvalIoctl',\
        -6: 'GSW_statusNoSupport', -7: 'GSW_statusTimeout', -8: 'GSW_statusValueRange', -9: 'GSW_statusPortInvalid', -10: 'GSW_statusIRQ_Invalid', \
        -11: 'GSW_statusMAC_TableFull', -12: 'GSW_statusLock_Failed', -13: 'GSW_statusMemErr', -14: 'GSW_statusBusErr', -15: 'GSW_statusTblFull'}

#========== PCE read / write process ===============================================
#    manually and automatically codes
#========== PCE read / write process ===============================================

def clear_pce_data():
	p = dict()
	a = dict()
	p["nIndex"] = 0
	p["bEnable"] = 0
	p["bPortIdEnable"] = 0
	p["nPortId"] = 0
	p["bDSCP_Enable"] = 0
	p["nDSCP"] = 0
	p["bPCP_Enable"] = 0
	p["nPCP"] = 0
	p["bSTAG_PCP_DEI_Enable"] = 0
	p["nSTAG_PCP_DEI"] = 0
	p["bPktLngEnable"] = 0
	p["nPktLng"] = 0
	p["nPktLngRange"] = 0
	p["bMAC_DstEnable"] = 0
	p["nMAC_Dst0"] = 0
	p["nMAC_Dst1"] = 0
	p["nMAC_Dst2"] = 0
	p["nMAC_Dst3"] = 0
	p["nMAC_Dst4"] = 0
	p["nMAC_Dst5"] = 0
	p["nMAC_DstMask"] = 0
	p["bMAC_SrcEnable"] = 0
	p["nMAC_Src0"] = 0
	p["nMAC_Src1"] = 0
	p["nMAC_Src2"] = 0
	p["nMAC_Src3"] = 0
	p["nMAC_Src4"] = 0
	p["nMAC_Src5"] = 0
	p["nMAC_SrcMask"] = 0
	p["bAppDataMSB_Enable"] = 0
	p["nAppDataMSB"] = 0
	p["bAppMaskRangeMSB_Select"] = 0
	p["nAppMaskRangeMSB"] = 0
	p["bAppDataLSB_Enable"] = 0
	p["nAppDataLSB"] = 0
	p["bAppMaskRangeLSB_Select"] = 0
	p["nAppMaskRangeLSB"] = 0
	p["eDstIP_Select"] = 0
	p["nDstIPipv4"] = 0
	p["nDstIPipv60"] = 0
	p["nDstIPipv61"] = 0
	p["nDstIPipv62"] = 0
	p["nDstIPipv63"] = 0
	p["nDstIPipv64"] = 0
	p["nDstIPipv65"] = 0
	p["nDstIPipv66"] = 0
	p["nDstIPipv67"] = 0
	p["nDstIP_Mask"] = 0
	p["eSrcIP_Select"] = 0
	p["nSrcIPipv4"] = 0
	p["nSrcIPipv60"] = 0
	p["nSrcIPipv61"] = 0
	p["nSrcIPipv62"] = 0
	p["nSrcIPipv63"] = 0
	p["nSrcIPipv64"] = 0
	p["nSrcIPipv65"] = 0
	p["nSrcIPipv66"] = 0
	p["nSrcIPipv67"] = 0
	p["nSrcIP_Mask"] = 0
	p["bEtherTypeEnable"] = 0
	p["nEtherType"] = 0
	p["nEtherTypeMask"] = 0
	p["bProtocolEnable"] = 0
	p["nProtocol"] = 0
	p["nProtocolMask"] = 0
	p["bSessionIdEnable"] = 0
	p["nSessionId"] = 0
	p["bVid"] = 0
	p["nVid"] = 0
	p["bVidRange_Select"] = 0
	p["nVidRange"] = 0
	p["bSLAN_Vid"] = 0
	p["nSLAN_Vid"] = 0
	a["eTrafficClassAction"] = 0
	a["nTrafficClassAlternate"] = 0
	a["eSnoopingTypeAction"] = 0
	a["eLearningAction"] = 0
	a["eIrqAction"] = 0
	a["eCrossStateAction"] = 0
	a["eCritFrameAction"] = 0
	a["eTimestampAction"] = 0
	a["ePortMapAction"] = 0
	a["nForwardPortMap"] = 0
	a["bRemarkAction"] = 0
	a["bRemarkPCP"] = 0
	a["bRemarkSTAG_PCP"] = 0
	a["bRemarkSTAG_DEI"] = 0
	a["bRemarkDSCP"] = 0
	a["bRemarkClass"] = 0
	a["eMeterAction"] = 0
	a["nMeterId"] = 0
	a["bRMON_Action"] = 0
	a["nRMON_Id"] = 0
	a["eVLAN_Action"] = 0
	a["nVLAN_Id"] = 0
	a["nFId"] = 0
	a["eSVLAN_Action"] = 0
	a["nSVLAN_Id"] = 0
	a["eVLAN_CrossAction"] = 0
	a["bCVLAN_Ignore_Control"] = 0
	a["bPortBitMapMuxControl"] = 0
	a["bPortTrunkAction"] = 0
	a["bPortLinkSelection"] = 0
	a["bFlowID_Action"] = 0
	a["nFlowID"] = 0
	return [p, a]

def pyGSW_PceRuleWrite(p, a):
	ret = dict()
	ret["ret"] =  sw.pyGSW_PceRuleWrite(p["nIndex"], p["bEnable"], p["bPortIdEnable"], p["nPortId"], p["bDSCP_Enable"], p["nDSCP"], p["bPCP_Enable"], p["nPCP"], p["bSTAG_PCP_DEI_Enable"], p["nSTAG_PCP_DEI"], p["bPktLngEnable"], p["nPktLng"], p["nPktLngRange"], p["bMAC_DstEnable"], p["nMAC_Dst0"], p["nMAC_Dst1"], p["nMAC_Dst2"], p["nMAC_Dst3"], p["nMAC_Dst4"], p["nMAC_Dst5"], p["nMAC_DstMask"], p["bMAC_SrcEnable"], p["nMAC_Src0"], p["nMAC_Src1"], p["nMAC_Src2"], p["nMAC_Src3"], p["nMAC_Src4"], p["nMAC_Src5"], p["nMAC_SrcMask"], p["bAppDataMSB_Enable"], p["nAppDataMSB"], p["bAppMaskRangeMSB_Select"], p["nAppMaskRangeMSB"], p["bAppDataLSB_Enable"], p["nAppDataLSB"], p["bAppMaskRangeLSB_Select"], p["nAppMaskRangeLSB"], p["eDstIP_Select"], p["nDstIPipv4"], p["nDstIPipv60"], p["nDstIPipv61"], p["nDstIPipv62"], p["nDstIPipv63"], p["nDstIPipv64"], p["nDstIPipv65"], p["nDstIPipv66"], p["nDstIPipv67"], p["nDstIP_Mask"], p["eSrcIP_Select"], p["nSrcIPipv4"], p["nSrcIPipv60"], p["nSrcIPipv61"], p["nSrcIPipv62"], p["nSrcIPipv63"], p["nSrcIPipv64"], p["nSrcIPipv65"], p["nSrcIPipv66"], p["nSrcIPipv67"], p["nSrcIP_Mask"], p["bEtherTypeEnable"], p["nEtherType"], p["nEtherTypeMask"], p["bProtocolEnable"], p["nProtocol"], p["nProtocolMask"], p["bSessionIdEnable"], p["nSessionId"], p["bVid"], p["nVid"], p["bVidRange_Select"], p["nVidRange"], p["bSLAN_Vid"], p["nSLAN_Vid"], a["eTrafficClassAction"], a["nTrafficClassAlternate"], a["eSnoopingTypeAction"], a["eLearningAction"], a["eIrqAction"], a["eCrossStateAction"], a["eCritFrameAction"], a["eTimestampAction"], a["ePortMapAction"], a["nForwardPortMap"], a["bRemarkAction"], a["bRemarkPCP"], a["bRemarkSTAG_PCP"], a["bRemarkSTAG_DEI"], a["bRemarkDSCP"], a["bRemarkClass"], a["eMeterAction"], a["nMeterId"], a["bRMON_Action"], a["nRMON_Id"], a["eVLAN_Action"], a["nVLAN_Id"], a["nFId"], a["eSVLAN_Action"], a["nSVLAN_Id"], a["eVLAN_CrossAction"], a["bCVLAN_Ignore_Control"], a["bPortBitMapMuxControl"], a["bPortTrunkAction"], a["bPortLinkSelection"], a["bFlowID_Action"], a["nFlowID"])
	return ret

def pyGSW_PceRuleRead(idx = 0):
	ret = dict()
	ret["ret"] = sw.pyGSW_PceRuleRead(idx)
	fo = open(fn, "r")
	print (fo.read())
	return ret

#========== Auto Adap PySwitchCli.py functions ===============================================
#    Auto generated code from abc.ipynb "Generate Switch.py"
#========== Auto Adap PySwitchCli.py functions ===============================================

def pyGSW_8021X_EAPOL_RuleGet(nForwardPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_8021X_EAPOL_RuleGet(nForwardPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_8021X_EAPOL_RuleSet(eForwardPort = 0, nForwardPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_8021X_EAPOL_RuleSet(eForwardPort, nForwardPortId)
	return ret

def pyGSW_8021X_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_8021X_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_8021X_PortCfgSet(nPortId = 0, eState = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_8021X_PortCfgSet(nPortId, eState)
	return ret

def pyGSW_MAC_TableClear(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MAC_TableClear()
	return ret

def pyGSW_MAC_TableEntryAdd(nFId = 0, nPortId = 0, nAgeTimer = 0, nSVLAN_Id = 0, bStaticEntry = 0, nTrafficClass = 0, \
          nMAC = [0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MAC_TableEntryAdd(nFId, nPortId, nAgeTimer, nSVLAN_Id, bStaticEntry, nTrafficClass, \
          nMAC[0], nMAC[1], nMAC[2], nMAC[3], nMAC[4], nMAC[5])
	return ret

def pyGSW_MAC_TableEntryQuery(nMAC = [0, 0, 0, 0, 0, 0], nFId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MAC_TableEntryQuery(nMAC[0], nMAC[1], nMAC[2], nMAC[3], nMAC[4], nMAC[5], nFId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MAC_TableEntryRead(bInitial = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MAC_TableEntryRead(bInitial)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MAC_TableEntryRemove(nFId = 0, nMAC = [0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MAC_TableEntryRemove(nFId, nMAC[0], nMAC[1], nMAC[2], nMAC[3], nMAC[4], nMAC[5])
	return ret

def pyGSW_STP_BPDU_RuleGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_STP_BPDU_RuleGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_STP_BPDU_RuleSet(eForwardPort = 0, nForwardPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_STP_BPDU_RuleSet(eForwardPort, nForwardPortId)
	return ret

def pyGSW_STP_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_STP_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_STP_PortCfgSet(nPortId = 0, nFId = 0, ePortState = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_STP_PortCfgSet(nPortId, nFId, ePortState)
	return ret

def pyGSW_TrunkingCfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TrunkingCfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_TrunkingCfgSet(bIP_Src = 0, bIP_Dst = 0, bMAC_Src = 0, bMAC_Dst = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TrunkingCfgSet(bIP_Src, bIP_Dst, bMAC_Src, bMAC_Dst)
	return ret

def pyGSW_TrunkingPortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TrunkingPortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_TrunkingPortCfgSet(bAggregateEnable = 0, nPortId = 0, nAggrPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TrunkingPortCfgSet(bAggregateEnable, nPortId, nAggrPortId)
	return ret

def pyGSW_SVLAN_CfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_SVLAN_CfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_SVLAN_CfgSet(nEthertype = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_SVLAN_CfgSet(nEthertype)
	return ret

def pyGSW_SVLAN_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_SVLAN_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_SVLAN_PortCfgSet(nPortId = 0, bSVLAN_TagSupport = 0, bSVLAN_MACbasedTag = 0, nPortVId = 0, \
          bVLAN_ReAssign = 0, eVLAN_MemberViolation = 0, eAdmitMode = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_SVLAN_PortCfgSet(nPortId, bSVLAN_TagSupport, bSVLAN_MACbasedTag, nPortVId, bVLAN_ReAssign, \
          eVLAN_MemberViolation, eAdmitMode)
	return ret

def pyGSW_VLAN_Member_Init(nPortMemberMap = 0, nEgressTagMap = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_Member_Init(nPortMemberMap, nEgressTagMap)
	return ret

def pyGSW_VLAN_IdCreate(nVId = 0, nFId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_IdCreate(nVId, nFId)
	return ret

def pyGSW_VLAN_IdDelete(nVId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_IdDelete(nVId)
	return ret

def pyGSW_VLAN_IdGet(nVId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_IdGet(nVId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_VLAN_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_VLAN_PortCfgSet(nPortId = 0, nPortVId = 0, bVLAN_UnknownDrop = 0, bVLAN_ReAssign = 0, eVLAN_MemberViolation = 0, \
          eAdmitMode = 0, bTVM = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_PortCfgSet(nPortId, nPortVId, bVLAN_UnknownDrop, bVLAN_ReAssign, eVLAN_MemberViolation, \
          eAdmitMode, bTVM)
	return ret

def pyGSW_VLAN_PortMemberAdd(nVId = 0, nPortId = 0, bVLAN_TagEgress = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_PortMemberAdd(nVId, nPortId, bVLAN_TagEgress)
	return ret

def pyGSW_VLAN_PortMemberRead(bInitial = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_PortMemberRead(bInitial)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_VLAN_PortMemberRemove(nVId = 0, nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_PortMemberRemove(nVId, nPortId)
	return ret

def pyGSW_VLAN_ReservedAdd(nVId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_ReservedAdd(nVId)
	return ret

def pyGSW_VLAN_ReservedRemove(nVId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VLAN_ReservedRemove(nVId)
	return ret

def pyGSW_QoS_ClassDSCP_Get(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ClassDSCP_Get()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_ClassDSCP_Set(nTrafficClass = 0, nDSCP = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
          0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ClassDSCP_Set(nTrafficClass, nDSCP[0], nDSCP[1], nDSCP[2], nDSCP[3], nDSCP[4], \
          nDSCP[5], nDSCP[6], nDSCP[7], nDSCP[8], nDSCP[9], nDSCP[10], \
          nDSCP[11], nDSCP[12], nDSCP[13], nDSCP[14], nDSCP[15])
	return ret

def pyGSW_QoS_ClassPCP_Get(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ClassPCP_Get()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_ClassPCP_Set(nTrafficClass = 0, nPCP = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ClassPCP_Set(nTrafficClass, nPCP[0], nPCP[1], nPCP[2], nPCP[3], nPCP[4], nPCP[5], \
          nPCP[6], nPCP[7], nPCP[8], nPCP[9], nPCP[10], nPCP[11], \
          nPCP[12], nPCP[13], nPCP[14], nPCP[15])
	return ret

def pyGSW_QoS_DSCP_ClassGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_DSCP_ClassGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_DSCP_ClassSet(nDSCP = 0, nTrafficClass = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_DSCP_ClassSet(nDSCP, nTrafficClass[0], nTrafficClass[1], nTrafficClass[2], \
          nTrafficClass[3], nTrafficClass[4], nTrafficClass[5], \
          nTrafficClass[6], nTrafficClass[7], nTrafficClass[8], \
          nTrafficClass[9], nTrafficClass[10], nTrafficClass[11], \
          nTrafficClass[12], nTrafficClass[13], nTrafficClass[14], \
          nTrafficClass[15], nTrafficClass[16], nTrafficClass[17], \
          nTrafficClass[18], nTrafficClass[19], nTrafficClass[20], \
          nTrafficClass[21], nTrafficClass[22], nTrafficClass[23], \
          nTrafficClass[24], nTrafficClass[25], nTrafficClass[26], \
          nTrafficClass[27], nTrafficClass[28], nTrafficClass[29], \
          nTrafficClass[30], nTrafficClass[31], nTrafficClass[32], \
          nTrafficClass[33], nTrafficClass[34], nTrafficClass[35], \
          nTrafficClass[36], nTrafficClass[37], nTrafficClass[38], \
          nTrafficClass[39], nTrafficClass[40], nTrafficClass[41], \
          nTrafficClass[42], nTrafficClass[43], nTrafficClass[44], \
          nTrafficClass[45], nTrafficClass[46], nTrafficClass[47], \
          nTrafficClass[48], nTrafficClass[49], nTrafficClass[50], \
          nTrafficClass[51], nTrafficClass[52], nTrafficClass[53], \
          nTrafficClass[54], nTrafficClass[55], nTrafficClass[56], \
          nTrafficClass[57], nTrafficClass[58], nTrafficClass[59], \
          nTrafficClass[60], nTrafficClass[61], nTrafficClass[62], \
          nTrafficClass[63])
	return ret

def pyGSW_QoS_DSCP_DropPrecedenceCfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_DSCP_DropPrecedenceCfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_DSCP_DropPrecedenceCfgSet(nDSCP = 0, nDSCP_DropPrecedence = [0, 0, 0, 0, 0, 0, 0, 0, 0, \
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_DSCP_DropPrecedenceCfgSet(nDSCP, nDSCP_DropPrecedence[0], nDSCP_DropPrecedence[1], nDSCP_DropPrecedence[2], \
          nDSCP_DropPrecedence[3], nDSCP_DropPrecedence[4], nDSCP_DropPrecedence[5], \
          nDSCP_DropPrecedence[6], nDSCP_DropPrecedence[7], nDSCP_DropPrecedence[8], \
          nDSCP_DropPrecedence[9], nDSCP_DropPrecedence[10], \
          nDSCP_DropPrecedence[11], nDSCP_DropPrecedence[12], \
          nDSCP_DropPrecedence[13], nDSCP_DropPrecedence[14], \
          nDSCP_DropPrecedence[15], nDSCP_DropPrecedence[16], \
          nDSCP_DropPrecedence[17], nDSCP_DropPrecedence[18], \
          nDSCP_DropPrecedence[19], nDSCP_DropPrecedence[20], \
          nDSCP_DropPrecedence[21], nDSCP_DropPrecedence[22], \
          nDSCP_DropPrecedence[23], nDSCP_DropPrecedence[24], \
          nDSCP_DropPrecedence[25], nDSCP_DropPrecedence[26], \
          nDSCP_DropPrecedence[27], nDSCP_DropPrecedence[28], \
          nDSCP_DropPrecedence[29], nDSCP_DropPrecedence[30], \
          nDSCP_DropPrecedence[31], nDSCP_DropPrecedence[32], \
          nDSCP_DropPrecedence[33], nDSCP_DropPrecedence[34], \
          nDSCP_DropPrecedence[35], nDSCP_DropPrecedence[36], \
          nDSCP_DropPrecedence[37], nDSCP_DropPrecedence[38], \
          nDSCP_DropPrecedence[39], nDSCP_DropPrecedence[40], \
          nDSCP_DropPrecedence[41], nDSCP_DropPrecedence[42], \
          nDSCP_DropPrecedence[43], nDSCP_DropPrecedence[44], \
          nDSCP_DropPrecedence[45], nDSCP_DropPrecedence[46], \
          nDSCP_DropPrecedence[47], nDSCP_DropPrecedence[48], \
          nDSCP_DropPrecedence[49], nDSCP_DropPrecedence[50], \
          nDSCP_DropPrecedence[51], nDSCP_DropPrecedence[52], \
          nDSCP_DropPrecedence[53], nDSCP_DropPrecedence[54], \
          nDSCP_DropPrecedence[55], nDSCP_DropPrecedence[56], \
          nDSCP_DropPrecedence[57], nDSCP_DropPrecedence[58], \
          nDSCP_DropPrecedence[59], nDSCP_DropPrecedence[60], \
          nDSCP_DropPrecedence[61], nDSCP_DropPrecedence[62], \
          nDSCP_DropPrecedence[63])
	return ret

def pyGSW_QoS_FlowctrlCfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_FlowctrlCfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_FlowctrlCfgSet(nFlowCtrlNonConform_Min = 0, nFlowCtrlNonConform_Max = 0, nFlowCtrlConform_Min = 0, \
          nFlowCtrlConform_Max = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_FlowctrlCfgSet(nFlowCtrlNonConform_Min, nFlowCtrlNonConform_Max, nFlowCtrlConform_Min, \
          nFlowCtrlConform_Max)
	return ret

def pyGSW_QoS_FlowctrlPortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_FlowctrlPortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_FlowctrlPortCfgSet(nPortId = 0, nFlowCtrl_Min = 0, nFlowCtrl_Max = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_FlowctrlPortCfgSet(nPortId, nFlowCtrl_Min, nFlowCtrl_Max)
	return ret

def pyGSW_QoS_MeterCfgGet(nMeterId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_MeterCfgGet(nMeterId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_MeterCfgSet(bEnable = 0, nMeterId = 0, nCbs = 0, nEbs = 0, nRate = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_MeterCfgSet(bEnable, nMeterId, nCbs, nEbs, nRate)
	return ret

def pyGSW_QoS_MeterPortAssign(nMeterId = 0, eDir = 0, nPortIngressId = 0, nPortEgressId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_MeterPortAssign(nMeterId, eDir, nPortIngressId, nPortEgressId)
	return ret

def pyGSW_QoS_MeterPortDeassign(nMeterId = 0, nPortIngressId = 0, nPortEgressId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_MeterPortDeassign(nMeterId, nPortIngressId, nPortEgressId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_MeterPortGet(bInitial = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_MeterPortGet(bInitial)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_PCP_ClassGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_PCP_ClassGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_PCP_ClassSet(nPCP = 0, nTrafficClass = [0, 0, 0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = swse.enum[sw.pyGSW_QoS_PCP_ClassSet(nPCP, nTrafficClass[0], nTrafficClass[1], nTrafficClass[2], nTrafficClass[3], \
          nTrafficClass[4], nTrafficClass[5], nTrafficClass[6], \
          nTrafficClass[7])]
	return ret

def pyGSW_QoS_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_PortCfgSet(nPortId = 0, eClassMode = 0, nTrafficClass = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_PortCfgSet(nPortId, eClassMode, nTrafficClass)
	return ret

def pyGSW_QoS_PortRemarkingCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_PortRemarkingCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_PortRemarkingCfgSet(nPortId = 0, eDSCP_IngressRemarkingEnable = 0, bDSCP_EgressRemarkingEnable = 0, \
          bPCP_IngressRemarkingEnable = 0, bPCP_EgressRemarkingEnable = 0, bSTAG_PCP_IngressRemarkingEnable = 0, \
          bSTAG_DEI_IngressRemarkingEnable = 0, bSTAG_PCP_DEI_EgressRemarkingEnable = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_PortRemarkingCfgSet(nPortId, eDSCP_IngressRemarkingEnable, bDSCP_EgressRemarkingEnable, \
          bPCP_IngressRemarkingEnable, bPCP_EgressRemarkingEnable, \
          bSTAG_PCP_IngressRemarkingEnable, bSTAG_DEI_IngressRemarkingEnable, \
          bSTAG_PCP_DEI_EgressRemarkingEnable)
	return ret

def pyGSW_QoS_QueueBufferReserveCfgGet(nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_QueueBufferReserveCfgGet(nQueueId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_QueueBufferReserveCfgSet(nQueueId = 0, nBufferReserved = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_QueueBufferReserveCfgSet(nQueueId, nBufferReserved)
	return ret

def pyGSW_QoS_QueuePortGet(nPortId = 0, nTrafficClassId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_QueuePortGet(nPortId, nTrafficClassId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_QueuePortSet(nPortId = 0, nTrafficClassId = 0, nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_QueuePortSet(nPortId, nTrafficClassId, nQueueId)
	return ret

def pyGSW_QoS_SVLAN_ClassPCP_PortGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_SVLAN_ClassPCP_PortGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_SVLAN_ClassPCP_PortSet(nPortId = 0, nTrafficClass = 0, nCPCP = [0, 0, 0, 0, 0, 0, 0, 0, \
          0, 0, 0, 0, 0, 0, 0, 0], nSPCP = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], nDSCP = [\
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_SVLAN_ClassPCP_PortSet(nPortId, nTrafficClass, nCPCP[0], nCPCP[1], nCPCP[2], nCPCP[3], \
          nCPCP[4], nCPCP[5], nCPCP[6], nCPCP[7], nCPCP[8], nCPCP[9], \
          nCPCP[10], nCPCP[11], nCPCP[12], nCPCP[13], nCPCP[14], \
          nCPCP[15], nSPCP[0], nSPCP[1], nSPCP[2], nSPCP[3], \
          nSPCP[4], nSPCP[5], nSPCP[6], nSPCP[7], nSPCP[8], nSPCP[9], \
          nSPCP[10], nSPCP[11], nSPCP[12], nSPCP[13], nSPCP[14], \
          nSPCP[15], nDSCP[0], nDSCP[1], nDSCP[2], nDSCP[3], \
          nDSCP[4], nDSCP[5], nDSCP[6], nDSCP[7], nDSCP[8], nDSCP[9], \
          nDSCP[10], nDSCP[11], nDSCP[12], nDSCP[13], nDSCP[14], \
          nDSCP[15])
	return ret

def pyGSW_QoS_SVLAN_PCP_ClassGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_SVLAN_PCP_ClassGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_SVLAN_PCP_ClassSet(nTrafficClass = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], nTrafficColor = [\
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], nPCP_Remark_Enable = [0, 0, 0, 0, 0, 0, 0, \
          0, 0, 0, 0, 0, 0, 0, 0, 0], nDEI_Remark_Enable = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
          0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_SVLAN_PCP_ClassSet(nTrafficClass[0], nTrafficClass[1], nTrafficClass[2], nTrafficClass[3], \
          nTrafficClass[4], nTrafficClass[5], nTrafficClass[6], \
          nTrafficClass[7], nTrafficClass[8], nTrafficClass[9], \
          nTrafficClass[10], nTrafficClass[11], nTrafficClass[12], \
          nTrafficClass[13], nTrafficClass[14], nTrafficClass[15], \
          nTrafficColor[0], nTrafficColor[1], nTrafficColor[2], \
          nTrafficColor[3], nTrafficColor[4], nTrafficColor[5], \
          nTrafficColor[6], nTrafficColor[7], nTrafficColor[8], \
          nTrafficColor[9], nTrafficColor[10], nTrafficColor[11], \
          nTrafficColor[12], nTrafficColor[13], nTrafficColor[14], \
          nTrafficColor[15], nPCP_Remark_Enable[0], nPCP_Remark_Enable[1], \
          nPCP_Remark_Enable[2], nPCP_Remark_Enable[3], nPCP_Remark_Enable[4], \
          nPCP_Remark_Enable[5], nPCP_Remark_Enable[6], nPCP_Remark_Enable[7], \
          nPCP_Remark_Enable[8], nPCP_Remark_Enable[9], nPCP_Remark_Enable[10], \
          nPCP_Remark_Enable[11], nPCP_Remark_Enable[12], nPCP_Remark_Enable[13], \
          nPCP_Remark_Enable[14], nPCP_Remark_Enable[15], nDEI_Remark_Enable[0], \
          nDEI_Remark_Enable[1], nDEI_Remark_Enable[2], nDEI_Remark_Enable[3], \
          nDEI_Remark_Enable[4], nDEI_Remark_Enable[5], nDEI_Remark_Enable[6], \
          nDEI_Remark_Enable[7], nDEI_Remark_Enable[8], nDEI_Remark_Enable[9], \
          nDEI_Remark_Enable[10], nDEI_Remark_Enable[11], nDEI_Remark_Enable[12], \
          nDEI_Remark_Enable[13], nDEI_Remark_Enable[14], nDEI_Remark_Enable[15])
	return ret

def pyGSW_QoS_SchedulerCfgGet(nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_SchedulerCfgGet(nQueueId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_SchedulerCfgSet(nQueueId = 0, eType = 0, nWeight = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_SchedulerCfgSet(nQueueId, eType, nWeight)
	return ret

def pyGSW_QoS_ShaperCfgGet(nRateShaperId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ShaperCfgGet(nRateShaperId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_ShaperCfgSet(nRateShaperId = 0, bEnable = 0, bAVB = 0, nCbs = 0, nRate = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ShaperCfgSet(nRateShaperId, bEnable, bAVB, nCbs, nRate)
	return ret

def pyGSW_QoS_ShaperQueueAssign(nRateShaperId = 0, nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ShaperQueueAssign(nRateShaperId, nQueueId)
	return ret

def pyGSW_QoS_ShaperQueueDeassign(nRateShaperId = 0, nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ShaperQueueDeassign(nRateShaperId, nQueueId)
	return ret

def pyGSW_QoS_ShaperQueueGet(nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_ShaperQueueGet(nQueueId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_StormCfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_StormCfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_StormCfgSet(nMeterId = 0, bBroadcast = 0, bMulticast = 0, bUnknownUnicast = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_StormCfgSet(nMeterId, bBroadcast, bMulticast, bUnknownUnicast)
	return ret

def pyGSW_QoS_WredCfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_WredCfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_WredCfgSet(eProfile = 0, eThreshMode = 0, nRed_Min = 0, nRed_Max = 0, nYellow_Min = 0, \
          nYellow_Max = 0, nGreen_Min = 0, nGreen_Max = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_WredCfgSet(eProfile, eThreshMode, nRed_Min, nRed_Max, nYellow_Min, nYellow_Max, \
          nGreen_Min, nGreen_Max)
	return ret

def pyGSW_QoS_WredPortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_WredPortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_WredPortCfgSet(nPortId = 0, nRed_Min = 0, nRed_Max = 0, nYellow_Min = 0, nYellow_Max = 0, \
          nGreen_Min = 0, nGreen_Max = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_WredPortCfgSet(nPortId, nRed_Min, nRed_Max, nYellow_Min, nYellow_Max, nGreen_Min, \
          nGreen_Max)
	return ret

def pyGSW_QoS_WredQueueCfgGet(nQueueId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_WredQueueCfgGet(nQueueId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_QoS_WredQueueCfgSet(nQueueId = 0, nRed_Min = 0, nRed_Max = 0, nYellow_Min = 0, nYellow_Max = 0, \
          nGreen_Min = 0, nGreen_Max = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_QoS_WredQueueCfgSet(nQueueId, nRed_Min, nRed_Max, nYellow_Min, nYellow_Max, nGreen_Min, \
          nGreen_Max)
	return ret

def pyGSW_MulticastRouterPortAdd(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastRouterPortAdd(nPortId)
	return ret

def pyGSW_MulticastRouterPortRead(bInitial = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastRouterPortRead(bInitial)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MulticastRouterPortRemove(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastRouterPortRemove(nPortId)
	return ret

def pyGSW_MulticastSnoopCfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastSnoopCfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MulticastSnoopCfgSet(eIGMP_Mode = 0, bIGMPv3 = 0, bCrossVLAN = 0, eForwardPort = 0, nForwardPortId = 0, \
          nClassOfService = 0, nRobust = 0, nQueryInterval = 0, eSuppressionAggregation = 0, bFastLeave = 0, \
          bLearningRouter = 0, bMulticastUnknownDrop = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastSnoopCfgSet(eIGMP_Mode, bIGMPv3, bCrossVLAN, eForwardPort, nForwardPortId, \
          nClassOfService, nRobust, nQueryInterval, eSuppressionAggregation, \
          bFastLeave, bLearningRouter, bMulticastUnknownDrop)
	return ret

def pyGSW_MulticastTableEntryAdd(nPortId = 0, eIPVersion = 0, uIP_Gda = 0, uIP_Gsa = 0, eModeMember = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastTableEntryAdd(nPortId, eIPVersion, uIP_Gda, uIP_Gsa, eModeMember)
	return ret

def pyGSW_MulticastTableEntryRead(bInitial = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastTableEntryRead(bInitial)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MulticastTableEntryRemove(nPortId = 0, eIPVersion = 0, uIP_Gda = 0, uIP_Gsa = 0, eModeMember = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MulticastTableEntryRemove(nPortId, eIPVersion, uIP_Gda, uIP_Gsa, eModeMember)
	return ret

def pyGSW_CPU_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_CPU_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_CPU_PortCfgSet(nPortId = 0, bCPU_PortValid = 0, bSpecialTagIngress = 0, bSpecialTagEgress = 0, \
          bFcsCheck = 0, bFcsGenerate = 0, bSpecialTagEthType = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_CPU_PortCfgSet(nPortId, bCPU_PortValid, bSpecialTagIngress, bSpecialTagEgress, \
          bFcsCheck, bFcsGenerate, bSpecialTagEthType)
	return ret

def pyGSW_CapGet(nCapType = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_CapGet(nCapType)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_CfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_CfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_CfgSet(eMAC_TableAgeTimer = 0, bVLAN_Aware = 0, nMaxPacketLen = 0, bLearningLimitAction = 0, \
          bMAC_SpoofingAction = 0, bPauseMAC_ModeSrc = 0, nPauseMAC_Src = [0, 0, 0, 0, 0, 0], pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_CfgSet(eMAC_TableAgeTimer, bVLAN_Aware, nMaxPacketLen, bLearningLimitAction, \
          bMAC_SpoofingAction, bPauseMAC_ModeSrc, nPauseMAC_Src[0], \
          nPauseMAC_Src[1], nPauseMAC_Src[2], nPauseMAC_Src[3], \
          nPauseMAC_Src[4], nPauseMAC_Src[5])
	return ret

def pyGSW_Disable(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_Disable()
	return ret

def pyGSW_Enable(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_Enable()
	return ret

def pyGSW_HW_Init(eInitMode = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_HW_Init(eInitMode)
	return ret

def pyGSW_MDIO_CfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MDIO_CfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MDIO_CfgSet(nMDIO_Speed = 0, bMDIO_Enable = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MDIO_CfgSet(nMDIO_Speed, bMDIO_Enable)
	return ret

def pyGSW_MDIO_DataRead(nAddressDev = 0, nAddressReg = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MDIO_DataRead(nAddressDev, nAddressReg)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MDIO_DataWrite(nAddressDev = 0, nAddressReg = 0, nData = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MDIO_DataWrite(nAddressDev, nAddressReg, nData)
	return ret

def pyGSW_MonitorPortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MonitorPortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_MonitorPortCfgSet(nPortId = 0, bMonitorPort = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_MonitorPortCfgSet(nPortId, bMonitorPort)
	return ret

def pyGSW_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_PortCfgSet(nPortId = 0, eEnable = 0, bUnicastUnknownDrop = 0, bMulticastUnknownDrop = 0, bReservedPacketDrop = 0, \
          bBroadcastDrop = 0, bAging = 0, bLearning = 0, bLearningMAC_PortLock = 0, nLearningLimit = 0, \
          bMAC_SpoofingDetection = 0, eFlowCtrl = 0, ePortMonitor = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortCfgSet(nPortId, eEnable, bUnicastUnknownDrop, bMulticastUnknownDrop, \
          bReservedPacketDrop, bBroadcastDrop, bAging, bLearning, \
          bLearningMAC_PortLock, nLearningLimit, bMAC_SpoofingDetection, \
          eFlowCtrl, ePortMonitor)
	return ret

def pyGSW_PortLinkCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortLinkCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_PortLinkCfgSet(nPortId = 0, bDuplexForce = 0, eDuplex = 0, bSpeedForce = 0, eSpeed = 0, bLinkForce = 0, \
          eLink = 0, eMII_Mode = 0, eMII_Type = 0, eClkMode = 0, bLPI = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortLinkCfgSet(nPortId, bDuplexForce, eDuplex, bSpeedForce, eSpeed, bLinkForce, \
          eLink, eMII_Mode, eMII_Type, eClkMode, bLPI)
	return ret

def pyGSW_PortPHY_AddrGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortPHY_AddrGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_PortPHY_Query(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortPHY_Query(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_PortRGMII_ClkCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortRGMII_ClkCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_PortRGMII_ClkCfgSet(nPortId = 0, nDelayRx = 0, nDelayTx = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortRGMII_ClkCfgSet(nPortId, nDelayRx, nDelayTx)
	return ret

def pyGSW_PortRedirectGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortRedirectGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_PortRedirectSet(nPortId = 0, bRedirectEgress = 0, bRedirectIngress = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PortRedirectSet(nPortId, bRedirectEgress, bRedirectIngress)
	return ret

def pyGSW_RMON_Clear(eRmonType = 0, nRmonId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_RMON_Clear(eRmonType, nRmonId)
	return ret

def pyGSW_RMON_Port_Get(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_RMON_Port_Get(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_VersionGet(nId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_VersionGet(nId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_WoL_CfgGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_WoL_CfgGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_WoL_CfgSet(nWolMAC = [0, 0, 0, 0, 0, 0], nWolPassword = [0, 0, 0, 0, 0, 0], bWolPasswordEnable = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_WoL_CfgSet(nWolMAC[0], nWolMAC[1], nWolMAC[2], nWolMAC[3], nWolMAC[4], nWolMAC[5], \
          nWolPassword[0], nWolPassword[1], nWolPassword[2], \
          nWolPassword[3], nWolPassword[4], nWolPassword[5], \
          bWolPasswordEnable)
	return ret

def pyGSW_WoL_PortCfgGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_WoL_PortCfgGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_WoL_PortCfgSet(nPortId = 0, bWakeOnLAN_Enable = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_WoL_PortCfgSet(nPortId, bWakeOnLAN_Enable)
	return ret

def pyGSW_RegisterGet(nRegAddr = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_RegisterGet(nRegAddr)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_RegisterSet(nRegAddr = 0, nData = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_RegisterSet(nRegAddr, nData)
	return ret

def pyGSW_IrqMaskGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_IrqMaskGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_IrqMaskSet(nPortId = 0, eIrqSrc = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_IrqMaskSet(nPortId, eIrqSrc)
	return ret

def pyGSW_PceRuleDelete(nIndex = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_PceRuleDelete(nIndex)
	return ret


def pyGSW_RMON_ExtendGet(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_RMON_ExtendGet(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_Reset(eReset = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_Reset(eReset)
	return ret

def pyGSW_TimestampPortRead(nPortId = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TimestampPortRead(nPortId)

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_TimestampTimerGet(pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TimestampTimerGet()

	fo = open(fn, "r")
	for line in fo.readlines():
		if len(line.split()) == 1:
			line = line[:-1] + "    ---    Return value: " + nRet[ret["ret"]] + "\n"
		else:
			if line.split()[0][-1] == "]":
				s = ""
				for i in line.split()[2:]:
					s = s + i + " "
				ret[line.split()[0]] = s
			else:
				ret[line.split()[0]] = line.split()[3]
		if pr == 1:
			s = ""
			for st in swse.struct:
				for p in swse.struct[st]:
					if p[1] == line.split()[0]:
						e = p[0]
						if p[0] in swse.enum:
							s = swse.enum[p[0]][line.split()[3]] + "  [" + p[0] + "]"
			print (line[:-1], s)
	fo.close()
	return ret

def pyGSW_TimestampTimerSet(nSec = 0, nNanoSec = 0, nFractionalNanoSec = 0, pr = 1):
	ret = dict()
	ret["ret"] = sw.pyGSW_TimestampTimerSet(nSec, nNanoSec, nFractionalNanoSec)
	return ret






#==================================================================================
#========== Copy from PySwitchCli.py End===========================================
#==================================================================================

def Phy_sum(n):
		a = mdior(n, 1)
		b = mdior(n, 0x18)
		c = mdior(n, 0x10)
		d = mdior(n, 0xa)
		e = mdior(n, 0x15)
		print ("Phy:", n, "   Link state:", (a&0x4)/4, "    Speed:", 10**((b&0x3)+1), "Mbps" )
		print ("Master(1)/Slave(0):", (d&0x4000)/0x4000, "    Local receiver OK:", (d&0x2000)/0x2000, \
			"    Remote receiver OK:", (d&0x1000)/0x1000)
		print ("SNR margin:", (c&0xf0)/0x10, "    Cable length:", (c&0xf)*10, "m")
		str01 = ["rx err","rx frames","ESD err","SSD err","tx err","tx frames","collision","no. of link down","no. of ADS"]
		#print ("Error counter:", e&0xff, "   ", str01[(e&0xf00)/0x100%9])
		
def set_counter(n):
		print ("0: rx err")
		print ("1: rx frames")
		print ("2: ESD err")
		print ("3: SSD err")
		print ("4: tx err")
		print ("5: tx frames")
		print ("6: collision")
		print ("7: no. of link down")
		print ("8: no. of ADS")
		a = input("Which counter to set: 0-8 [1]")
		mdiow(n, 0x15, a*0x100)
