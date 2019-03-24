#include "native-activity.hxx"

#include <cassert>
#include <android/sensor.h>
#include "pal-log.hxx"

#define _LV(...)    PAL_LOG_V("app-input-queue", __VA_ARGS__)
#define _LD(...)    PAL_LOG_D("app-input-queue", __VA_ARGS__)

const int EVENT_TYPE_ID_INPUT = 0x11;
const int EVENT_TYPE_ID_SENSOR_ACCELEROMETER = 0x12;

static ASensorManager *_get_sensor_manager_instance(ANativeActivity *);

class MyActivity : public NativeActivity {
    typedef NativeActivity Super;
public:
    MyActivity(ANativeActivity *native)
            : NativeActivity(native), _inputQueue(nullptr), _accSensor(nullptr),
              _accQueue(nullptr) {

    }

////////////////////////////////////////////////////////////////////////////////
//  begin: deal with accelerometer sensor
    virtual void onCreate(void *savedState, size_t savedStateSize) override {
        Super::onCreate(savedState, savedStateSize);

        ALooper *looper = ALooper_forThread();
        ASensorManager *sensorManager = _get_sensor_manager_instance(_native);
        ALooper_callbackFunc cb = [](int fd, int events, void *data) -> int {
            _LV("_acc_sensor_callback(fd: %d, events: %d, data: %p", fd, events, data);
            MyActivity *activity = (MyActivity *) (data);
            activity->onAccSensorEventCallback();
            return 1;   // return 1 mean's continue receive callback
        };

        _accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
        _accQueue = ASensorManager_createEventQueue(sensorManager, looper,
                                                    EVENT_TYPE_ID_SENSOR_ACCELEROMETER, cb, this);
    }

    virtual void onDestroy() override {
        Super::onDestroy();
        ALooper *looper = ALooper_forThread();
        ASensorManager *sensorManager = _get_sensor_manager_instance(_native);
        ASensorManager_destroyEventQueue(sensorManager, _accQueue);
        _accQueue = nullptr;
        _accSensor = nullptr;
    }

    virtual void onWindowFocusChanged(int hasFocus) override {
        Super::onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            ASensorEventQueue_enableSensor(_accQueue, _accSensor);
            // We'd like to get 3 events per second (in us). might not work
            ASensorEventQueue_setEventRate(_accQueue, _accSensor, (1000L / 3) * 1000);
        } else {
            ASensorEventQueue_disableSensor(_accQueue, _accSensor);
        }
    }

    void onAccSensorEventCallback() {
        if (ASensorEventQueue_hasEvents(_accQueue)) {
            _LV("SensorQueue has Event");
            ASensorEvent event;
            ssize_t num = ASensorEventQueue_getEvents(_accQueue, &event, 1);
            if (num) {
                _LV("accelerometer: x=%f y=%f z=%f",
                    event.acceleration.x, event.acceleration.y,
                    event.acceleration.z);
            } else {
                _LV("accelerometer get no events");
            }
            while (ASensorEventQueue_getEvents(_accQueue, &event, 1) > 0) {
                _LV("accelerometer: x=%f y=%f z=%f",
                    event.acceleration.x, event.acceleration.y,
                    event.acceleration.z);
            }
        }
    }

//  end: deal with accelerometer sensor
////////////////////////////////////////////////////////////////////////////////
//  begin: deal with input event
    virtual void onInputQueueCreated(AInputQueue *queue) override {
        NativeActivity::onInputQueueCreated(queue);
        ALooper *looper = ALooper_forThread();
        assert(looper != nullptr && _inputQueue == nullptr);
//        ALooper_addFd(looper, )

        _inputQueue = queue;
        ALooper_callbackFunc cb = [](int fd, int events, void *data) -> int {
            _LV("_looper_callback(fd: %d, events: %d, data: %p", fd, events, data);
            MyActivity *activity = (MyActivity *) (data);
            activity->onInputEventCallback();
            return 1;   // return 1 mean's continue receive callback
        };
        AInputQueue_attachLooper(queue, looper, EVENT_TYPE_ID_INPUT, cb, this);
    }

    virtual void onInputQueueDestroyed(AInputQueue *queue) override {
        NativeActivity::onInputQueueDestroyed(queue);
        AInputQueue_detachLooper(queue);
    }

    void onInputEventCallback() {
        if (AInputQueue_hasEvents(_inputQueue)) {
            _LV("InputQueue has Event");
            AInputQueue *queue = _inputQueue;
            AInputEvent *event;
            AInputQueue_getEvent(queue, &event);

            int32_t type = AInputEvent_getType(event);
            switch (type) {
                case AINPUT_EVENT_TYPE_MOTION: {
                    switch (AMotionEvent_getAction(event)) {
                        case AMOTION_EVENT_ACTION_DOWN: {
                            float x = AMotionEvent_getX(event, 0);
                            float y = AMotionEvent_getY(event, 0);
                            _LV("Motion Event(down): X:%f,Y:%f", x, y);
                            break;
                        }
                        case AMOTION_EVENT_ACTION_MOVE: {
                            float x = AMotionEvent_getX(event, 0);
                            float y = AMotionEvent_getY(event, 0);
                            _LV("Motion Event(move): X:%f,Y:%f", x, y);
                            break;
                        }
                        case AMOTION_EVENT_ACTION_UP: {
                            break;
                        }
                    }
                    break;
                }
                case AINPUT_EVENT_TYPE_KEY: {
                    switch (AKeyEvent_getAction(event)) {
                        case AKEY_EVENT_ACTION_DOWN: {
                            switch (AKeyEvent_getKeyCode(event)) {
                                case AKEYCODE_BACK: {
                                    _LV("Key Event(down): BACK");
                                    break;
                                }
                            }
                            break;
                        }
                        case AKEY_EVENT_ACTION_UP: {
                            switch (AKeyEvent_getKeyCode(event)) {
                                case AKEYCODE_BACK: {
                                    _LV("Key Event(up): BACK");
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            AInputQueue_finishEvent(queue, event, true);
        }
    }
//  end: deal with default input event
////////////////////////////////////////////////////////////////////////////////

private:
    //  accelerometer sensor
    const ASensor *_accSensor;
    ASensorEventQueue *_accQueue;
    AInputQueue *_inputQueue;
};

#include <dlfcn.h>

static ASensorManager *_get_sensor_manager_instance(ANativeActivity *native) {
    typedef ASensorManager *(*PF_GETINSTANCEFORPACKAGE)(const char *name);
    void *androidHandle = dlopen("libandroid.so", RTLD_NOW);
    PF_GETINSTANCEFORPACKAGE getInstanceForPackageFunc = (PF_GETINSTANCEFORPACKAGE)
            dlsym(androidHandle, "ASensorManager_getInstanceForPackage");
    if (getInstanceForPackageFunc) {
        JNIEnv *env = native->env;
//        native->vm->AttachCurrentThread(&env, NULL);

        jclass android_content_Context = env->GetObjectClass(native->clazz);
        jmethodID midGetPackageName = env->GetMethodID(android_content_Context,
                                                       "getPackageName",
                                                       "()Ljava/lang/String;");
        jstring packageName = (jstring) env->CallObjectMethod(native->clazz,
                                                              midGetPackageName);

        const char *nativePackageName = env->GetStringUTFChars(packageName, 0);
        ASensorManager *mgr = getInstanceForPackageFunc(nativePackageName);
        env->ReleaseStringUTFChars(packageName, nativePackageName);
//        native->vm->DetachCurrentThread();
        if (mgr) {
            dlclose(androidHandle);
            return mgr;
        }
    }

    typedef ASensorManager *(*PF_GETINSTANCE)();
    PF_GETINSTANCE getInstanceFunc = (PF_GETINSTANCE)
            dlsym(androidHandle, "ASensorManager_getInstance");
    // by all means at this point, ASensorManager_getInstance should be available
    assert(getInstanceFunc);
    dlclose(androidHandle);

    return getInstanceFunc();
}

extern "C" JNIEXPORT
void ANativeActivity_onCreate(ANativeActivity *native, void *savedState, size_t savedStateSize) {
    NativeActivity *activity = new MyActivity(native);
    activity->create(savedState, savedStateSize);
    native->instance = activity;
}
