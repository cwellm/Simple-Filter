cmake -S . -B build -DPROJECT_VERSION=1.0
cmake --build build

if [[ $? -neq 0 ]]; then
    echo "An error occured during build!"
    exit 1
fi
