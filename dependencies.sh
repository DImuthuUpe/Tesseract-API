#!/bin/bash
#curl -O https://tesseract-ocr.googlecode.com/files/tesseract-ocr-3.02.02.tar.gz
#curl -O http://leptonica.googlecode.com/files/leptonica-1.69.tar.gz
tar -zxvf tesseract-ocr-3.02.02.tar.gz
tar -zxvf leptonica-1.69.tar.gz
rm -r jni/tesseract/src
mkdir jni/tesseract/src/tesseract-ocr
rm -r jni/leptonica/src
mkdir jni/leptonica/src/leptonica-1.6
#rm -f tesseract-ocr-3.02.02.tar.gz
#rm -f leptonica-1.69.tar.gz
mv tesseract-ocr ./jni/tesseract/src
mv leptonica-1.69 ./jni/leptonica/src
echo You may now run ndk-build to generate shared libraries.
