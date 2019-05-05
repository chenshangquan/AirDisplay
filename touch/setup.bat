@echo off
echo NexTransmitter.exe build begin

rem 获取NSIS安装路径，softDisk:盘符，softPathTmp:盘符冒号后面的字符串，“delims=: ”表示冒号和空格是分隔符
for /f "skip=2 tokens=3* delims=: " %%j in ('reg query HKEY_LOCAL_MACHINE\SOFTWARE\NSIS /ve') do (
   set softDisk=%%j
   set softPathTmp=%%k
)
set softPath=%softDisk%:%softPathTmp%

set compileVerPath=..\..\..\10-common\version\release\win32\AirDisplay

if exist "setup files" (
    rmdir /s/q "setup files"
)


if not exist "setup files" (
    mkdir "setup files"
)


xcopy "%compileVerPath%\*.*" "setup files\" /s /y /h
copy /Y "setup\setup.nsi" "setup files\"
copy /Y "setup\touch.ico" "setup files\"

rem 打包成NexTransmitter.exe
cd "setup files"
"%softPath%\makensis.exe" setup.nsi
cd..

copy /Y "setup files\NexTransmitter.exe" "%compileVerPath%\"

cd "setup"
call compile.bat %1
cd..

rmdir /s/q "setup files"

echo NexTransmitter.exe build end
:end
