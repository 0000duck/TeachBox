/**
*@file
*文件名称：GlobalVar.h
*摘要：定义全局变量
*@author fly1992@163.com
**/
#pragma once
#include <string>
#include <sstream>
#include <exdisp.h>
#include <comdef.h>
#include "UIlib.h"
#include "TechBoxLib.h"
using namespace DuiLib;
#ifdef UNICODE  
	#ifndef TSTRING  
		#define TSTRING std::wstring  
#	endif  
#else  
	#ifndef TSTRING  
		#define TSTRING std::string  
	#endif  
#endif 

#include "KeyPadWnd.h"

extern const wchar_t *HostIP;///<主机（服务器）的ip地址
extern const int PORT;///<通信端口号

///用户级别定义
typedef enum USERLIMITS{OPERATOR,ADMIN};
extern USERLIMITS USLM;

typedef enum KEYSWITCH{KEYNEWFILE,KEYPROJECT};
extern KEYSWITCH GKW;///<确定当前的按键是KEYNEWFILE，KEYPROJECT

typedef enum AXIS{AXISSM=0,AXISSP,AXISLM,AXISLP,
					AXISUM,AXISUP,AXISRM,AXISRP,AXISBM,
					AXISBP,AXISTM,AXISTP,AXISSTOP,NUMAXISCONTROL=12};

typedef enum INSTR{INSERTMOVJ=0,INSERTMOVL,INSERTMOVC,INSTREND};
///数字转string
template <class Type>
string NumToString(const Type num)
{
	ostringstream str;
	str<<num;
	return str.str();
}
///宽字符转string
std::string Tchar2String(LPCTSTR tChar);
///string转宽字符
CStdString StringToTChar(std::string str);
void Delayms(DWORD TempTime);
///重定义物理按键键值，便于识记
class CTeachBoxKeyValue
{
public:
	static const int KEYUP=0;///<按键弹出时发出的响应
	static const int KEYCONNECT=TEACHBOX_KEY1;
	static const int KEYNEWFILE=TEACHBOX_KEY4;
	static const int KEYPROJECT=TEACHBOX_KEY5;
	static const int KEYCOORD=TEACHBOX_KEY6;
	static const int KEYSHUTDOWN1=TEACHBOX_KEY7;
	static const int KEYSTART=TEACHBOX_KEY9;
	

	static const int KEYAXISSM=TEACHBOX_KEY10;
	static const int KEYAXISSP=TEACHBOX_KEY11;
	static const int KEYAXISLM=TEACHBOX_KEY12;
	static const int KEYAXISLP=TEACHBOX_KEY13;
	static const int KEYAXISUM=TEACHBOX_KEY14;
	static const int KEYAXISUP=TEACHBOX_KEY15;
	static const int KEYAXISRM=TEACHBOX_KEY16;
	static const int KEYAXISRP=TEACHBOX_KEY17;
	static const int KEYAXISBM=TEACHBOX_KEY18;
	static const int KEYAXISBP=TEACHBOX_KEY19;
	static const int KEYAXISTM=TEACHBOX_KEY20;
	static const int KEYAXISTP=TEACHBOX_KEY21;
	static const int KEYSHUTDOWN2=TEACHBOX_KEY22;
	static const int KEYMODEL=TEACHBOX_KEY23;

	static const int KEYSYNC=TEACHBOX_KEY24;
	static const int KEYSERVE=TEACHBOX_KEY25;
	static const int KEYROBOT=TEACHBOX_KEY26;
	static const int KEYSTEP=TEACHBOX_KEY29;
	static const int KEYSPEED=TEACHBOX_KEY31;

};
///定义机器人命令号，发送到控制器
class CRobotStateValue
{
public:

	static const int SERVEON=1000;
	static const int SERVEOFF=1001;
	static const int MODELTEACH=1006;
	static const int MODELREPALY=1007;
	static const int SPEEDHIGH=1008;
	static const int SPEEDMID=1009;
	static const int SPEEDLOW=1010;
	static const int COORDCART=1002;
	static const int COORDJOINT=1003;
	static const int COORDTOOL=1004;
	static const int COORDUSER=1005;
	static const int SYNC=1014;
	static const int UNSYNC=1015;
	static const int ROBOTBASE=1016;
	static const int POSTIONER=1017;

	static const int AXISSM=3003;
	static const int AXISSP=3004;
	static const int AXISLM=3005;
	static const int AXISLP=3006;
	static const int AXISUM=3007;
	static const int AXISUP=3008;
	static const int AXISRM=3009;
	static const int AXISRP=3010;
	static const int AXISBM=3011;
	static const int AXISBP=3012;
	static const int AXISTM=3013;
	static const int AXISTP=3014;
	static const int AXISSTOP=3015;

	static const int INSERTMOVJ=3002;
	static const int INSERTMOVL=3017;
	static const int INSERTMOVC=3018;
	static const int INSTREND=3001;
};

