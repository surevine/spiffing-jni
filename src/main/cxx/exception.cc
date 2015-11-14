//
// Created by dwd on 14/11/15.
//

#include <jni.h>
#include "exception.h"

void SpiffingJNI::throwJava(JNIEnv * jenv, std::runtime_error const & e) {
    jclass exClass;
    const char * className = "com/surevine/spiffing/SIOException";

    exClass = jenv->FindClass(className);
    if (!exClass) throw std::runtime_error("Exception class not found.");

    jenv->ThrowNew(exClass, e.what());
}