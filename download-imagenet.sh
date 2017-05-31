#!/usr/bin/env bash

DIR="example-3D-assigned-images/bin/data/"
DIR2="example-3D-unassigned-images/bin/data/"

DB_URL="https://raw.githubusercontent.com/liuliu/ccv/unstable/samples/image-net-2012.sqlite3"
WORDS_URL="https://raw.githubusercontent.com/liuliu/ccv/unstable/samples/image-net-2012.words"

DB_FILE="image-net-2012.sqlite3"
WORDS_FILE="image-net-2012.words"

mkdir -p $DIR
mkdir -p $DIR2

if [ ! -e $DB_FILE ] ; then
echo "Downloading image-net-2012 network (ccv)"
curl -o $DIR$DB_FILE $DB_URL
curl -o $DIR$WORDS_FILE $WORDS_URL
cp $DIR$DB_FILE $DIR2$DB_FILE
cp $DIR$DWORDS_FILE $DIR2$WORDS_FILE
fi
echo "Downloaded: image-net-2012 network (ccv)"
