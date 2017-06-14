#include "RoomScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene/UI/RoleBox.h"
#include "Scene/GameScene.h"
#include "Scene/StartScene.h"
#include "Settings.h"

USING_NS_CC;

/*to do */
/*the back button*/
/*the case of the players*/

Scene* RoomScene::createScene()
{
	//scene is an auto release object 
	auto scene = Scene::create();

	//layer is an auto release object
	auto layer = RoomScene::create();

	//add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}

bool RoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    // room controller
    roomController = RoomController::create();
    addChild(roomController);
    // ready button callback
    readyButtonCallBack = CC_CALLBACK_1(RoomController::onUserChangeStats, roomController);
   
    createUI();
	return true;
}

void RoomScene::createUI()
{
    createReadyButton();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //the title
    auto label = Label::createWithTTF("ROOM", Settings::Font::Type::title, Settings::Font::Size::label);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
    label->enableGlow(Color4B::BLUE);
    this->addChild(label, 1);

    //static node
    Sprite * bg = Sprite::create("RoomScene/bg03.jpg");
    bg->setScale(1.25f);
    bg->setLocalZOrder(-1);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(bg);

    initUserBox();
    std::string roleDefault = "Player";
    for (int i = 1; i <= 2; i++)
    {
        auto box = RoleBox::create(roleDefault + StringUtils::format("%d", i), i);
        roleBox.pushBack(box);
        this->addChild(box);
    }

    auto mouseListener = cocos2d::EventListenerMouse::create();

    mouseListener->onMouseUp = [=](Event* event)
    {
        EventMouse* e = (EventMouse*)event;
        auto touch = e->getLocation();
        for (int i = 0; i < roleBox.size(); i++)
        {
            auto range = (roleBox.at(i))->getBound();
            if (range.containsPoint(touch))
            {
                // TODO
            }
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    addChild(createText());
}

void RoomScene::createReadyButton()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto getShowText = [](bool isReady)
    {
        return isReady ? "Cancel" : "Ready";
    };
    static bool isReady = false;
    readyButton = ui::Button::create("RoomScene/button_normal.png", "RoomScene/button_selected.png");
    readyButton->setTitleText(getShowText(isReady));
    readyButton->setTitleFontSize(Settings::Font::Size::normal);
    readyButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            auto button = static_cast<ui::Button*>(sender);
            isReady = !isReady;
            button->setTitleText(getShowText(isReady));
            if (readyButtonCallBack) readyButtonCallBack(isReady);
        }
    });

    readyButton->setPosition(Vec2(visibleSize.width*0.4f + readyButton->getContentSize().width, visibleSize.height*0.1f));
    this->addChild(readyButton);
}

void RoomScene::onExit()
{
    Layer::onExit();
}

cocos2d::Menu* RoomScene::createText() {
	const auto buttons = Menu::create();

	const auto backButton = MenuItemLabel::create(
		Label::createWithTTF("Back", Settings::Font::Type::base, Settings::Font::Size::label),
		CC_CALLBACK_1(RoomScene::menuBackCallback, this));

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto baseY = visibleSize.height * 0.85f;

	backButton->setPosition(backButton->getContentSize().width / 2 + 30, baseY + 30);

	buttons->addChild(backButton, 1);

	buttons->setPosition(0, 0);

	return buttons;
}

void RoomScene::menuBackCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void RoomScene::initUserBox()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (int i = 1; i < 9; ++i)
    {
        auto userBox = Sprite::create("RoomScene/roomcase_01.png");
        if (i < 5)
        {
            userBox->setPosition(Vec2(userBox->getContentSize().width * i * 1.25 - userBox->getContentSize().width * 0.5f,
                visibleSize.height*0.68f));
        }
        else
        {
            userBox->setPosition(Vec2(userBox->getContentSize().width * (i - 4)* 1.25 - userBox->getContentSize().width *0.5f
                , visibleSize.height *0.68f - userBox->getContentSize().height * 1.28));
        }
        userBox->setScale(1.25);
        userBoxes.pushBack(userBox);
        this->addChild(userBox);
    }
}
