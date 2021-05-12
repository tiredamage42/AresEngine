del /S *.sln
del /S *.vcxproj*
rmdir /Q /S .vs
rmdir /Q /S Builds
rmdir /Q /S Intermediates
call Premake\premake5.exe vs2019
PAUSE