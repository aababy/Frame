//
//  Part.h
//  Frame
//
//  Created by luoxp on 14-10-17.
//
//

#ifndef __Frame__Part__
#define __Frame__Part__

#include "IncludeForHeader.h"

class Part : public CCObject
{
public:
    Part(CCSprite * preview, UIListView *list);
    void preview(float delay);
    void deleteFrames();

    void import(string path);
    vector<MyFrame> m_vFrameOriginal;
    vector<MyFrame> m_vFrameUsed;

private:
    CCSprite * m_preview;

    vector<string> m_vFileName;

    char    address[200];
    char    fullPathName[200];

    bool    m_bRunning;
    float   m_fAccumulate;
    int     m_iCurFrameIndex;

    void update(float delta);

    string  _path;
    UIListView *_list;

    float   _fDelay;
};

#endif /* defined(__Frame__Part__) */
