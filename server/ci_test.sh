#!/bin/bash

set -e # return on any error

echo "Run Selfaware-Monopoly-Server tests ..."

cd server
./build/server-test
