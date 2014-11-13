#!/bin/sh

set -x
 
export JAVAHOME=/usr/lib/jvm/java-7-oracle
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JAVAHOME/jre/lib/amd64:.
javac TestPlotter.java
javah TestCanvas
#g++ -fPIC -I$JAVAHOME/include -I$JAVAHOME/include/linux Graphics2DOpenGL.cpp 
g++ -shared -fPIC -I$JAVAHOME/include -I$JAVAHOME/include/linux Graphics2DOpenGL.cpp libPaint.cc\
	-L$JAVAHOME/jre/lib/amd64 -ljawt -lGL -lGLU -o libPaint.so
java TestPlotter
