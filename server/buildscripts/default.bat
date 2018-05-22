@echo off

set CMAKE_GENERATOR="Visual Studio 15 2017 Win64"
set QT_PATH=C:/Qt/5.10.1/msvc2017_64

if exist configure.bat (
	call configure.bat
)

set CMAKE_PREFIX_PATH=%QT_PATH%/lib/cmake;%CMAKE_PREFIX_PATH%
set PATH=%QT_PATH%/bin;%PATH%
