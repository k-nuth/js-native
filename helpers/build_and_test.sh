#!/usr/bin/env bash

if [ "$OSTYPE" == "darwin" ]; then
    export MACOSX_DEPLOYMENT_TARGET=14.0
fi

rm -rf blockchain lib
node-pre-gyp configure build


for i in $(seq 1 50);
do
    node tests.js
    if [ $? -ne 0 ]; then
        echo "************ ERROR ************"
        break
    fi
done
