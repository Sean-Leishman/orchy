cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cd build && make

./apps/app test
