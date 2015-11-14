//
// Created by dwd on 14/11/15.
//

#ifndef SPIFFING_JNI_CXX_EXCEPTION_H
#define SPIFFING_JNI_CXX_EXCEPTION_H

#include <stdexcept>
#include <jni.h>

namespace SpiffingJNI {
    void throwJava(JNIEnv * jenv, std::runtime_error const &e);
}

#endif //SPIFFING_JNI_CXX_EXCEPTION_H
