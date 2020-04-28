@echo off
set PROJECT_NAME=%1
echo %PROJECT_NAME%
if not defined PROJECT_NAME (
	set PROJECT_NAME=quectel_bg96_multithread
	)
echo %PROJECT_NAME%
build_demo.bat llvm %PROJECT_NAME%
