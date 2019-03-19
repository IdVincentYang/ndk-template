#include "native-activity.hxx"

extern "C" JNIEXPORT
void ANativeActivity_onCreate(ANativeActivity *native, void *savedState, size_t savedStateSize) {
    NativeActivity *activity = new NativeActivity(native);
    activity->create(savedState, savedStateSize);
    native->instance = activity;
}
