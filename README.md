# el_wheel
Some common use function in c++ project and math

## Build & Install
> Only tested in ubuntu!!!
```bash
mkdir build
cd build
cmake .. 
make
# run tests
make test
sudo make install
```
Or, you can use ninja
```bash
# install Ninja 
sudo apt install ninja-build

mkdir build
cd build
cmake .. -G Ninja
ninja
# run tests
ninja test
sudo ninja install
```

## Todo list
- [ ] add tests  
- [ ] add install in cmakelists  
- [x] use C++ time instead of posix time  
- [ ] avoid singularity in eulers 