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

#include "com_surevine_spiffing_Site.h"
#include "handle.h"
#include "exception.h"
#include <spiffing/spiffing.h>
#include <fstream>

/*
 * Class:     com_surevine_spiffing_Site
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_surevine_spiffing_Site_init
(JNIEnv * jenv, jobject jobj) {
    try {
        setHandle(jenv, jobj, new Spiffing::Site());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Site
 * Method:    spif_native
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_surevine_spiffing_Site_spif_1native
        (JNIEnv * jenv, jobject jobj, jstring joid) {
    try {
        auto deleter = [&joid, &jenv](const char * d) {
            jenv->ReleaseStringUTFChars(joid, d);
        };
        std::unique_ptr<const char, decltype(deleter)> oid(jenv->GetStringUTFChars(joid, nullptr), deleter);
        std::shared_ptr<Spiffing::Spif> spif(Spiffing::Site::site().spif(&*oid));
        return reinterpret_cast<jlong>(&*spif);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Site
 * Method:    load_native
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_surevine_spiffing_Site_load_1native
        (JNIEnv * jenv, jobject jobj, jstring jfilename) {
    try {
        auto deleter = [&jfilename, &jenv](const char * d) {
            jenv->ReleaseStringUTFChars(jfilename, d);
        };
        std::unique_ptr<const char, decltype(deleter)> filename(jenv->GetStringUTFChars(jfilename, nullptr), deleter);
        std::ifstream ifs(&*filename);
        std::shared_ptr<Spiffing::Spif> spif(Spiffing::Site::site().load(ifs));
        return reinterpret_cast<jlong>(&*spif);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}

/*
 * Class:     com_surevine_spiffing_Site
 * Method:    dispose_native
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_surevine_spiffing_Site_dispose_1native
(JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Site * s = getHandle<Spiffing::Site>(jenv, jobj);
        delete s;
        setHandle<Spiffing::Site>(jenv, jobj, nullptr);
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}
