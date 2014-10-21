//
//  IncludeForHeader.h
//  Tool
//
//  Created by luoxp on 14-7-30.
//
//

#ifndef Tool_IncludeForHeader_h
#define Tool_IncludeForHeader_h

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

class Part;

using std::string;
using std::vector;
using std::swap;
using std::ofstream;

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

#define FLAG_COUNT              (6)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define SEPARATOR   ("\\")
#else
#define SEPARATOR   ("/")
#endif

struct MyFrame
{
    string  sFrameName;
    int     iNumber;
    bool    bDeleted;           //这一帧是否被删除.
    float   fDelay;             //延迟
};

struct SkillName
{
    string  s;
    int     flag;               //0:普通攻击, 1:技能
};

enum setOperateType
{
    OT_NEW,
    OT_SELECT,
    OT_BROWSE,
};

enum curState
{
    CS_NONE,
    CS_TOTAL_PLIST,
    CS_MAIN_PLIST,
};

enum flagIndex
{
    FI_MOVE,                    //主体特有
    FI_RANDOMPOSITION,          //特效特有
    FI_RANDOMCOUNT,
    FI_FOLLOW,
    FI_FIXED,
    FI_ISOLATE,
    FI_MAX,
};


#endif
