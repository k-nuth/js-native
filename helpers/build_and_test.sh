#!/usr/bin/env bash

echo "OSTYPE: $OSTYPE"
if [ "$OSTYPE" == "darwin" ] || [ "$OSTYPE" == "darwin24" ]; then
    export MACOSX_DEPLOYMENT_TARGET=14.0
fi
echo "MACOSX_DEPLOYMENT_TARGET: $MACOSX_DEPLOYMENT_TARGET"

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
