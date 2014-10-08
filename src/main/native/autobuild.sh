#!/bin/bash
set -e

current_dir=$(dirname $0)
echo "Running autobuild"
cd "$current_dir"

cd src
BUILD=$PWD/build

# Leptonica refuses to play nice with --enable-shared=no on Linux, trying to statically
# link libstdc++, so instead we link with -whole-archive in the wrapper Makefile
echo "Builing on `uname`"
if [[ `uname` == 'Linux' ]]; then
   LEPTONICA_FLAGS='--with-pic'
   TESSERACT_FLAGS='--with-pic'
else
   LEPTONICA_FLAGS='--disable-shared --enable-shared=no'
   TESSERACT_FLAGS='--enable-shared=no'
fi

if [ -e $BUILD/lib/liblept.a ]
then
  echo "Skipping leptonica C++ build as the library already exists"
else
  echo "building leptonica"
  cd leptonica-1.71
  mkdir -p m4 # workaround for deprecated autotools functionality on Travis builds
  ./configure --prefix=$BUILD $LEPTONICA_FLAGS --disable-programs --without-zlib --without-libpng --without-jpeg --without-giflib --without-libtiff --without-libwebp --without-libopenjpeg
  make install
  cd ..
fi

if [ -e $BUILD/lib/libtesseract.a ]
then
  echo "Skipping libtesseract C++ build as the library already exists"
else
  echo "building tesseract"
  cd tesseract-3.03
  export CPPFLAGS="-I$BUILD/include"
  export LIBLEPT_HEADERSDIR="$BUILD/include"
  ./configure --prefix=$BUILD $TESSERACT_FLAGS --with-extra-libraries=$BUILD/lib --disable-graphics
  make install
  cd ..
fi

echo "Auto-building all libraries finished"
