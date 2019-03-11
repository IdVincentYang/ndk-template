#pragma once

#include <android/native_activity.h>

class NativeActivity {
public:
    NativeActivity(ANativeActivity *native);

    virtual ~NativeActivity();

    virtual void create(void *savedState, size_t savedStateSize);

    virtual void onCreate(void *savedState, size_t savedStateSize);

    virtual void onStart();

    virtual void onResume();

    virtual void *onSaveInstanceState(size_t *outSize);

    virtual void onPause();

    virtual void onStop();

    virtual void onDestroy();

    virtual void onWindowFocusChanged(int hasFocus);

    virtual void onNativeWindowCreated(ANativeWindow *window);

    virtual void onNativeWindowResized(ANativeWindow *window);

    virtual void onNativeWindowRedrawNeeded(ANativeWindow *window);

    virtual void onNativeWindowDestroyed(ANativeWindow *window);

    virtual void onInputQueueCreated(AInputQueue *queue);

    virtual void onInputQueueDestroyed(AInputQueue *queue);

    virtual void onContentRectChanged(const ARect *rect);

    virtual void onConfigurationChanged();

    virtual void onLowMemory();

protected:

    ANativeActivity *_native {nullptr};
};
