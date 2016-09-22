#!/bin/sh

if [ ! -d "build" ] ; then
  ./configure
fi

cd build

make -j install

if [ "$?" != "0" ] ; then
  echo "Could not build!"
  exit 1
fi


cd ..
