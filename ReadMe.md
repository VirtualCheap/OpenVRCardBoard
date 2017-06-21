# OpenVRCardBoard
#### Cloning instructions
```
git clone --recursive git@github.com:VirtualCheap/OpenVRCardBoard.git
```
Or if you cloned it with out the `recursive` argument
```
git submodule update --init --recursive --remote
```
#### Folder layout:
- steamapps/common/SteamVR/drivers/VirtualCheap:
  - bin
    - linux64 (32 if 32 bit)
      - driver_VirtualCheap.so (compiled file)
  - resources
    - settings
      - default.vrsettings
