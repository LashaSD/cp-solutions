@echo off
call vcvarsall x64
cl /Zi /EHsc /std:c++20 sol.cpp /Fe:build\sol.exe /Fo:build\ /Fd:build\
