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


    jclass testCanvasClass = env->FindClass("TestCanvas");
    
    jfieldID showPointsField = env->GetFieldID(testCanvasClass,"showPts","Z");

    jboolean showPoints = env->GetBooleanField(canvas,showPointsField);

    
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


    if(showPoints){

    g.drawPoint(-0.5,0.5,0);
    
    g.drawPoint(0.5,0.5,0);
    
    g.drawPoint(0.5,-0.5,0);
    
    g.drawPoint(-0.5,-0.5,0);


        
    }
    

}
