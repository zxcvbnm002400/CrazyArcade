#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"

class StartScene :
    public cocos2d::Layer
{
private:
    bool musicOn = true;    
    cocos2d::Menu* createText();
    void menuCloseCallback(cocos2d::Ref* pSender);
    cocos2d::Menu* musicInit();
    void musicPP(cocos2d::Ref* pSender);    //play or pause the music
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);                
};

#endif // __START_SCENE_H__
