#!/bin/bash

echo "Running autoclean"
current_dir=$(dirname $0)
cd "$current_dir"

cd leptonica-1.71
make clean
cd ..

cd tesseract-3.03
make clean
cd ..

rm -r build
