#!/bin/sh

set -x
 
export JAVAHOME=/usr/lib/jvm/java
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JAVAHOME/jre/lib/amd64:.
javac TestPlotter.java
javah TestCanvas
gcc -shared -fPIC -I$JAVAHOME/include -I$JAVAHOME/include/linux libPaint.cc \
	-L$JAVAHOME/jre/lib/amd64 -ljawt -o libPaint.so
java TestPlotter
