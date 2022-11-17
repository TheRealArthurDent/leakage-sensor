#!/bin/bash

PROJECT_NAME=esp8266-wifi-participant

(
    # cleanup
    cd .. || exit
    rm -r ${PROJECT_NAME} -f
)

(
    # copy files
    cd .. || exit
    cp -r src ${PROJECT_NAME}
    cp -r include/* ${PROJECT_NAME}
)

(
    # Rename cpp files to Arduino IDE sketches
    cd ../${PROJECT_NAME} || exit
    pwd
    # Rename "main" sketch
    mv main.cpp ${PROJECT_NAME}.ino
    # Rename remaining cpp files
    find -type f -name '*.cpp' -exec mv {} {}.ino \;
)