#include "MainScene.h"
#include "IncludeForCpp.h"

enum UITag
{
    FRAME_BG = 6,
    BUTTON_IMPORT = 8,
};


//1920x1080
//1920x864
//960x432
CCScene* MainScene::scene()
{
    CCScene* pScene = CCScene::create();
    MainScene* uiLayer = new MainScene();
    if (uiLayer && uiLayer->init(pScene))
    {
        uiLayer->autorelease();
        pScene->addChild(uiLayer);
    }
    else
    {
        CC_SAFE_DELETE(uiLayer);
    }
    return pScene;
}


bool MainScene::init(CCScene* pScene)
{
    if (CCLayer::init())
    {      
        m_rootNode = (NodeReader::getInstance()->createNode("R/Frame_1.ExportJson"));
        addChild(m_rootNode);
        
        Layout *root = static_cast<Layout*>(m_rootNode->getChildren()->objectAtIndex(0));
        m_root = root;
        
        setTouchEnabled(true);
        
        return true;
    }
    
    return true;
}

MainScene::~MainScene()
{
    xNotify->removeAllObservers(this);
}


void MainScene::touchEvent(CCObject *pSender, TouchEventType type)
{
    if(type != TOUCH_EVENT_ENDED)
    {
        return;
    }
    
    Widget *widget = (Widget*)pSender;
    int iTag = widget->getTag();
    
    switch (iTag) {
        case BUTTON_IMPORT:
        {
        }
            break;
        default:
        {
        }
            break;
    }
}

void MainScene::editBoxEditingDidBegin(CCEditBox* editBox)
{
}

void MainScene::editBoxEditingDidEnd(CCEditBox* editBox)
{
}

void MainScene::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
}

void MainScene::editBoxReturn(CCEditBox* editBox)
{
}



