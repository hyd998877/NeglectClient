//
//  ApplicationUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/24.
//
//

#ifndef NeglecClient_ApplicationUtil_h
#define NeglecClient_ApplicationUtil_h

#include "base/CCValue.h"
#include "platform/CCFileUtils.h"

// TODO: 一旦平文で保存してるけど、いずれ暗号化とかする
class ApplicationUtil
{
public:
    static void saveData(const std::string &uuid) {
        cocos2d::ValueMap saveData{
            {"uuid", cocos2d::Value(uuid)},
        };
        cocos2d::FileUtils::getInstance()->writeToFile(saveData, createSaveFilePath());
    }
    static cocos2d::ValueMap loadData() {
        std::string saveFilePath = createSaveFilePath();
        CCLOG("%s %d load %s ", __FILE__, __LINE__, saveFilePath.c_str());
        
        auto saveData = cocos2d::FileUtils::getInstance()->getValueMapFromFile(saveFilePath);
        return saveData;
    }
private:
    static std::string createSaveFilePath() {
        return cocos2d::FileUtils::getInstance()->getWritablePath() + "save_data.plist";
    }
    
    static void remoteSaveFile() {
        std::string saveFilePath = createSaveFilePath();
        remove(saveFilePath.c_str());
    }
};

#endif
