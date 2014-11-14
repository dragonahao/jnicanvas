#include <iostream>
#include<GL/glu.h>
#include<GL/glx.h>
#include <jawt_md.h>
#include "JNICanvas.h"

static JAWT awt;
static JAWT_DrawingSurface* ds;
static JAWT_DrawingSurfaceInfo* dsi;
static JAWT_X11DrawingSurfaceInfo* dsi_x11;
static GC gc;

#define TEST_OPENGL

JNIEXPORT void JNICALL Java_JNICanvas_initialize(JNIEnv *env, jobject canvas)
{
    std::cerr << "entering initialize\n";
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

    /* Create the X11 graphic context */
    gc = XCreateGC(dsi_x11->display, dsi_x11->drawable, 0, 0);

    Window root = DefaultRootWindow(dsi_x11->display);

    GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
    XVisualInfo* vi = glXChooseVisual(dsi_x11->display, 0, att);

    Colormap cmap = XCreateColormap(dsi_x11->display, root, vi->visual,
        AllocNone);

    // TODO:  Doesn't swa need to be either set or used?
    XSetWindowAttributes swa;
//    swa.colormap = cmap;
//    swa.event_mask = ExposureMask | KeyPressMask;

    GLXContext glc = glXCreateContext(dsi_x11->display, vi, NULL, GL_TRUE);

    glShadeModel(GL_SMOOTH);

    glXMakeCurrent(dsi_x11->display, dsi_x11->drawable, glc);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glXSwapBuffers(dsi_x11->display, dsi_x11->drawable);

    ds->Unlock(ds);
}

JNIEXPORT void JNICALL Java_JNICanvas_dispose(JNIEnv *, jobject)
{
    std::cerr << "entering dispose\n";
    /* Free the graphics context */
    XFreeGC(dsi_x11->display, gc);

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
    std::cerr << "entering paint\n";
    Java_JNICanvas_initialize(env, canvas);
}

JNIEXPORT void JNICALL Java_JNICanvas_segment(JNIEnv *env, jobject canvas,
        jdouble x1, jdouble y1, jdouble x2, jdouble y2)
{
    std::cerr << "entering segment\n";
    /* Lock the drawing surface */
    jint lock = ds->Lock(ds);
    if((lock & JAWT_LOCK_ERROR) != 0) {
        printf("JNICanvas::initialize: Error locking surface\n");
        awt.FreeDrawingSurface(ds);
        return;
    }

    glColor4d(255, 0, 0, 0);
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();

    glXSwapBuffers(dsi_x11->display, dsi_x11->drawable);

    ds->Unlock(ds);
}
