cmake -S . -B build -DPROJECT_VERSION=1.0
cmake --build build

if [[ ! $? -eq 0 ]]; then
    echo "An error occured during build!"
    exit 42
fi
