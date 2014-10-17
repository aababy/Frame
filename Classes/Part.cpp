//
//  Part.cpp
//  Frame
//
//  Created by luoxp on 14-10-17.
//
//
#include "IncludeForCpp.h"
#include "Part.h"


Part::Part(CCSprite * preview)
{
    m_preview = preview;
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

        m_vFrameOriginal.push_back(frames);
    }

    fin.close();

    if (m_vFrameOriginal.size() != 0)
    {
        //排序
        bubble_sort(m_vFrameOriginal);

        CCFileUtils::sharedFileUtils()->addSearchPath(szAddress);

        //读取每一个图片
        for(int i = 0; i < m_vFrameOriginal.size(); i++)
        {
            CCSprite *sprite = CCSprite::create(m_vFrameOriginal.at(i).sFrameName.c_str());
            CCSpriteFrame *frame = CCSpriteFrame::create(m_vFrameOriginal.at(i).sFrameName.c_str(), CCRectMake(0, 0, sprite->getContentSize().width, sprite->getContentSize().height));
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, m_vFrameOriginal.at(i).sFrameName.c_str());
        }
    }
}


void Part::preview()
{
    m_vFrameUsed.clear();

    for(int i = 0; i < m_vFrameOriginal.size(); i++)
    {
        if(m_vFrameOriginal.at(i).bDeleted == false)
        {
            m_vFrameUsed.push_back(m_vFrameOriginal.at(i));
        }
    }

    m_iCurFrameIndex = 0;
    CCSpriteFrame* frame = xSpriteFC->spriteFrameByName(m_vFrameUsed.at(m_iCurFrameIndex).sFrameName.c_str());
    m_preview->setDisplayFrame(frame);
    m_preview->setVisible(true);

    xScheduler->unscheduleUpdateForTarget(this);
    xScheduler->scheduleUpdateForTarget(this, 0, false);
    m_bRunning = true;
}


void Part::update(float delta)
{
    if (m_bRunning) {
        //累积时间
        m_fAccumulate += delta;

        //如果累积时间大于帧间隔, 清空, 然后播放下一帧
        if (m_fAccumulate > 0.05f) {
            m_fAccumulate = 0.f;
            m_iCurFrameIndex++;

            if (m_iCurFrameIndex < m_vFrameUsed.size()) {
                CCSpriteFrame* frame = xSpriteFC->spriteFrameByName(m_vFrameUsed.at(m_iCurFrameIndex).sFrameName.c_str());
                m_preview->setDisplayFrame(frame);
            }
            else
            {
                //所有帧数都播放完.
                m_bRunning = false;
                m_fAccumulate = 0;
                //如果是特效, 设置不可见
                m_preview->setVisible(false);

                xScheduler->unscheduleUpdateForTarget(this);
            }
        }
    }
}