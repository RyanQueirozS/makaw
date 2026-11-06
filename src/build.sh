#!/bin/sh

gcc \
main.c makaw.h makaw.c mkwcore.h mkwcore.c \
./vendor/include/glad/glad.h \
./vendor/src/glad.c \
\
-o app \
\
-I./vendor/include/ \
-lglfw \
-lGL \
-lX11 \
-lpthread \
-lXrandr \
-lXi \
-ldl
