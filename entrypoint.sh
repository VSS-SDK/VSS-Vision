#!/bin/bash

EXIT_IF_AN_ERROR_OCCURRED() {
    LAST_CODE=$?;
    echo "$LAST_CODE";
    if [[ $LAST_CODE != 0 ]];
    then
        exit $LAST_CODE;
    fi
}

TEST() {
    cd build
    ./tests
    EXIT_IF_AN_ERROR_OCCURRED;
    cd ..
}

if [[ $1 == "test" ]];
then
    TEST;
else
    echo "Only supports test"
fi