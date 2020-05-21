# el_wheel
Some common use functions in c++ project and math

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
  - [ ] time
  - [ ] SimpleTime
  - [ ] Macros
  - [ ] mutex
  - [ ] eulers & transforms
  - [ ] average quaternion
  - [ ] math 
- [x] add install in cmakelists  
- [x] use C++ time instead of posix time  
- [ ] avoid singularity in eulers 
- [ ] use map (or unordered_map) instead of vector for clocks
- [ ] SimpleTime: user-define judge time
- [ ] add cmake find
- [ ] add cc file for simple time instead of implementation in header file