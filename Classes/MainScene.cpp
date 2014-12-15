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
    BTN_UP = 412,
    BTN_DOWN = 413,
    LAYOUT_TEST= 999,
};


#define SIDE_LEN            (200)
#define OFFSET_Y            (200 + 30)          //一行的高度 + 间隔

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
        initButton(BTN_UP, root, this, toucheventselector(MainScene::touchEvent));
        initButton(BTN_DOWN, root, this, toucheventselector(MainScene::touchEvent));

        input = InputBox::create(UI_INPUT, root, this, m_rootNode);
        _inputDelay = InputBox::create(INPUT_DELAY, root, this, m_rootNode);
        _inputDelay->setText("0.05");
        
        _listTotal = (UIListView*)UIHelper::seekWidgetByTag(root, 392);

        check = (UICheckBox*)UIHelper::seekWidgetByTag(root, CHECK_BOX);
        check->setVisible(false);
        
        _delayPanel = (Layout*)UIHelper::seekWidgetByTag(m_root, 407);
        _delayPanel->setVisible(false);
        _posDelayPanel = _delayPanel->getPosition();

        setTouchEnabled(true);

        _preview = (CCSprite*)m_rootNode->getChildByTag(SPRITE);
        
        return true;
    }
    
    return true;
}

MainScene::~MainScene()
{
    xNotify->removeAllObservers(this);
}

void MainScene::add(float dt)
{
    const char * text = _labelNumber->getStringValue();
    float delay = atof(text);
    delay += 0.05f;
    _labelNumber->setText(any2string(delay));
}

void MainScene::del(float dt)
{
    const char * text = _labelNumber->getStringValue();
    float delay = atof(text);
    delay -= 0.05f;
    _labelNumber->setText(any2string(delay));
}

void MainScene::touchEvent(CCObject *pSender, TouchEventType type)
{
    if(type != TOUCH_EVENT_ENDED && type != TOUCH_EVENT_BEGAN)
    {
        return;
    }
    
    Widget *widget = (Widget*)pSender;
    int iTag = widget->getTag();
    
    
    if (type == TOUCH_EVENT_BEGAN) {
        
        switch (iTag) {
            case BTN_ADD:
            {
                _labelNumber = (UILabel*)UIHelper::seekWidgetByTag((Widget*)widget->getParent(), LABEL_DELAY);
                schedule(schedule_selector(MainScene::add), 0.17, kCCRepeatForever, 1);
            }
                break;
            case BTN_DEL:
            {
                _labelNumber = (UILabel*)UIHelper::seekWidgetByTag((Widget*)widget->getParent(), LABEL_DELAY);
                schedule(schedule_selector(MainScene::del), 0.17, kCCRepeatForever, 1);
            }
                break;
            default:
                break;
        }
        
        return;
    }
    
    switch (iTag) {
        case BUTTON_IMPORT:
        {
            import();
        }
            break;
        case BTN_UP:
        {
            _listTotal->scrollChildren(0, -OFFSET_Y);
        }
            break;
        case BTN_DOWN:
        {
            _listTotal->scrollChildren(0, OFFSET_Y);
        }
            break;
        case BTN_PREVIEW:
        {
            _listPart->changeTotalCount(_count++);

            for (int i = 0; i < _parts.size(); i++) {
                _parts.at(i)->preview();
            }
        }
            break;
        case BTN_DELETE_ALL:
        {
            for (int i = 0; i < _parts.size(); i++) {
                _parts.at(i)->deleteFrames();
            }
        }
            break;
        case BTN_ADD:
        {
            UIButton* btn = (UIButton*)widget;
            UILabel * label = (UILabel*)UIHelper::seekWidgetByTag((Widget*)btn->getParent(), LABEL_DELAY);
            const char * text = label->getStringValue();
            float delay = atof(text);
            delay += 0.01f;
            label->setText(any2string(delay));
            
            //改变数据
            float *pDelay = (float *)label->getUserData();
            if (pDelay) {
                *pDelay = delay;
            }
            
            unschedule(schedule_selector(MainScene::add));
        }
            break;
        case BTN_DEL:
        {
            UIButton* btn = (UIButton*)widget;
            UILabel * label = (UILabel*)UIHelper::seekWidgetByTag((Widget*)btn->getParent(), LABEL_DELAY);
            const char * text = label->getStringValue();
            float delay = atof(text);
            delay -= 0.01f;
            label->setText(any2string(delay));
            
            //改变数据
            float *pDelay = (float *)label->getUserData();
            if (pDelay) {
                *pDelay = delay;
            }
            
            unschedule(schedule_selector(MainScene::del));
        }
            break;
        case LAYOUT:
        {
            UICheckBox * check = (UICheckBox*)UIHelper::seekWidgetByTag(widget, CHECK_BOX);
            
            bool bCheck = !(check->getSelectedState());
            check->setSelectedState(bCheck);
            
            bool * pDeleted = (bool *)check->getUserData();
            *pDeleted = !check->getSelectedState();
            
            break;
        }
        case LAYOUT_TEST:
        {
            _listPart->requestUpdateView();

            break;
        }
        default:
        {
        }
            break;
    }
}

void MainScene::onCheckBox(CCObject* sender, CheckBoxEventType type)
{
    //获得数据
    UICheckBox *check = (UICheckBox*)sender;
    bool * pDeleted = (bool *)check->getUserData();
    *pDeleted = !check->getSelectedState();
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
    if (editBox == _inputDelay->m_edit) {
        for(int j = 0; j < _parts.size(); j++)
        {
            for(int i = 0; i < _parts.at(j)->m_vFrameOriginal.size(); i++)
            {
                _parts.at(j)->m_vFrameOriginal.at(i).fDelay = atof(text.c_str());
            }
        }
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

        //以下为测试代码
        UIListView * listPart = UIListView::create(30, 7, listviewupdateselector(MainScene::updateCellAtIndex));
        listPart->setSize(CCSizeMake(1920, SIDE_LEN));
        listPart->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        listPart->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        listPart->setItemsMargin(20);
        listPart->setTarget(this);
        listPart->requestInitialization();
        _listPart = listPart;

        _listTotal->pushBackCustomItem(listPart);

        return;
    }
    
    //获取part
    Part * part;
    
    if (_parts.size() == 0) {
        //第一个part, 特殊处理
        part = new Part(_preview);
        _parts.push_back(part);
    }
    else
    {
        //创建一个Sprite
        CCSprite* preview = CCSprite::create();
        preview->setPosition(_preview->getPosition());
        _preview->getParent()->addChild(preview);
        
        part = new Part(preview);
        _parts.push_back(part);
    }

    part->import(input->getText());

    vector<MyFrame> &vFrameName = part->m_vFrameOriginal;
    
    UIListView * listPart = UIListView::create(vFrameName.size(), listviewupdateselector(MainScene::updateCellAtIndex));
    listPart->setSize(CCSizeMake(1920, SIDE_LEN));
    listPart->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    listPart->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
    listPart->setTarget(this);
    listPart->setUserData((void*)part);
    listPart->requestInitialization();
    
    _listTotal->pushBackCustomItem(listPart);
    
    //增加起始帧
    Layout * layout_delay = (Layout*)_delayPanel->clone();
    layout_delay->setVisible(true);
    layout_delay->setPosition(ccp(_posDelayPanel.x, _posDelayPanel.y - _parts.size() * layout_delay->getContentSize().height * 1.3));
    
    UILabel * label = (UILabel*)UIHelper::seekWidgetByTag(layout_delay, LABEL_DELAY);
    label->setText("0");
    
    initButton(BTN_ADD, layout_delay, this, toucheventselector(MainScene::touchEvent));
    initButton(BTN_DEL, layout_delay, this, toucheventselector(MainScene::touchEvent));

    _delayPanel->getParent()->addChild(layout_delay);
    _layouts.push_back(layout_delay);
    
    //设置binding的List
    part->setBindingList(listPart, label);
}

#if 0
void MainScene::updateCellAtIndex(CCObject* list, const CCPoint &indexes, const bool &created, Widget *item)
{
    int index = indexes.x + indexes.y;

    Layout * layout;

    if(created)
    {
        layout = Layout::create();
        layout->setContentSize(CCSizeMake(SIDE_LEN, SIDE_LEN));
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setSize(CCSizeMake(SIDE_LEN, SIDE_LEN));

        UILabel * label = (UILabel*)UILabel::create();

        label->setText(any2string(index));
        label->setFontSize(60);
        label->setPosition(ccp(layout->getContentSize().width/2, layout->getContentSize().height/2));
        layout->addChild(label);
        layout->setTag(LAYOUT_TEST);
        layout->setTouchEnabled(true);
        layout->addTouchEventListener(this, toucheventselector(MainScene::touchEvent));

        ((UIListView*)list)->updateCustomItem(layout);
    }
    else
    {
        layout = (Layout *)item;
    }


    if(index == ((UIListView*)list)->getCurSelectedIndex())
    {
        layout->setBackGroundColor(ccGRAY);
    }
    else
        layout->setBackGroundColor(ccBLACK);
}
#else
void MainScene::updateCellAtIndex(CCObject* list, const CCPoint &indexes, const bool &created, Widget *item)
{
    UIListView* listview = (UIListView*)list;
    Part *part = (Part*)listview->getUserData();
    vector<MyFrame> &vFrameName = part->m_vFrameOriginal;
    
    Layout * layout = Layout::create();
    layout->setContentSize(CCSizeMake(SIDE_LEN, SIDE_LEN));
    layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
    layout->setBackGroundColor(ccBLACK);
    layout->setSize(CCSizeMake(SIDE_LEN, SIDE_LEN));
    layout->setTouchEnabled(true);
    layout->setTag(LAYOUT);
    layout->addTouchEventListener(this, toucheventselector(MainScene::touchEvent));
    
    UIImageView * image = UIImageView::create();
    image->loadTexture(vFrameName.at(indexes.x).sFrameName.c_str(), UI_TEX_TYPE_PLIST);
    image->setPosition(ccp(SIDE_LEN/2, SIDE_LEN/2));
    image->setScale(0.5);
    
    UICheckBox * checkOne = (UICheckBox*)check->clone();
    checkOne->setVisible(true);
    checkOne->setScale(0.5);
    checkOne->setPosition(ccp(SIDE_LEN - 20, SIDE_LEN - 20));
    checkOne->setSelectedState(!part->m_vFrameOriginal.at(indexes.x).bDeleted);
    checkOne->addEventListenerCheckBox(this, checkboxselectedeventselector(MainScene::onCheckBox));
    bool * pDeleted = &(part->m_vFrameOriginal.at(indexes.x).bDeleted);
    checkOne->setUserData((void*)pDeleted);
    
    Layout * layout_delay = (Layout*)_delayPanel->clone();
    layout_delay->setVisible(true);
    layout_delay->setPosition(ccp(SIDE_LEN/2 - layout_delay->getContentSize().width / 2, 0));
    
    UILabel * label = (UILabel*)UIHelper::seekWidgetByTag(layout_delay, LABEL_DELAY);
    label->setText(any2string(part->m_vFrameOriginal.at(indexes.x).fDelay));
    float * pDelay = &(part->m_vFrameOriginal.at(indexes.x).fDelay);
    label->setUserData((void*)pDelay);
    
    initButton(BTN_ADD, layout_delay, this, toucheventselector(MainScene::touchEvent));
    initButton(BTN_DEL, layout_delay, this, toucheventselector(MainScene::touchEvent));
    
    
    layout->addChild(image);
    layout->addChild(checkOne);
    layout->addChild(layout_delay, 10);
    
    ((UIListView*)list)->updateCustomItem(layout);
}
#endif