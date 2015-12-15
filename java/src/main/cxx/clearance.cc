//
// Created by dwd on 19/11/15.
//

#include <spiffing/spif.h>
#include <spiffing/clearance.h>
#include <iostream>
#include "com_surevine_spiffing_Clearance.h"
#include "handle.h"
#include "exception.h"
#include "base64.h"

/*
 * Class:     com_surevine_spiffing_Clearance
 * Method:    displayMarking
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Clearance_displayMarking
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Clearance * clearance = getHandle<Spiffing::Clearance>(jenv, jobj);
        Spiffing::Spif const & spif = clearance->policy();
        std::string dm = spif.displayMarking(*clearance);
        return jenv->NewStringUTF(dm.c_str());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Clearance
 * Method:    dominates
 * Signature: (Lcom/surevine/spiffing/Label;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_surevine_spiffing_Clearance_dominates
        (JNIEnv * jenv, jobject jclr, jobject jlbl) {
    try {
        Spiffing::Clearance * clearance = getHandle<Spiffing::Clearance>(jenv, jclr);
        Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jlbl);
        Spiffing::Spif const & spif = clearance->policy();
        return spif.acdf(*label, *clearance);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Clearance
 * Method:    policy_native
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_surevine_spiffing_Clearance_policy_1native
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Clearance * clearance = getHandle<Spiffing::Clearance>(jenv, jobj);
        return reinterpret_cast<jlong>(&clearance->policy());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Clearance
 * Method:    init
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_surevine_spiffing_Clearance_init
        (JNIEnv * jenv, jobject jobj, jstring jbase64) {
    try {
        auto deleter = [&jbase64, &jenv](const char * d) {
            jenv->ReleaseStringUTFChars(jbase64, d);
        };
        std::unique_ptr<const char, decltype(deleter)> base64(jenv->GetStringUTFChars(jbase64, nullptr), deleter);
        std::size_t base64_len = jenv->GetStringLength(jbase64);
        std::cerr << "Decoding " << base64_len << " bytes of base64." << std::endl;
        std::cerr << "Data is " << &*base64 << std::endl;
        std::string clrstr = base64_decode(std::string{&*base64, base64_len});
        std::cerr << "-> Into " << clrstr.length() << " bytes of BER." << std::endl;
        Spiffing::Clearance * clr = new Spiffing::Clearance(clrstr, Spiffing::Format::BER);
        setHandle(jenv, jobj, clr);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Clearance
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_surevine_spiffing_Clearance_dispose
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Clearance * clr = getHandle<Spiffing::Clearance>(jenv, jobj);
        delete clr;
        setHandle<Spiffing::Clearance>(jenv, jobj, nullptr);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}
