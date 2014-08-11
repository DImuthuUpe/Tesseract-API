Tesseract-API
=============
This project provides a JNI wrapper for Tesseract OCR Library.

Before building this project 

Download http://opensource.mxtelecom.com/maven/repo/com/wapmx/native/mx-native-loader/1.2/mx-native-loader-1.2-src.zip

Extract and run mvn clean install

Building Tesseract API
=====================

1 - Simple way (This automatically builds all Tesseract and Leptonica static libraries)

Goto porject root directory and run
mvn clean install

--------------------------------------------------
2 - Custom way

Download suitable static libs that are compatible with your system. Ex : Mac OS x64
liblepta.a and libtesseract.a from sourceforge

Copy them to src/main/resources/libs

Comment out line 48 ( <exec executable="src/main/native/autobuild.sh" failonerror="true">) in pom.xml

Build project using mvn clean install