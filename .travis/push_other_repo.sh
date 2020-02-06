#!/bin/bash

function replace_versions {
    # echo $1 #project name
    # echo $2 #build number
    if [ ! -f versions.txt ]; then
        echo "$1: $2" >> versions.txt
    else
        while read p; do
            if [[ $p == *"$1:"* ]]; then
                echo "$1: $2" >> versions.txt.t
            else
                echo $p >> versions.txt.t
            fi
        done <versions.txt
        mv versions.txt{.t,}
    fi
}  

function increment_py_version {
    while read p; do
        if [[ $p == "__version__ ="* ]]; then
            # echo "$1: $2" >> version.py.t
            # echo "__version__ = '1.1.9'" | perl -pe 's/\b(\d+)(?=\D*$)/$1+1/e'
            echo $p | perl -pe 's/\b(\d+)(?=\D*$)/$1+1/e' >> version.py.t
        else
            echo $p >> version.py.t
        fi
    done <version.py
    mv version.py{.t,}
}  


# --------------------------------------------------------------------------------------------------------------------

set -e
set -x

git config --global user.email "ci@kth.cash"
git config --global user.name "Knuth CI"

mkdir temp
cd temp

# --------------------------------------------------------------------------------------------------------------------


# --------------------------------------------------------------------------------------------------------------------
# py-api
# --------------------------------------------------------------------------------------------------------------------
git clone https://github.com/k-nuth/py-api.git

cd py-api
echo "Travis branch: ${TRAVIS_BRANCH}"
git checkout ${TRAVIS_BRANCH}

replace_versions c-api $KTH_BUILD_NUMBER
increment_py_version

cat versions.txt
cat version.py

git add . versions.txt
git add . version.py
git commit --message "Travis py-native build: $KTH_BUILD_NUMBER, $TRAVIS_BUILD_NUMBER" || true
git remote add origin-commit https://${GH_TOKEN}@github.com/k-nuth/py-api.git > /dev/null 2>&1
git push --quiet --set-upstream origin-commit ${TRAVIS_BRANCH}  || true

cd ..

# --------------------------------------------------------------------------------------------------------------------
