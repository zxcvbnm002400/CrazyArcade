#ifndef __SCENE_LOADINGSCENE_H__
#define __SCENE_LOADINGSCENE_H__

#include "cocos2d.h"
#include "Scene/StartScene.h"
#include "ui/CocosGUI.h"

class LoadingScene : public cocos2d::Layer
{
private:
    void endLoading(float dt);
    cocos2d::ui::LoadingBar* createLoadingBar();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
};

#endif // __SCENE_LOADINGSCENE_H__