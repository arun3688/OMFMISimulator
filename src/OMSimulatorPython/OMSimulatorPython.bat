@echo off
REM %~dp0 will give the location of the bat file
REM set Pythonpath to the location of python script
set PYTHONPATH=%PYTHONPATH%;%~dp0../lib
python "%*"
