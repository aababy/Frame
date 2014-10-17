#include "MainScene.h"
#include "IncludeForCpp.h"

enum UITag
{
    BTN_PREVIEW = 393,
    CHECK_BOX = 394,
    SPRITE = 398,
    INPUT = 399,
    BUTTON_IMPORT = 400,
    LAYOUT = 100,
    BTN_DELETE = 401,
};


#define SIDE_LEN            (200)

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

        initButton(BTN_PREVIEW, root, this, toucheventselector(MainScene::touchEvent));
        initButton(BUTTON_IMPORT, root, this, toucheventselector(MainScene::touchEvent));
        initButton(BTN_DELETE, root, this, toucheventselector(MainScene::touchEvent));

        input = InputBox::create(INPUT, root, this, m_rootNode);

        _list = (UIListView*)UIHelper::seekWidgetByTag(root, 392);

        check = (UICheckBox*)UIHelper::seekWidgetByTag(root, CHECK_BOX);
        check->setVisible(false);

        setTouchEnabled(true);

        CCSprite *preview = (CCSprite*)m_rootNode->getChildByTag(SPRITE);

        part = new Part(preview, _list);
        
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
            import();
        }
            break;
        case BTN_PREVIEW:
        {
            part->preview(_list);
        }
            break;
        case BTN_DELETE:
        {
            part->deleteFrames();
        }
            break;
        case LAYOUT:
        {
            CCArray *array = _list->getItems();

            CCObject *object = NULL;
            CCARRAY_FOREACH(array, object)
                {
                    Layout * layout = (Layout*)object;

                    if (layout == pSender)
                    {
                        UICheckBox * check = (UICheckBox*)UIHelper::seekWidgetByTag(layout, CHECK_BOX);

                        bool bCheck = !(check->getSelectedState());
                        check->setSelectedState(bCheck);
                    }
                }
        }
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


void MainScene::import()
{
    if(strcmp(input->getText(), "") == 0)
    {
        return;
    }

    part->import(input->getText());

    vector<FramesName> &vFrameName = part->m_vFrameOriginal;

    for(int i = 0; i < vFrameName.size(); i++)
    {
        Layout * layout = Layout::create();
        layout->setContentSize(CCSizeMake(SIDE_LEN, SIDE_LEN));
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(ccBLACK);
        layout->setSize(CCSizeMake(SIDE_LEN, SIDE_LEN));
        layout->setTouchEnabled(true);
        layout->setTag(LAYOUT);
        layout->addTouchEventListener(this, toucheventselector(MainScene::touchEvent));

        UIImageView * image = UIImageView::create();
        image->loadTexture(vFrameName.at(i).sFrameName.c_str(), UI_TEX_TYPE_PLIST);
        image->setPosition(ccp(SIDE_LEN/2, SIDE_LEN/2));
        image->setScale(0.5);

        UICheckBox * checkOne = (UICheckBox*)check->clone();
        checkOne->setVisible(true);
        checkOne->setScale(0.5);
        checkOne->setPosition(ccp(SIDE_LEN - 20, SIDE_LEN - 20));
        checkOne->setSelectedState(!part->m_vFrameOriginal.at(i).bDeleted);

        layout->addChild(image);
        layout->addChild(checkOne);
        _list->pushBackCustomItem(layout);
    }
}
