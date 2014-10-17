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

class Part
{
public:
    Part();

    void import(string path);
    vector<FramesName> m_vFrameOriginal;
    vector<FramesName> m_vFrameUsed;

private:
    vector<string> m_vFileName;

    char    address[200];
    char    fullPathName[200];
};

#endif /* defined(__Frame__Part__) */
