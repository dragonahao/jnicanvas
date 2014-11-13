#include <jawt_md.h>
#include "JNICanvas.h"

static JAWT awt;
static JAWT_DrawingSurface* ds;
static JAWT_DrawingSurfaceInfo* dsi;
static JAWT_X11DrawingSurfaceInfo* dsi_x11;

JNIEXPORT void JNICALL Java_JNICanvas_initialize(JNIEnv *env, jobject canvas)
{
    /* Get the AWT */
    awt.version = JAWT_VERSION_1_3;
    if (JAWT_GetAWT(env, &awt) == JNI_FALSE) {
        printf("JNICanvas::initialize: AWT not found\n");
        return;
    }

    /* Get the drawing surface */
    ds = awt.GetDrawingSurface(env, canvas);
    if (ds == NULL) {
        printf("JNICanvas::initialize: NULL drawing surface\n");
        return;
    }

    /* Lock the drawing surface */
    jint lock = ds->Lock(ds);
    if((lock & JAWT_LOCK_ERROR) != 0) {
        printf("JNICanvas::initialize: Error locking surface\n");
        awt.FreeDrawingSurface(ds);
        return;
    }

    /* Get the drawing surface info */
    dsi = ds->GetDrawingSurfaceInfo(ds);
    if (dsi == NULL) {
        printf("JNICanvas::initialize: Error getting surface info\n");
        ds->Unlock(ds);
        awt.FreeDrawingSurface(ds);
        return;
    }

    /* Get the platform-specific drawing info */
    dsi_x11 = (JAWT_X11DrawingSurfaceInfo*) dsi->platformInfo;
}

JNIEXPORT void JNICALL Java_JNICanvas_dispose(JNIEnv *, jobject)
{
    /* Free the drawing surface info */
    ds->FreeDrawingSurfaceInfo(dsi);

    /* Unlock the drawing surface */
    ds->Unlock(ds);

    /* Free the drawing surface */
    awt.FreeDrawingSurface(ds);
}

JNIEXPORT void JNICALL Java_JNICanvas_paint(JNIEnv* env, jobject canvas,
        jobject graphics)
{
    Java_JNICanvas_initialize(env, canvas);
    GC gc = XCreateGC(dsi_x11->display, dsi_x11->drawable, 0, 0);
    XSetBackground(dsi_x11->display, gc, 0);
    for (int i=0; i<36;i++)
    {
	XSetForeground(dsi_x11->display, gc, 10*i);
	XFillRectangle(dsi_x11->display, dsi_x11->drawable, gc,
                10*i, 5, 90, 90);
    }
    XSetForeground(dsi_x11->display, gc, 155);
    const char *testString = "^^^ rendered from native code ^^^";
    XDrawImageString(dsi_x11->display, dsi_x11->drawable, gc,
			100, 110, testString, strlen(testString));
    XFreeGC(dsi_x11->display, gc);
    Java_JNICanvas_dispose(env, canvas);
}
