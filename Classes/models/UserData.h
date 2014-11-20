//
//  UserData.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/15.
//
//

#ifndef NeglecClient_UserData_h
#define NeglecClient_UserData_h

#include <vector>
#include "json11.hpp"

namespace UserData {
    
    struct TAccount {
        int64_t accountID;
        std::string UUID; // TODO: 送らないようにする?
        std::string name;
        std::string description;
    };
    
    struct TAccountStatus {
        int64_t accountID;
        int lv;
        int exp;
        int hp;
        int maxHp;
        int mp;
        int maxMp;
        int equipItem1ID;
        int equipItem2ID;
        int equipItem3ID;
        int equipItem4ID;
    };
//    TAccountStatus tAccountStatus;
    
    struct TStorageItem {
        int64_t accountID;
        int itemID;
        int seqNo;
    };
//    std::vector<TStorageItem> tStorageItem;
    
    struct TUserItem {
        int64_t accountID;
        int itemID;
        int seqNo;
    };
//    std::vector<TUserItem> tUserItem;

    struct TPlayQuest {
        int64_t accountID;
        int questID;
        int floorCount;
        int64_t startTime;
        int64_t endTime;
    };
//    TPlayQuest tPlayQuest;
    
    struct TPlayQuestLog {
        int64_t accountID;
        int questID;
        int seqID;
        std::string message;
    };
//    std::vector<TPlayQuestLogs> tPlayQuestLogs;
    
    template <typename T>
    static T create(json11::Json item) {
        assert(false);
    }

    template<>
    TAccount create(json11::Json item) {
        TAccount data;
        
        data.accountID    = item["AccountID"].number_value();
        data.UUID    = item["UUID"].string_value();
        data.name    = item["Name"].string_value();
        data.description = item["Description"].string_value();
        
        return data;
    }
    
    template<>
    TAccountStatus create(json11::Json item) {
        TAccountStatus data;
        
        data.accountID    = item["AccountID"].int_value();
        data.lv    = item["Lv"].int_value();
        data.exp    = item["Exp"].int_value();
        data.hp    = item["Hp"].int_value();
        data.maxHp = item["MaxHp"].int_value();
        data.mp    = item["Mp"].int_value();
        data.maxMp = item["MaxMp"].int_value();
        data.equipItem1ID = item["EquipItem1ID"].int_value();
        data.equipItem2ID = item["EquipItem2ID"].int_value();
        data.equipItem3ID = item["EquipItem3ID"].int_value();
        data.equipItem4ID = item["EquipItem4ID"].int_value();
        
        return data;
    }
    
    template<>
    TPlayQuest create(json11::Json item) {
        TPlayQuest data;
        
        data.accountID  = item["AccountID"].number_value();
        data.questID    = item["QuestID"].int_value();
        data.floorCount = item["FloorCount"].int_value();
        data.startTime  = item["StartTime"].number_value();
        data.endTime    = item["EndTime"].number_value();
        
        return data;
    }
};

#endif
