#!/bin/bash

if [ -z "$1" ];then
    echo "./%0 <name>"
    exit 1
fi

cp -f TFxExample.h TFx${1}.h
cp -f TFxExample.cxx TFx${1}.cxx

sed -i -e 's/TFxExample/TFx'$1'/g' TFx${1}.h
sed -i -e 's/TFxExample/TFx'$1'/g' TFx${1}.cxx

echo "Files 'TFx${1}.h' and 'TFx${1}.cxx' were created."
