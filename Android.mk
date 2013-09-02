LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

CPP_FILES = $(subst $(1)/,,$(wildcard $(1)/*.cpp))

LOCAL_MODULE := AMazed

LOCAL_SRC_FILES := $(call CPP_FILES,$(LOCAL_PATH))

# aditional cpp files
#LOCAL_SRC_FILES += math/Plane.cpp
#LOCAL_SRC_FILES += math/BoundingBox.cpp
#LOCAL_SRC_FILES += math/Frustrum.cpp
#LOCAL_SRC_FILES += math/Camera.cpp

#LOCAL_SRC_FILES += scene/Node.cpp
#LOCAL_SRC_FILES += scene/TransformationNode.cpp

LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2 #-lGLESv1_CM #-lOpenSLES

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)

