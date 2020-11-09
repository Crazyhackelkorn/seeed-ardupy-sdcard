# Seeed ArduPy SD Card
## Introduction

An ArduPy library for SD card. Mount a FAT formatted SD card in to the vFAT of Micropython. So that standard functions for read and write Data can be used.

## How to binding with ArduPy
- Install [AIP](https://github.com/Seeed-Studio/ardupy-aip)
```shell
pip3 install aip
```
- Build firmware with Seeed ArduPy LIS3DHTR
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
```python
import os
from arduino import sdcard

SD=sdcard()
os.mount(SD,'/sd')

with open('/sd/hello.txt', 'w') as f:
    f.write('Hello world')
	
print(open('/sd/hello.txt').read())
```
## API Reference
later
<!---
- **available(*void*) : bool** - available
```python
if lis.available():
    print("X: " + lis.x)
```

- **setPoweMode(*mode\<uint8_t\>*) : void** - set power mode
```python
# Set power mode
lis.setPoweMode(0) #POWER_MODE_NORMAL 
lis.setPoweMode(1) #POWER_MODE_LOW 
```
- **setFullScaleRange(*range\<uint8_t\>*) : void** - set full scale range
```python
lis.setFullScaleRange(0) # LIS3DHTR_RANGE_2G 
lis.setFullScaleRange(1) # LIS3DHTR_RANGE_4G
lis.setFullScaleRange(2) # IS3DHTR_RANGE_8G
lis.setFullScaleRange(3) # LIS3DHTR_RANGE_16G
```
- **setOutputDataRate(*rate\<uint8_t\>*) : void** - set output data rate
```python
lis.setOutputDataRate(0) # LIS3DHTR_DATARATE_POWERDOWN 
lis.setOutputDataRate(2) # LIS3DHTR_DATARATE_10HZ
lis.setOutputDataRate(3) # LIS3DHTR_DATARATE_25HZ
lis.setOutputDataRate(4) # LIS3DHTR_DATARATE_50HZ
lis.setOutputDataRate(5) # LIS3DHTR_DATARATE_100HZ
lis.setOutputDataRate(6) # LIS3DHTR_DATARATE_400HZ
lis.setOutputDataRate(7) # LIS3DHTR_DATARATE_400HZ
lis.setOutputDataRate(8) # LIS3DHTR_DATARATE_1_6KH
lis.setOutputDataRate(9) # LIS3DHTR_DATARATE_5KHZ
```
- **setHighSolution(*rate\<bool\>*) : void** set high solution
```python
lis.setHighSolution(True) # HighSolution enable
lis.setHighSolution(False) # HighSolution disable
```
- **openTemp(*void*) : void** - open temperature enable
```python
lis.openTemp()
```
- **closeTemp(*void*) : void** - close temperature enable
```python
lis.closeTemp()
```
- **x : float** - get acceleration z
```python
x = lis.x
```
- **y : float** - get acceleration y
```python
y = lis.y
```
- **z : float** - get acceleration z
```python
z = lis.z
```
- **adc1 : uint16_t** - get adc channle 1
```python
adc1 = lis.adc1
```
- **adc2 : uint16_t** - get adc channle 2
```python
adc2 = lis.adc2
```
- **adc3 : uint16_t** - get adc channle 3
```python
adc3 = lis.adc3
```

- **temperature : uint16_t** - get temperature
```python
temperature = lis.temperature
```
-->

----
## License
This software is written by seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.