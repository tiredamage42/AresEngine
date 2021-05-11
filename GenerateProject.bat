del *.sln
del *.vcxproj*
rmdir /Q .vs
rmdir /Q Builds
rmdir /Q Intermediates
call Premake\premake5.exe vs2019
PAUSE