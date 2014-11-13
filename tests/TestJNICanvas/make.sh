#!/bin/sh

set -x
 
export JAVAHOME=/usr/lib/jvm/java
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JAVAHOME/jre/lib/amd64:.
javac TestJNICanvas.java
gcc -shared -fPIC -I$JAVAHOME/include -I$JAVAHOME/include/linux \
	libJNICanvas.cc -L$JAVAHOME/jre/lib/amd64 -ljawt -o libJNICanvas.so
java TestJNICanvas
