#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "IncludeForHeader.h"

#define UI_SCENE_CREATE_FUNC(UIScene) \
public: \
static CCScene* scene() \
{ \
    CCScene* pScene = CCScene::create(); \
    UIScene* uiLayer = new UIScene(); \
    if (uiLayer && uiLayer->init()) \
    { \
    uiLayer->autorelease(); \
    pScene->addChild(uiLayer); \
    } \
    else \
    { \
    CC_SAFE_DELETE(uiLayer); \
    } \
    return pScene; \
}

class InputBox;

class MainScene : public CCLayer, public CCEditBoxDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(CCScene* pScene);
    
    // implement the "static node()" method manually
    static CCScene* scene();
    
    void touchEvent(CCObject *pSender, TouchEventType type);
    
    //editbox
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
protected:
    ~MainScene();

    Layout*     m_root;
    CCNode*     m_rootNode;
    UIListView* _list;
    UICheckBox * check;
    InputBox*   input;
    InputBox*_inputDelay;

    Part *      part;

    void import();
};

#endif // __HELLOWORLD_SCENE_H__
