//
//  Part.cpp
//  Frame
//
//  Created by luoxp on 14-10-17.
//
//
#include "IncludeForCpp.h"
#include "Part.h"


Part::Part()
{

}

void Part::import(string path)
{
    if(path.empty()) return;

    m_vFileName.clear();
    m_vFrameUsed.clear();
    m_vFrameOriginal.clear();

    //1. 将指定地址下的文件列出来, 存放到临时文件里面.
    const char * szAddress = path.c_str();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    sprintf(address, "dir \"%s\" /b > \"%s/temp.txt\"", szAddress, szAddress);
#else
    sprintf(address, "ls \"%s\" > \"%s/temp.txt\"", szAddress, szAddress);
#endif

    //使用shell/dos命令来操作
    system(address);

    //2. 将文件中的内容读出来, 存放到vector里面.
    sprintf(fullPathName, "%s/temp.txt", szAddress);
    //int lines = countLines(fullPathName);

    ifstream fin(fullPathName);
    string strLine;
    while(getline(fin,strLine))
    {
        if(strLine.compare("temp.txt") == 0) continue;

        FramesName frames;
        frames.iNumber = getNumber(strLine);
        frames.sFrameName = strLine;
        frames.bDeleted = false;

        m_vFrameUsed.push_back(frames);
        m_vFrameOriginal.push_back(frames);
    }

    fin.close();

    if (m_vFrameUsed.size() != 0)
    {
        //排序
        bubble_sort(m_vFrameUsed);

        CCFileUtils::sharedFileUtils()->addSearchPath(szAddress);

        //读取每一个图片
        for(int i = 0; i < m_vFrameUsed.size(); i++)
        {
            CCSprite *sprite = CCSprite::create(m_vFrameUsed.at(i).sFrameName.c_str());
            CCSpriteFrame *frame = CCSpriteFrame::create(m_vFrameUsed.at(i).sFrameName.c_str(), CCRectMake(0, 0, sprite->getContentSize().width, sprite->getContentSize().height));
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, m_vFrameUsed.at(i).sFrameName.c_str());
        }
    }
}
