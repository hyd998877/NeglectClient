//
//  UUIDUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/24.
//
//

#ifndef NeglecClient_UUIDUtil_h
#define NeglecClient_UUIDUtil_h

#include <string>
#include <uuid/uuid.h>

namespace UUIDUtil {
    std::string generateUUID() {
        uuid_t value;
        uuid_string_t uuidStr;
        uuid_generate(value);
        uuid_unparse_upper(value, uuidStr);
        return std::string(uuidStr);
    }
}

#endif
