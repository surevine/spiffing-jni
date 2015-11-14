#include "com_surevine_spiffing_Spif.h"
#include "handle.h"
#include "exception.h"
#include <spiffing/spif.h>

/*
 * Class:     com_surevine_spiffing_Spif
 * Method:    name
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_surevine_spiffing_Spif_name
  (JNIEnv * jenv, jobject jobj) {
    try {
        Spiffing::Spif * spif = getHandle<Spiffing::Spif>(jenv, jobj);
        return jenv->NewStringUTF(spif->name().c_str());
    } catch (std::runtime_error & e) {
        SpiffingJNI::throwJava(jenv, e);
    }
}