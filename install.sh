#!/bin/bash
echo "Downloading bullet"
curl -# -o bullet-2.79.tgz http://bullet.googlecode.com/files/bullet-2.79-rev2440.tgz 
echo "extracting"
tar -xvf bullet-2.79.tgz
cd bullet-2.79
./autogen.sh
./configure
make
