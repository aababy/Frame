//
//  Helper.h
//  Tool
//
//  Created by luoxp on 14-7-31.
//
//

#ifndef __Tool__Helper__
#define __Tool__Helper__

#include "IncludeForHeader.h"

class Motion;

int cycleNum(bool bAdd, int iCount, int *idx);

Button * initButton(int iTag, Layout* root, CCObject *target, SEL_TouchEvent selector);

TextField * initTextField(int iTag, Layout* root);

int getNumber(string &str);

void bubble_sort(vector<FramesName> &vFrameName);
void insertFloat(CCDictionary *dic, const string& key, float value);
void insertString(CCDictionary *dic, const string& key, const string& value);
void insertInteger(CCDictionary *dic, const string& key, int value);
void insertArray(CCDictionary *dic, const string& key, CCArray* value);
void insertCCPoint(CCDictionary *dic, const string& key, CCPoint& value);
string itostring(int i);
CheckBox * initCheckBox(int iTag, Layout* root, CCObject *target, SEL_SelectedStateEvent selector);
CCPoint pointRotateWithAngle(CCPoint& point, float fDegree);
string flag2string(bool m_flag[FLAG_COUNT]);
void string2Vector(string &name, vector<string>& vec);
CCPoint str2Point(const char * sz);
void string2Flags(CCString *sFlags, bool *flags);
bool isEqualFloat(float f1, float f2);
void makeDir(string path);
void deleteFile(string &path);
void renameFile(string &path, string &old, string &newname);

template <class T> string any2string(T tmp)
{
    std::stringstream ss;
    ss << tmp;
    return ss.str();
};
#endif /* defined(__Tool__Helper__) */
