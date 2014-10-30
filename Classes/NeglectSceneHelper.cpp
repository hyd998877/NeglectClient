//
//  NeglectSceneHelper.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "NeglectSceneHelper.h"

#include "MyPageScene.h"
#include "QuestListScene.h"
#include "QuestStartScene.h"
#include "QuestPlayScene.h"

cocos2d::Scene* NeglectSceneHelper::createScene(SceneID sceneID)
{
    switch (sceneID) {
        case MY_PAGE:
            return createScene<MyPageScene>();
        case QUEST_LIST:
            return createScene<QuestListScene>();
        case QUEST_DETAIL:
            return createScene<QuestStartScene>();
        case QUEST_PLAY:
            return createScene<QuestPlayScene>();
        default:
            break;
    }
    return nullptr;
}

void NeglectSceneHelper::replaceScene(SceneID sceneID)
{
    cocos2d::Director::getInstance()->replaceScene(NeglectSceneHelper::createScene(sceneID));
}
