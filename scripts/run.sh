#!/bin/bash

PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"
MY_PWD=`pwd`

# Build
cd $PROJECT_DIR
$PROJECT_DIR/scripts/make.sh install || exit $?

export LD_LIBRARY_PATH="$PROJECT_DIR/lib:$LD_LIBRARY_PATH"

if [ -n "$1" ];then
  MY_RUN_DIR=$PROJECT_DIR/tmp/${1/.C/}
  rm -Rf $MY_RUN_DIR
  mkdir -p $MY_RUN_DIR

  MACRO=$(basename $1)
  MACRO_DIR=$(dirname $1)

  shift
  cd $MY_RUN_DIR
  cp -r $PROJECT_DIR/$MACRO_DIR/* .
  cp -r $PROJECT_DIR/pars/* .
fi
nice -n 15 root $ROOT_ARGS -l $PROJECT_DIR/macros/MainRun.C'("'$MACRO'","'$*'","'$PROJECT_DIR/'")'
cd $MY_PWD


