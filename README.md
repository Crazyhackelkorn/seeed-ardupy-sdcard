# Seeed ArduPy SD Card
## Introduction

An ArduPy library for SD card. Mount a FAT formatted SD card in to the vFAT of Micropython. So that standard functions for read and write Data can be used.

## How to binding with ArduPy
- Install [AIP](https://github.com/Seeed-Studio/ardupy-aip)
```shell
pip3 install aip
```
- Build firmware with Seeed ArduPy SD Card
```shell
aip install https://github.com/Crazyhackelkorn/seeed-ardupy-sdcard
aip build
```
- Flash new firmware to you ArduPy board
```shell
aip flash [Ardupy Bin PATH]
```
For more examples of using AIP, please refer to [AIP](https://github.com/Seeed-Studio/ardupy-aip).

## Usage
**Note:** Tested code with Wio Terminal and an 32GB SanDisk microSDHC (FAT32)

```python
import os
from arduino import sdcard
# from machine import Map

SD=sdcard()
# sdcard(64,Map.SPI2,5000000) # equal for Wio Terminal
os.mount(SD,'/sd')

with open('/sd/hello.txt', 'w') as f:
    f.write('Hello world')
	
print(open('/sd/hello.txt').read())
```
## API Reference
- **available(*mode\<char>*) : bool** - available
```python
# simple attribute check
if SD.available():
    print(open('/sd/hello.txt').read())
	
# reinit SD card. Should detect ejected SD card.
if SD.available('f'):
    print(open('/sd/hello.txt').read())
else:
	os.umount('/sd')
	SD.umount()
```

- **type : int** - SD type
```python
if SD.type == 0:
	print("No card")
elif SD.type == 1:
	print("MMC card")
elif SD.type == 2:
	print("SD card")
elif SD.type == 3:
	print("SDHC card")
elif SD.type == 4:
	print("Unknown card")
```

- **size : int** - SD physical size in KB
```python
print (SD.size,"KB")
```

- **umount(*void*) : void** - deinit SD state, type, sector count
```python
os.umount('/sd')
SD.umount() # isn't needed but so SD.type, SD.size and SD.available() return correct values.
```

### Block Devise Functions
For more detail see [uos.AbstractBlockDev](https://docs.micropython.org/en/latest/library/uos.html#uos.AbstractBlockDev)

- **readblocks(*num\<uint64>*,*buf\<bytearray>*) : void** - reads raw data
```python
b = bytearray(512) # one block is 512 Byte
SD.readblocks(0,b)
print(b)
```

- **writeblocks(*num\<uint64>*,*buf\<bytearray>*) : void** - writes raw data

**Note: Don't do this**

```python
b = bytearray(512) # one block is 512 Byte
SD.writeblocks(0,b) #shouldn't be done
SD.readblocks(0,b)
print(b)
```

- **ioctl(*cmd\<uint8>*) : uint64** - additional io functions
```python
SD.ioctl(1) # initialise the device / get device status
SD.ioctl(2) # deinitialise/shutdown the device
SD.ioctl(3) # sync the device
SD.ioctl(4) # get a count of the number of blocks
SD.ioctl(5) # get the number of bytes in a block
```

----
## License
This software is written by seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.