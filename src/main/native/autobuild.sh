#!/bin/bash

current_dir=$(dirname $0)
echo "Running autobuild........."
cd "$current_dir"
cd src/leptonica/src/src/
make
cd ../../../tesseract/src/
./configure
make install
mv tesseract/libs/libtesseract.a tesseract/libs/libtesseracta.a
cp tesseract/libs/libtesseracta.a ../../../../resources/libs/
echo "Auto Building all libraries finished"