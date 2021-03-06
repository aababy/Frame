//
//  IncludeForCpp.h
//  Tool
//
//  Created by luoxp on 14-7-30.
//
//

#ifndef Tool_IncludeForCpp_h
#define Tool_IncludeForCpp_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "cocos-ext.h"

#include "MainScene.h"
#include "Helper.h"
#include "InputBox.h"
#include "XmlData.h"
#include "Part.h"

using namespace cocostudio::timeline;

#define xScheduler                      CCDirector::sharedDirector()->getScheduler()
#define xSpriteFC                       CCSpriteFrameCache::sharedSpriteFrameCache()
#define xNotify                         (CCNotificationCenter::sharedNotificationCenter())
#define xData                           (CCUserDefault::sharedUserDefault())

#define UPDATE_PROPERTY                 "UPDATE_PROPERTY"
#define SEARCH_PATH                     "SEARCH_PATH"
#define SAVE_PATH                       "SAVE_PATH"
#define UPDATE_MOTION                   "UPDATE_MOTION"
#define UPDATE_EFFECT_LIST              "UPDATE_EFFECT_LIST"
#define UPDATE_MOTION_LIST              "UPDATE_MOTION_LIST"
#define UPDATE_ALL_INDEX                "UPDATE_ALL_INDEX"
#define NORMAL                          "NORMAL"
#define UPDATE_ERROR                     "UPDATE_ERROR"

#endif
