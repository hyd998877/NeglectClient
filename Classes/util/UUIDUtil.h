//
//  UUIDUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/24.
//
//

#ifndef NeglecClient_UUIDUtil_h
#define NeglecClient_UUIDUtil_h

#include "sole.hpp"

namespace UUIDUtil {
    std::string generateUUID() {
        auto u0 = sole::uuid0();
        return u0.str();
    }
}

#endif
