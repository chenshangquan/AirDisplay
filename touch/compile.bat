@echo off

rem 删除iso打包失败的残留AirDisplay文件
if exist "..\..\..\10-common\version\release\win32\AirDisplay" (
    del /S /Q "..\..\..\10-common\version\release\win32\AirDisplay"
)

if exist "..\..\..\10-common\version\release\win32\AirDisplay" (
    rmdir /s/q "..\..\..\10-common\version\release\win32\AirDisplay"
)
if not exist "..\..\..\10-common\version\release\win32\AirDisplay" (
	mkdir "..\..\..\10-common\version\release\win32\AirDisplay"
)

cd..
cd CommInterfaceDll
call compile.bat %1

cd..
cd tservice
call compile.bat %1

cd..
cd touch
cd prj_win32
call compile.bat %1

cd..
call setup.bat %1

rem 拷贝pdb文件
copy /Y "prj_win32\release\touch.pdb" "..\..\..\10-common\version\release\win32\AirDisplay"
copy /Y "..\tservice\prj_win32\release\tservice.pdb" "..\..\..\10-common\version\release\win32\AirDisplay"
copy /Y "..\..\..\10-common\lib\locallib\release\win32\AVCollection.pdb" "..\..\..\10-common\version\release\win32\AirDisplay"

@echo on