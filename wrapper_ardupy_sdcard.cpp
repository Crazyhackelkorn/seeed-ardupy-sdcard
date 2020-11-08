/**
 * The MIT License (MIT)
 *
 * Author: Stephan Hartl
 *
 * Copyright (C) 2020 Stephan Hartl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Arduino.h>
#include <SPI.h>
#include "Seeed_Arduino_SDCard/src/SD.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/util.h"
}

#define sdcard     (*(SD *)self->module)
void * operator new(size_t, void *);

extern "C" {
    void common_hal_sdcard_construct(abstract_module_t *self, size_t n_args, const mp_obj_t *args){
		uint8_t cs = SDCARD_SS_PIN;
		SPIClass* spi = &SDCARD_SPI;
		uint32_t fre = 5000000UL;
		
		if(n_args >= 1)
		{
			cs = mp_obj_get_int(args[0]);
			
			#ifdef ARDUPY_GET_SPI
        	if(n_args >= 2)
        	{
            	int32_t spi_num = mp_obj_get_int(args[1]);
            	spi = ardupy_get_spi(spi_num); 
				
        		if(n_args == 3)
        		{
            		fre = mp_obj_get_int(args[2]);
        		}
			}
		}
        #endif
        self->module = new (m_new_obj(SD)) SD(cs,spi,fre);
    }
	
    void common_hal_sdcard_deinit(abstract_module_t *self){
        sdcard.~SD();
    }
    uint32_t common_hal_sdcard_readblocks(abstract_module_t *self, uint8_t *buffer, unsigned long long sector, unsigned int count){
        return sdcard.read(buffer, sector, count);
    }
    uint32_t common_hal_sdcard_writeblocks(abstract_module_t *self, uint8_t *buffer, unsigned long long sector, unsigned int count){
        return sdcard.write(buffer, sector, count);
    }
    uint32_t common_hal_sdcard_ioctl(abstract_module_t *self, uint8_t ops, void* arg){
        return sdcard.ioctl(ops, arg);
    }
    uint8_t common_hal_sdcard_type(abstract_module_t *self){
        return sdcard.sdcard_type();
    }
}