@echo off
set BDS=C:\Program Files\Embarcadero\Studio\16.0
set path=%path%;C:\WINDOWS\Microsoft.NET\Framework\v3.5
set path=%path%;D:\Programmes

echo Compiling code...
msbuild Photo.cbproj /t:Build /property:"Config=Release" /nologo /v:q
if errorlevel 1 goto error

echo Compressing executable...
rem upx --brute --force -qq Photo.exe
BCBStriper Release\Photo.exe
if errorlevel 1 goto error

echo Zipping files...
zip -q -j -9 photo.zip Release\Photo.exe lisez-moi.htm
if errorlevel 1 goto error

echo Build successful.
goto end
:error
echo Build incomplete!
:end
pause