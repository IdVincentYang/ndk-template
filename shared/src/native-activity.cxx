#include "native-activity.hxx"

#include "pal-log.hxx"

#define _LD(...)  PAL_LOG_D("native-lib", __VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////////////////////////
//  local

static void _on_start(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onStart();
}

static void _on_resume(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onResume();
}

static void *_on_save_instance_state(ANativeActivity *native, size_t *out_size) {
    return ((NativeActivity *) native->instance)->onSaveInstanceState(out_size);
}

static void _on_pause(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onPause();
}

static void _on_stop(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onStop();
}

static void _on_destroy(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onDestroy();
}

static void on_window_focus_changed(ANativeActivity *native, int has_focus) {
    ((NativeActivity *) native->instance)->onWindowFocusChanged(has_focus);
}

static void on_native_window_created(ANativeActivity *native, ANativeWindow *window) {
    ((NativeActivity *) native->instance)->onNativeWindowCreated(window);
}

static void on_native_window_resized(ANativeActivity *native, ANativeWindow *window) {
    ((NativeActivity *) native->instance)->onNativeWindowResized(window);
}

static void on_native_window_redraw_needed(ANativeActivity *native, ANativeWindow *window) {
    ((NativeActivity *) native->instance)->onNativeWindowRedrawNeeded(window);
}

static void on_native_window_destroyed(ANativeActivity *native, ANativeWindow *window) {
    ((NativeActivity *) native->instance)->onNativeWindowDestroyed(window);
}

static void on_input_queue_created(ANativeActivity *native, AInputQueue *queue) {
    ((NativeActivity *) native->instance)->onInputQueueCreated(queue);
}

static void on_input_queueDestroyed(ANativeActivity *native, AInputQueue *queue) {
    ((NativeActivity *) native->instance)->onInputQueueDestroyed(queue);
}

static void on_content_rect_changed(ANativeActivity *native, const ARect *rect) {
    ((NativeActivity *) native->instance)->onContentRectChanged(rect);
}

static void on_configuration_changed(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onConfigurationChanged();
}

static void on_low_memory(ANativeActivity *native) {
    ((NativeActivity *) native->instance)->onLowMemory();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  static

////////////////////////////////////////////////////////////////////////////////////////////////////
//  public

NativeActivity::NativeActivity(ANativeActivity *native)
        : _native(native) {
    _LD("call: %s", __PRETTY_FUNCTION__);
    ANativeActivityCallbacks *cbs = native->callbacks;
    cbs->onStart = _on_start;
    cbs->onResume = _on_resume;
    cbs->onSaveInstanceState = _on_save_instance_state;
    cbs->onPause = _on_pause;
    cbs->onStop = _on_stop;
    cbs->onDestroy = _on_destroy;
    cbs->onWindowFocusChanged = on_window_focus_changed;
    cbs->onNativeWindowCreated = on_native_window_created;
    cbs->onNativeWindowResized = on_native_window_resized;
    cbs->onNativeWindowRedrawNeeded = on_native_window_redraw_needed;
    cbs->onNativeWindowDestroyed = on_native_window_destroyed;
    cbs->onInputQueueCreated = on_input_queue_created;
    cbs->onInputQueueDestroyed = on_input_queueDestroyed;
    cbs->onContentRectChanged = on_content_rect_changed;
    cbs->onConfigurationChanged = on_configuration_changed;
    cbs->onLowMemory = on_low_memory;
}

NativeActivity::~NativeActivity() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::create(void *savedState, size_t savedStateSize) {
    _LD("call: %s", __PRETTY_FUNCTION__);
    this->onCreate(savedState, savedStateSize);
}

void NativeActivity::onCreate(void *savedState, size_t savedStateSize) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onStart() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onResume() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void *NativeActivity::onSaveInstanceState(size_t *outSize) {
    _LD("call: %s", __PRETTY_FUNCTION__);
    return nullptr;
}

void NativeActivity::onPause() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onStop() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onDestroy() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onWindowFocusChanged(int hasFocus) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onNativeWindowCreated(ANativeWindow *window) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onNativeWindowResized(ANativeWindow *window) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onNativeWindowRedrawNeeded(ANativeWindow *window) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onNativeWindowDestroyed(ANativeWindow *window) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onInputQueueCreated(AInputQueue *queue) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onInputQueueDestroyed(AInputQueue *queue) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onContentRectChanged(const ARect *rect) {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onConfigurationChanged() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}

void NativeActivity::onLowMemory() {
    _LD("call: %s", __PRETTY_FUNCTION__);
}
