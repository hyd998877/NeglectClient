//
//  QuestPlayScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/30.
//
//

#ifndef __NeglecClient__QuestPlayScene__
#define __NeglecClient__QuestPlayScene__

#include "cocos2d.h"

class QuestPlayScene : public cocos2d::Layer
{
public:
    QuestPlayScene();
    virtual ~QuestPlayScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(QuestPlayScene);
    
private:
    void initView();
    void requestPlayingQuest();
    
    // view
    void setTextQuestDetail(int floorCount, int hour, int minute);
    void setTextStatus(int lv, int hp, int maxHp, int mp, int maxMp);
    void setTextLogMessage(const std::string &message);
private:
    cocos2d::Node *_baseLayout;
};

#endif /* defined(__NeglecClient__QuestPlayScene__) */
