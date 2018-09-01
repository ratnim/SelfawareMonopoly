#!/bin/bash

set -e # return on any error

echo "Run Selfaware-Monopoly-Server tests ..."

./build/server-test

./build/rest-test
