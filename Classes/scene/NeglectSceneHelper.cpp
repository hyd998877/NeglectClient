//
//  NeglectSceneHelper.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "NeglectSceneHelper.h"

#include "StartScene.h"
#include "MyPageScene.h"
#include "QuestListScene.h"
#include "QuestStartScene.h"
#include "QuestPlayScene.h"

cocos2d::Scene* NeglectSceneHelper::createScene(SceneID sceneID)
{
    cocos2d::Scene* scene = nullptr;
    switch (sceneID) {
        case START:
            scene = createScene<StartScene>();
            break;
        case MY_PAGE:
            scene = createScene<MyPageScene>();
            break;
        case QUEST_LIST:
            scene = createScene<QuestListScene>();
            break;
        case QUEST_DETAIL:
            scene = createScene<QuestStartScene>();
            break;
        case QUEST_PLAY:
            scene = createScene<QuestPlayScene>();
            break;
        default:
            break;
    }
    return scene;
}

void NeglectSceneHelper::replaceScene(SceneID sceneID)
{
    cocos2d::Director::getInstance()->replaceScene(NeglectSceneHelper::createScene(sceneID));
}
