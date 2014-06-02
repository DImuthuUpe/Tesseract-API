Tesseract-API
=============
This project provides a JNI wrapper for Tesseract OCR Library.

Before building this project 

Download http://opensource.mxtelecom.com/maven/repo/com/wapmx/native/mx-native-loader/1.2/mx-native-loader-1.2-src.zip

Extract and run mvn clean install

To build platform dependant Leptonica and Tesseract static libs

1. Go to src/main/native/src/leptonica/src

2. make clean

3. make

4. Go to /Users/dimuthuupeksha/Documents/Academic/Tesseract-API/src/main/native/src/tesseract/src

5. Open configure file

6. Line 2592 : LDFLAGS="-L{path to root folder}/src/main/resources/{OS name}/libs"

7. Line 17269 : LIBLEPT_HEADERSDIR="{path to root folder}/src/main/native/src/leptonica/include/leptonica"

8. Run configure file : ./configure

9. make clean

10. make install

11. Copy {path to root folder}/src/main/native/src/tesseract/src/tesseract/libs/libtesseract.a to {path to root folder}/src/main/resources/{OS name}/libs/libtesseracta.a (* file should be re named libtesseract.a -> libtesseracta.a)

12. Goto porject root directory run : mvn clean install