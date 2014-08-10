#!/bin/bash

echo "Running autoclean........."
current_dir=$(dirname $0)
cd "$current_dir"
cd src/leptonica/src/src/
make clean
cd ../../../tesseract/src/
make clean
