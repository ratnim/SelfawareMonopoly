#!/bin/bash

set -e # return on any error

echo "Run Selfaware-Monopoly-Server tests ..."

./server/build/server-test
./server/build/rest-test
