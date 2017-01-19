//
// Created by dwd on 05/11/15.
//

/*
 * Copyright 2015 Surevine Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * (These are the standard Surevine/MIT terms)
 */

#include "com_surevine_spiffing_Label.h"
#include "handle.h"
#include "base64.h"
#include "exception.h"
#include <spiffing/label.h>
#include <spiffing/spif.h>

#include <iostream>

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    displayMarking
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Label_displayMarking
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jobj);
        Spiffing::Spif const & spif = label->policy();
        std::string dm = spif.displayMarking(*label, Spiffing::MarkingCode::pageTop);
        return jenv->NewStringUTF(dm.c_str());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    fgColour
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Label_fgColour
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jobj);
        return jenv->NewStringUTF(label->classification().fgcolour().c_str());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    bgColour
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Label_bgColour
        (JNIEnv * jenv, jobject) {
    return nullptr;
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_surevine_spiffing_Label_init
        (JNIEnv * jenv, jobject jobj, jstring jbase64) {
    try {
        auto deleter = [&jbase64, &jenv](const char * d) {
            jenv->ReleaseStringUTFChars(jbase64, d);
        };
        std::unique_ptr<const char, decltype(deleter)> base64(jenv->GetStringUTFChars(jbase64, nullptr), deleter);
        std::size_t base64_len = jenv->GetStringLength(jbase64);
        std::cerr << "Decoding " << base64_len << " bytes of base64." << std::endl;
        std::cerr << "Data is " << &*base64 << std::endl;
        std::string labelstr = base64_decode(std::string{&*base64, base64_len});
        std::cerr << "-> Into " << labelstr.length() << " bytes of BER." << std::endl;
        Spiffing::Label * label = new Spiffing::Label(labelstr, Spiffing::Format::BER);
        setHandle(jenv, jobj, label);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    dispose_n
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_surevine_spiffing_Label_dispose_1n
        (JNIEnv * jenv, jobject jobj) {
    Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jobj);
    delete label;
    setHandle<Spiffing::Label>(jenv, jobj, nullptr);
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    policy_n
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_surevine_spiffing_Label_policy_1n
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jobj);
        return reinterpret_cast<jlong>(&label->policy());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    valid
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_surevine_spiffing_Label_valid
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jobj);
        Spiffing::Spif const & spif = label->policy();
        return spif.valid(*label);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }

}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    fgColour
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Label_toESSBase64
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Label *label = getHandle<Spiffing::Label>(jenv, jobj);
        std::string out;
        label->write(Spiffing::Format::BER, out);
        std::string labelstr = base64_encode(reinterpret_cast<const unsigned char *>(out.c_str()), out.length());
        return jenv->NewStringUTF(labelstr.c_str());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    fgColour
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Label_toNATOXML
        (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Label *label = getHandle<Spiffing::Label>(jenv, jobj);
        std::string out;
        label->write(Spiffing::Format::NATO, out);
        std::string labelstr = base64_encode(reinterpret_cast<const unsigned char *>(out.c_str()), out.length());
        return jenv->NewStringUTF(labelstr.c_str());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Label
 * Method:    encrypt
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jlong JNICALL Java_com_surevine_spiffing_Label_encryptn
        (JNIEnv * jenv, jobject jobj, jstring jstr) {
    try {
        auto deleter = [&jstr, &jenv](const char * d) {
            jenv->ReleaseStringUTFChars(jstr, d);
        };
        std::unique_ptr<const char, decltype(deleter)> str(jenv->GetStringUTFChars(jstr, nullptr), deleter);
        std::string policy_id{&*str};
        Spiffing::Label * label = getHandle<Spiffing::Label>(jenv, jobj);
        std::unique_ptr<Spiffing::Label> newl = label->encrypt(policy_id);
        return reinterpret_cast<jlong>(newl.release());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}