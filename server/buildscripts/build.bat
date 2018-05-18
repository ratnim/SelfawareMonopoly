@echo off

set CALL_DIR=%CD%

call default.bat

cd ..
if not exist build (
	mkdir build
)

cd build

echo prefix path: %CMAKE_PREFIX_PATH%

cmake -DCMAKE_PREFIX_PATH=%QT_CMAKE_DIR%;%CMAKE_PREFIX_PATH% -G%CMAKE_GENERATOR% ..

cd %CALL_DIR%

PAUSE
