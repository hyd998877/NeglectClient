LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

ifeq ($(HOST_OS),windows)
  CPP_FILES := $(shell dir $(LOCAL_PATH)/../../Classes/*.cpp /b/a-d/s)                   
else
  CPP_FILES := $(shell find $(LOCAL_PATH)/../../Classes -name *.cpp)                   
endif

LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)

#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

ifeq ($(HOST_OS),windows)
  LOCAL_C_INCLUDES := $(shell dir $(LOCAL_PATH)/../../Classes /b/ad/s)                   
else
  LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)                   
endif

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
