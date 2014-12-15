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
    
    void add(float dt);
    void del(float dt);
    
    //editbox
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
    void updateCellAtIndex(CCObject* list, const CCPoint &indexes, const bool &created, Widget *userData);
    void onCheckBox(CCObject* sender, CheckBoxEventType type);
    
protected:
    ~MainScene();

    Layout*     m_root;
    CCNode*     m_rootNode;
    UIListView* _list;
    UIListView* _listTotal;
    UICheckBox * check;
    InputBox*   input;
    InputBox*_inputDelay;

    vector<Part*> _parts;
    vector<Layout*> _layouts;
    
    CCSprite *_preview;
    
    Layout * _delayPanel;
    
    CCPoint _posDelayPanel;

    void import();
    
    bool        _bAdd = true;
    UILabel *   _labelNumber;
    float       _fAdjust = 0.01;
    UIListView* _listPart;
    int         _count = 7;
};

#endif // __HELLOWORLD_SCENE_H__
