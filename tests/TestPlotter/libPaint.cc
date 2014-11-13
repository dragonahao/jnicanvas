/*
 * Copyright 1999 Oracle and/or its affiliates.,
 * 901 San Antonio Road, Palo Alto, California, 94303, U.S.A.
 * All rights reserved.
 *
 */

#include "TestCanvas.h"
#include "jawt_md.h"
#include <iostream>
#include "Graphics2DOpenGL.h"

/*
 * Class:     TestCanvas
 * Method:    paint
 * Signature: (Ljava/awt/Graphics;)V
 */
JNIEXPORT void JNICALL Java_TestCanvas_paint
(JNIEnv* env, jobject canvas, jobject graphics) {



    
    Graphics2DOpenGL g(env, canvas);

    g.setCoordSystem(-1, 1, -1, 1, -1, 1);

    g.setColor(0, 0, 255, 255);

    g.drawSegment(0, 0, 0, 1, 0, 0);

    g.setColor(0, 255, 0, 255);

    g.drawSegment(0, 0, 0, -1, 0, 0);

    g.setColor(255, 0, 0, 255);

    g.drawSegment(0, 0, -1, 0, 0, 0);

    g.setColor(255, 255, 255, 255);

    g.drawSegment(0, 0, 1, 0, 0, 0);


    g.drawPoint(-0.5,0.5,0);
    
    g.drawPoint(0.5,0.5,0);
    
    g.drawPoint(0.5,-0.5,0);
    
    g.drawPoint(-0.5,-0.5,0);
    

    
    

    //   JAWT awt;
    //    JAWT_DrawingSurface* ds;
    //    JAWT_DrawingSurfaceInfo* dsi;
    //    JAWT_X11DrawingSurfaceInfo* dsi_x11;
    //    jboolean result;
    //    jint lock;
    //    GC gc;
    //
    //    short i;
    //    const char *testString = "^^^ rendered from native code ^^^";
    //
    //    /* Get the AWT */
    //    awt.version = JAWT_VERSION_1_3;
    //    if (JAWT_GetAWT(env, &awt) == JNI_FALSE) {
    //        printf("AWT Not found\n");
    //        return;
    //    }
    //
    //    /* Get the drawing surface */
    //    ds = awt.GetDrawingSurface(env, canvas);
    //    if (ds == NULL) {
    //        printf("NULL drawing surface\n");
    //        return;
    //    }
    //
    //    /* Lock the drawing surface */
    //    lock = ds->Lock(ds);
    //    if((lock & JAWT_LOCK_ERROR) != 0) {
    //        printf("Error locking surface\n");
    //        awt.FreeDrawingSurface(ds);
    //        return;
    //    }
    //
    //    /* Get the drawing surface info */
    //    dsi = ds->GetDrawingSurfaceInfo(ds);
    //    if (dsi == NULL) {
    //        printf("Error getting surface info\n");
    //        ds->Unlock(ds);
    //        awt.FreeDrawingSurface(ds);
    //        return;
    //    }
    //
    //    /* Get the platform-specific drawing info */
    //    dsi_x11 = (JAWT_X11DrawingSurfaceInfo*)dsi->platformInfo;
    //
    //
    //    /* Now paint */
    //    gc = XCreateGC(dsi_x11->display, dsi_x11->drawable, 0, 0);
    //    XSetBackground(dsi_x11->display, gc, 0);
    //    for (i=0; i<36;i++)
    //    {
    //	XSetForeground(dsi_x11->display, gc, 10*i);
    //	XFillRectangle(dsi_x11->display, dsi_x11->drawable, gc,
    //                10*i, 5, 90, 90);
    //    }
    //    XSetForeground(dsi_x11->display, gc, 155);
    //    XDrawImageString(dsi_x11->display, dsi_x11->drawable, gc,
    //			100, 110, testString, strlen(testString));
    //    XFreeGC(dsi_x11->display, gc);
    //
    //
    //    /* Free the drawing surface info */
    //    ds->FreeDrawingSurfaceInfo(dsi);
    //
    //    /* Unlock the drawing surface */
    //    ds->Unlock(ds);
    //
    //    /* Free the drawing surface */
    //    awt.FreeDrawingSurface(ds); 
    //    

}
