jnicanvas
=========

A Bridged JNI Native Canvas implementation.

The plan is to use Java and JNI to control a C++ multi-dimensional graphics library.

The current implementation of the "multid" library consists of four parts:  multid, graphGL, guiFLTK, and wutil. These parts are listed in dependency order:

* wutil contains utility classes;
* guiFLTK is a generic GUI interface implemented using the FLTK library that depends on wutil;
* graphGL is a generic graphics interface implemented in terms of OpenGL that depends on guiFLTK;
* multid is a multid-dimensional graphics library that depends on graphGL.

The intention is to replace the functionality of guiFLTK with the Java language itself. Basically what is needed is a Java replacement for the guiFLTK CanvasWin object. JNI will serve as the bridge between Java and C++.
