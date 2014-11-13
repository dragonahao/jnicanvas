#ifndef _libJNICanvas_h
#define _libJNICanvas_h

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif
#undef JNICanvas_FOCUS_TRAVERSABLE_UNKNOWN
#define JNICanvas_FOCUS_TRAVERSABLE_UNKNOWN 0L
#undef JNICanvas_FOCUS_TRAVERSABLE_DEFAULT
#define JNICanvas_FOCUS_TRAVERSABLE_DEFAULT 1L
#undef JNICanvas_FOCUS_TRAVERSABLE_SET
#define JNICanvas_FOCUS_TRAVERSABLE_SET 2L
#undef JNICanvas_TOP_ALIGNMENT
#define JNICanvas_TOP_ALIGNMENT 0.0f
#undef JNICanvas_CENTER_ALIGNMENT
#define JNICanvas_CENTER_ALIGNMENT 0.5f
#undef JNICanvas_BOTTOM_ALIGNMENT
#define JNICanvas_BOTTOM_ALIGNMENT 1.0f
#undef JNICanvas_LEFT_ALIGNMENT
#define JNICanvas_LEFT_ALIGNMENT 0.0f
#undef JNICanvas_RIGHT_ALIGNMENT
#define JNICanvas_RIGHT_ALIGNMENT 1.0f
#undef JNICanvas_serialVersionUID
#define JNICanvas_serialVersionUID -7644114512714619750LL
#undef JNICanvas_serialVersionUID
#define JNICanvas_serialVersionUID -2284879212465893870LL
/*
 * Class:     JNICanvas
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JNICanvas_initialize
  (JNIEnv *, jobject);

/*
 * Class:     JNICanvas
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JNICanvas_dispose
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif

JAWT_X11DrawingSurfaceInfo* dsi_x11;

#endif /* _libJNICanvas_h */
