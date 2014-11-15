//
//  NeglectSceneHelper.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__NeglectSceneHelper__
#define __NeglecClient__NeglectSceneHelper__

#include "cocos2d.h"

class NeglectSceneHelper
{
public:
    enum SceneID {
        MY_PAGE,
        QUEST_LIST,
        QUEST_DETAIL,
        QUEST_PLAY,
    };

    static cocos2d::Scene* createScene(SceneID sceneID);
    
    static void replaceScene(SceneID sceneID);
    
    template<typename T>
    static cocos2d::Scene* createScene()
    {
        // 'scene' is an autorelease object
        auto scene = cocos2d::Scene::create();
        
        // 'layer' is an autorelease object
        auto layer = T::create();
        layer->setName("SceneLayer");
        
        // add layer as a child to scene
        scene->addChild(layer);
        
        // return the scene
        return scene;
    }
private:
    
};

#endif /* defined(__NeglecClient__NeglectSceneHelper__) */
