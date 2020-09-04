conan install . --install-folder build -s build_type=Debug
/usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc-9 -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++-9 -H/usr/src/tg_pokemon -B/usr/src/tg_pokemon/build -G Ninja
/usr/bin/cmake --build /usr/src/tg_pokemon/build --config Debug --target all -- -j 14