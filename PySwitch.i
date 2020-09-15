/* File: PySwitchCli.i */
%module PySwitchCli
%{
#define SWIG_FILE_WITH_INIT
#include "f2x_swapi.h"
#include "f2x_swapi_flow.h"
#include "f2x_swapi_kapi.h"
#include "f2x_swapi_types.h"
#include "gsw708x_reg.h"
#include "gsw_api_func.h"
#include "gsw_sw_init.h"
#include "gsw_core.h"
#include "gsw_io_wrap.h"
#include "gsw_swreg.h"
#include "gsw_py_interface.h"
%}

%typemap(in) u64, u32, u16, u8, i32, i16, i8, ur, ltq_bool_t, int, char, GSW_irqSrc_t, GSW_PCE_IP_t, GSW_PCE_ActionIGMP_Snoop_t, GSW_PCE_ActionLearning_t, GSW_PCE_ActionMeter_t, GSW_PCE_ActionTrafficClass_t, GSW_PCE_ActionIrq_t, GSW_PCE_ActionCrossState_t, GSW_PCE_ActionCriticalFrame_t, GSW_PCE_ActionTimestamp_t, GSW_PCE_ActionPortmap_t, GSW_PCE_ActionVLAN_t, GSW_PCE_ActionCrossVLAN_t, GSW_resetMode_t, GSW_portForward_t, GSW_STP_PortState_t, GSW_8021X_portState_t, GSW_VLAN_Admit_t, GSW_VLAN_MemberViolation_t, GSW_Qos_ingressRemarking_t, GSW_QoS_DropPrecedence_t, GSW_QoS_ClassSelect_t, GSW_QoS_WRED_ThreshMode_t, GSW_QoS_WRED_Profile_t, GSW_direction_t, GSW_QoS_Scheduler_t, GSW_multicastSnoopMode_t, GSW_multicastReportSuppression_t, GSW_IGMP_MemberMode_t, GSW_HW_InitMode_t, GSW_ageTimer_t, GSW_portSpeed_t, GSW_portDuplex_t, GSW_portLink_t, GSW_capType_t, GSW_portEnable_t, GSW_portMonitor_t, GSW_portFlow_t, GSW_CPU_SpecialTagEthType_t, GSW_CPU_HeaderMode_t, GSW_CPU_Pause_t, GSW_MII_Mode_t, GSW_MII_Type_t, GSW_clkMode_t, GSW_return_t, GSW_RMON_type_t, GSW_RMON_CountMode_t %{
  // Skips PyLong_Check and calls PyLong_AsLong, which calls __int__ as needed
  $1 = PyLong_AsUnsignedLong($input);
%}

%include "gsw_py_interface.h"