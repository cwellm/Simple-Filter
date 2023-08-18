set cmake="C:\Program Files\CMake\bin\cmake.exe"
%cmake% --version
%cmake% -S . -B build -DPROJECT_VERSION=1.0
%cmake% --build build
