LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Bubble.cpp \
                   ../../Classes/Bullet.cpp \
				   ../../Classes/Collider.cpp \
                   ../../Classes/ColliderManager.cpp \
                   ../../Classes/ConstVars.cpp \
                   ../../Classes/cppson.cpp \
                   ../../Classes/CreditScene.cpp \
                   ../../Classes/EndingScene.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/Explosion.cpp \
                   ../../Classes/FileStuff.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GameManager.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/IntroScene.cpp \
                   ../../Classes/jsoncpp.cpp \
                   ../../Classes/LightMangager.cpp \
                   ../../Classes/MainScene.cpp\
                   ../../Classes/MapEditer.cpp\
                   ../../Classes/MapEditLayer.cpp\
                   ../../Classes/Mirror.cpp\
                   ../../Classes/Sling.cpp\
                   ../../Classes/StageInformation.cpp\
                   ../../Classes/StageScene.cpp\
                   ../../Classes/stdafx.cpp\
                   ../../Classes/Stone.cpp\
                   ../../Classes/Target.cpp\
                   ../../Classes/Targetmanager.cpp\
                   ../../Classes/UILayer.cpp\
                   ../../Classes/Virtical_Mirror.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

LOCAL_CPPFLAGS += -std=c++11