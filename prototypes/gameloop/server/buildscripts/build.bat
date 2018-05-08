@echo off

call default.bat

cd ..
if not exist build (
	mkdir build
)

cd build

cmake -G%CMAKE_GENERATOR% ..

PAUSE
