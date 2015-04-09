LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
$(LOCAL_PATH)/../SDL_ttf \
$(LOCAL_PATH)/../SDL_image \
$(LOCAL_PATH)/../SDL_mixer

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(patsubst $(LOCAL_PATH)/%, %, $(wildcard $(LOCAL_PATH)/src/*.cpp)) \
	$(patsubst $(LOCAL_PATH)/%, %, $(wildcard $(LOCAL_PATH)/src/*.c)) \
	main.cpp

LOCAL_SHARED_LIBRARIES := SDL2 \
	SDL2_image \
	SDL2_ttf \
	SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
