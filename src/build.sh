#!/bin/sh

gcc \
main.c makaw.c mkwcore.c \
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
-ldl \
-Wall -Wextra -Wunused-function

./app
