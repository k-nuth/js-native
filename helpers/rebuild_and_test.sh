#!/usr/bin/env bash

rm -rf blockchain build lib deps
node-pre-gyp configure build


for i in $(seq 1 50);
do
    node tests.js
    if [ $? -ne 0 ]; then
        echo "************ ERROR ************"
        break
    fi
done
