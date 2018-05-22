@echo off

set CALL_DIR=%CD%

call default.bat

cd ..
if not exist build (
	mkdir build
)

cd build

cmake -G%CMAKE_GENERATOR% ..

cd %CALL_DIR%

PAUSE
