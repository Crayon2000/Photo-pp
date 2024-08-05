@echo off
set BDS=C:\Program Files (x86)\Embarcadero\Studio\23.0
set path=%path%;C:\WINDOWS\Microsoft.NET\Framework\v3.5
set path=%path%;E:\Programmes

echo Compiling Win32 code...
msbuild Photo.cbproj /target:Build /property:"Config=Release";"Platform=Win32" /nologo /v:q
if errorlevel 1 goto error

echo Compiling Win64 code...
msbuild Photo.cbproj /target:Build /property:"Config=Release";"Platform=Win64" /nologo /v:q
if errorlevel 1 goto error

echo Zipping Win32 files...
zip -q -j -9 photo_win32.zip Win32\Release\Photo.exe Docs\lisez-moi.htm
if errorlevel 1 goto error

echo Zipping Win64 files...
zip -q -j -9 photo_win64.zip Win64\Release\Photo.exe Docs\lisez-moi.htm
if errorlevel 1 goto error

echo Build successful.
goto end
:error
echo Build incomplete!
:end
pause
