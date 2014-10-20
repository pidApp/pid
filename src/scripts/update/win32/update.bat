@echo off

echo updating...
ping 192.0.22.22 -n 1 -w 2000 > nul
move /Y C:\PID\.pid\tmp\pid.exe C:\PID\deploy\pid.exe
start "" C:\PID\deploy\pid.exe
exit
