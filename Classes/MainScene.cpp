#include "MainScene.h"
#include "IncludeForCpp.h"

enum UITag
{
    BTN_PREVIEW = 393,
    CHECK_BOX = 394,
    SPRITE = 398,
    UI_INPUT = 399,
    BUTTON_IMPORT = 400,
    LAYOUT = 100,
    BTN_DELETE_ALL = 401,
    INPUT_DELAY = 403,
    LABEL_DELAY = 408,
    BTN_ADD = 409,
    BTN_DEL = 410,

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

        Layout * delay = (Layout*)UIHelper::seekWidgetByTag(m_root, 407);
        delay->setVisible(false);

        initButton(BTN_PREVIEW, root, this, toucheventselector(MainScene::touchEvent));
        initButton(BUTTON_IMPORT, root, this, toucheventselector(MainScene::touchEvent));
        initButton(BTN_DELETE_ALL, root, this, toucheventselector(MainScene::touchEvent));

        input = InputBox::create(UI_INPUT, root, this, m_rootNode);
        _inputDelay = InputBox::create(INPUT_DELAY, root, this, m_rootNode);
        _inputDelay->setText("0.05");

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
            part->preview(atof(_inputDelay->getText()));
        }
            break;
        case BTN_DELETE_ALL:
        {
            part->deleteFrames();
        }
            break;
        case BTN_ADD:
        {
            UIButton* btn = (UIButton*)widget;
            UILabel *label = (UILabel *)btn->getUserData();
            const char * text = label->getStringValue();
            float delay = atof(text);
            delay += 0.01f;
            label->setText(any2string(delay));
        }
            break;
        case BTN_DEL:
        {
            UIButton* btn = (UIButton*)widget;
            UILabel *label = (UILabel *)btn->getUserData();
            const char * text = label->getStringValue();
            float delay = atof(text);
            delay -= 0.01f;
            label->setText(any2string(delay));
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
    //改变所以帧的值
    for(int i = 0; i < part->m_vFrameOriginal.size(); i++)
    {
        Layout * layout = (Layout*) _list->getItem(i);
        UILabel * label = (UILabel*)UIHelper::seekWidgetByTag(layout, 408);
        label->setText(text);
    }
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

    vector<MyFrame> &vFrameName = part->m_vFrameOriginal;
    Layout * delay = (Layout*)UIHelper::seekWidgetByTag(m_root, 407);
    delay->setVisible(true);

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

        Layout * layout_delay = (Layout*)delay->clone();
        layout_delay->setPosition(ccp(SIDE_LEN/2 - layout_delay->getContentSize().width / 2, -1 * layout_delay->getContentSize().height));

        UILabel * label = (UILabel*)UIHelper::seekWidgetByTag(layout_delay, LABEL_DELAY);
        label->setText(any2string(part->m_vFrameOriginal.at(i).fDelay));

        UIButton * btnAdd = initButton(BTN_ADD, layout_delay, this, toucheventselector(MainScene::touchEvent));
        btnAdd->setUserData(label);

        UIButton * btnDel = initButton(BTN_DEL, layout_delay, this, toucheventselector(MainScene::touchEvent));
        btnDel->setUserData(label);

        layout->addChild(layout_delay, 10);
        layout->addChild(image);
        layout->addChild(checkOne);
        _list->pushBackCustomItem(layout);
    }

    delay->setVisible(false);
}
