echo off
echo touch.exe build begin


if not exist "release" (
	mkdir "release"
)

set compileVerPath=..\..\..\..\10-common\version

if exist "%compileVerPath%\compileinfo\airdisplay_touch_r.txt" (
del "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
)

if not exist "..\..\..\..\10-common\lib\locallib\release\win32\AVCollection.dll" (
    echo miss file AVCollection.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\asflib.dll" (
    echo miss file asflib.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\h264enc_x.dll" (
    echo miss file h264enc_x.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\kdvmedianetdll.dll" (
    echo miss file kdvmedianetdll.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\libkdcrypto-1_1.dll" (
    echo miss file libkdcrypto-1_1.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\libkdvsrtp.dll" (
    echo miss file libkdvsrtp.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\mediasdkvc10.dll" (
    echo miss file mediasdkvc10.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\mediawrapper.dll" (
    echo miss file mediawrapper.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\ospdll.dll" (
    echo miss file ospdll.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\kdimg.dll" (
    echo miss file kdimg.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\kdh4.dll" (
    echo miss file kdh4.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\kdmp3.acm" (
    echo miss file kdmp3.acm >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\kdaudproc.dll" (
    echo miss file kdaudproc.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\mfc100u.dll" (
    echo miss file mfc100u.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\msvcp100.dll" (
    echo miss file msvcp100.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\msvcr100.dll" (
    echo miss file msvcr100.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\codec\dll\kdaudcodec.dll" (
    echo miss file kdaudcodec.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\HwCodecWrapper.dll" (
    echo miss file HwCodecWrapper.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

if not exist "..\..\..\..\10-common\lib\releaselib\release\win32\IntelHwWrapper.dll" (
    echo miss file IntelHwWrapper.dll >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

rem touch 配置文件
if not exist "..\setup\touch.ini" (
    echo miss file touch.ini >> "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"
    goto end
)

call "%VS100COMNTOOLS%\vsvars32.bat"
echo build clean release vs2010
@devenv touch.vcxproj /ReBuild "Release" /Out "%compileVerPath%\compileinfo\airdisplay_touch_r.txt"

rem 还原现场
rem call "%VS60COMNTOOLS%\vcvars32.bat"


copy /Y release\touch.exe "%compileVerPath%\release\win32\AirDisplay\touch.exe"
copy /Y "..\..\..\..\10-common\lib\locallib\release\win32\AVCollection.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\asflib.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\h264enc_x.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\kdvmedianetdll.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\libkdcrypto-1_1.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\libkdvsrtp.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\mediasdkvc10.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\mediawrapper.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\ospdll.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\kdimg.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\kdh4.dll" "%compileVerPath%\release\win32\AirDisplay\tph4.dll"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\kdmp3.acm" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\kdaudproc.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\mfc100u.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\msvcp100.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\msvcr100.dll" "%compileVerPath%\release\win32\AirDisplay\"
rem 硬编码新增库
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\codec\dll\kdaudcodec.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\HwCodecWrapper.dll" "%compileVerPath%\release\win32\AirDisplay\"
copy /Y "..\..\..\..\10-common\lib\releaselib\release\win32\IntelHwWrapper.dll" "%compileVerPath%\release\win32\AirDisplay\"
rem touch 配置文件
copy /Y "..\setup\touch.ini" "%compileVerPath%\release\win32\AirDisplay\"

rem 数字签名
autosigntool touch_r.ini

echo build touch.exe over
echo on

:end