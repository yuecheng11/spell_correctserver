#!/bin/sh

set -x

SOURCE_DIR=`pwd`

BUILD_DIR=${BUILD_DIR:-../build}
PROJECT_NAME=${PROJECT_NAME:-spellcorrection}

if [ ! -d $BUILD_DIR/$PROJECT_NAME ]; then
	mkdir $BUILD_DIR/$PROJECT_NAME
fi

cd $BUILD_DIR/$PROJECT_NAME \
	&& cmake $SOURCE_DIR \
	&& make $*
