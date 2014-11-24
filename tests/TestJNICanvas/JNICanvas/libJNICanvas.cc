#include <iostream>
#include<GL/glu.h>
#include<GL/glx.h>
#include <jawt_md.h>
#include "JNICanvas.h"
#include "libJNICanvas.h"

// variables shared by construct_graphics() and destruct_graphics()
static bool is_graphics_constructed = false;
static JAWT awt;
static JAWT_DrawingSurface* ds;
static JAWT_DrawingSurfaceInfo* dsi;
static JAWT_X11DrawingSurfaceInfo* dsi_x11;
static GC gc;
static GLXContext glc;

static void
construct_graphics(JNIEnv *env, jobject canvas)
{
//    std::cerr << "entering construct_graphics()\n";
//    std::cerr << "construct_graphics:  is_graphics_constructed = "
//        << is_graphics_constructed << "\n";
    if (is_graphics_constructed)
        return;

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
    lock();

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

    glc = glXCreateContext(dsi_x11->display, vi, NULL, GL_TRUE);

    make_current();

    glShadeModel(GL_SMOOTH);

//    clear();

    unlock();

    is_graphics_constructed = true;
}

static void
destruct_graphics(void)
{
//    std::cerr << "entering destruct_graphics()\n";
//    std::cerr << "destruct_graphics:  is_graphics_constructed = "
//        << is_graphics_constructed << "\n";
    if (! is_graphics_constructed)
        return;

    /* Free the graphics context */
    XFreeGC(dsi_x11->display, gc);

    /* Free the drawing surface info */
    ds->FreeDrawingSurfaceInfo(dsi);

    /* Unlock the drawing surface */
    // BUG:  causes IllegalMonitorStateException
//    unlock();

    /* Free the drawing surface */
    awt.FreeDrawingSurface(ds);

    is_graphics_constructed = false;
}

void
make_current(void)
{
    glXMakeCurrent(dsi_x11->display, dsi_x11->drawable, glc);
}

void
clear(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    swap_buffers();
}

void
swap_buffers(void)
{
    glXSwapBuffers(dsi_x11->display, dsi_x11->drawable);
}

void
lock(void)
{
    jint lock = ds->Lock(ds);
    if((lock & JAWT_LOCK_ERROR) != 0) {
        // TODO:  throw an exception?
        printf("JNICanvas::lock():  Error locking drawing surface\n");
        destruct_graphics();
        return;
    }
}

void
unlock(void)
{
    ds->Unlock(ds);
}

JNIEXPORT jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    std::cerr << "entering JNI_OnLoad()\n";
    return JNI_VERSION_1_2;
}

/*
JNIEXPORT void JNICALL
Java_JNICanvas_initialize(JNIEnv *env, jobject canvas) {
    std::cerr << "entering Java_JNICanvas_initialize()\n";
    construct_graphics(env, canvas);
}
*/

JNIEXPORT void JNICALL
Java_JNICanvas_JNICanvas_paint(JNIEnv* env, jobject canvas, jobject graphics) {
    std::cerr << "entering Java_JNICanvas_JNICanvas_paint()\n";
    // count on paint() being called before any drawing is done
    construct_graphics(env, canvas);
    clear();
}

JNIEXPORT void JNICALL
Java_JNICanvas_JNICanvas_timing(JNIEnv* env, jclass) {
    std::cerr << "entering Java_JNICanvas_JNICanvas_timing()\n";
/*
    destruct_graphics();
    for (int i = 0; i < 1000; ++i) {
        construct_graphics(env, canvas);
        destruct_graphics();
    }
    construct_graphics(env, canvas);
*/
    XFreeGC(dsi_x11->display, gc);
    for (int i = 0; i < 10000; ++i) {
        gc = XCreateGC(dsi_x11->display, dsi_x11->drawable, 0, 0);
        XFreeGC(dsi_x11->display, gc);
    }
    gc = XCreateGC(dsi_x11->display, dsi_x11->drawable, 0, 0);
}

/*
JNIEXPORT void JNICALL
Java_JNICanvas_JNICanvas_dispose(JNIEnv *, jobject) {
    std::cerr << "entering Java_JNICanvas_JNICanvas_dispose()\n";
    destruct_graphics();
}
*/

JNIEXPORT void JNICALL
Java_JNICanvas_JNICanvas_segment(JNIEnv *env, jobject canvas,
        jdouble x1, jdouble y1, jdouble x2, jdouble y2)
{
    std::cerr << "entering Java_JNICanvas_JNICanvas_segment()\n";
    construct_graphics(env, canvas);
    make_current();
    lock();

    glColor4d(255, 0, 0, 0);
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();

    swap_buffers();
    unlock();
    destruct_graphics();
}
