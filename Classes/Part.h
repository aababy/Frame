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
    Part(CCSprite * preview);
    void preview(UIListView *_list);

    void import(string path);
    vector<FramesName> m_vFrameOriginal;
    vector<FramesName> m_vFrameUsed;

private:
    CCSprite * m_preview;

    vector<string> m_vFileName;

    char    address[200];
    char    fullPathName[200];

    bool    m_bRunning;
    float   m_fAccumulate;
    int     m_iCurFrameIndex;

    void update(float delta);


};

#endif /* defined(__Frame__Part__) */
