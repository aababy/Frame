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

class Part : public CCNode
{
public:
    Part(CCSprite * preview);
    void preview();
    void deleteFrames();

    void import(string path);
    vector<MyFrame> m_vFrameOriginal;
    vector<MyFrame> m_vFrameUsed;
    
    void setBindingList(UIListView *list, UILabel *label);
    void startPreview(float delta);
    UIListView *_list;

private:
    void texturePacker();
    CCSprite * m_preview;

    vector<string> m_vFileName;

    char    address[200];
    char    fullPathName[200];

    bool    m_bRunning;
    float   m_fAccumulate;
    int     m_iCurFrameIndex;

    void update(float delta);

    string  _path;
    
    UILabel *_label;

};

#endif /* defined(__Frame__Part__) */
