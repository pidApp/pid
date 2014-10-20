@echo off
set currentPath=%~dp0
mkdir C:\PID
move %currentPath%\deploy C:\PID\deploy
move %currentPath%\.pid C:\pid\.pid
%currentPath%\nircmd-x64\nircmd.exe shortcut "C:\PID\deploy\pid.exe" "~$folder.desktop$" "PID"
