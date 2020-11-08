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

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "shared-bindings/util.h"

void common_hal_sdcard_construct(abstract_module_t *self, size_t n_args, const mp_obj_t *args);
void common_hal_sdcard_deinit(abstract_module_t *self);
uint32_t common_hal_sdcard_readblocks(abstract_module_t *self, uint8_t *buffer, unsigned long long sector, unsigned int count);
uint32_t common_hal_sdcard_writeblocks(abstract_module_t *self, uint8_t *buffer, unsigned long long sector, unsigned int count);
uint32_t common_hal_sdcard_ioctl(abstract_module_t *self, uint8_t ops);
uint8_t common_hal_sdcard_type(abstract_module_t *self);

extern const mp_obj_type_t sdcard_type;

m_generic_make(sdcard)
{
    abstract_module_t *self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 0, 3, true);
    common_hal_sdcard_construct(self, n_args, args);
    return self;
}

// functions
mp_obj_t sdcard_readBlocks(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    unsigned long long sector = mp_obj_get_int(pos_args[1]);
	unsigned int count;
	//uint8_t* buffer=mp_obj_str_get_data(pos_args[2],&count);
	//mp_obj_get_array(pos_args[2],&count,&buffer);
	mp_obj_array_t* buf=MP_OBJ_TO_PTR(pos_args[1]);
	count=buf->len/(common_hal_sdcard_ioctl(self, 5));
    common_hal_sdcard_readblocks(self, buf->items, sector, count);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(sdcard_readBlocks_obj, 2, sdcard_readBlocks);

mp_obj_t sdcard_writeBlocks(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    unsigned long long sector = mp_obj_get_int(pos_args[1]);
	unsigned int count;
	//uint8_t* buffer=mp_obj_str_get_data(pos_args[2],&count);
	//mp_obj_get_array(pos_args[2],&count,&buffer);
	//count=count/(common_hal_sdcard_ioctl(self, 5));
	mp_obj_array_t* buf=MP_OBJ_TO_PTR(pos_args[1]);
	count=buf->len/(common_hal_sdcard_ioctl(self, 5));
    common_hal_sdcard_writeblocks(self, buf->items, sector, count);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(sdcard_writeBlocks_obj, 2, sdcard_writeBlocks);

mp_obj_t sdcard_ioctl(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    unsigned long long ops = mp_obj_get_int(pos_args[1]);
    uint32_t res = common_hal_sdcard_ioctl(self, ops);
    return mp_obj_new_int(res);
}
MP_DEFINE_CONST_FUN_OBJ_KW(sdcard_ioctl_obj, 2, sdcard_ioctl);

// attributes

void sdcard_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    abstract_module_t *self = (abstract_module_t *)self_in;
    uint32_t value;
    float number;
    if (dest[0] == MP_OBJ_NULL) {
        if (attr == MP_QSTR_type) {
            value = common_hal_sdcard_type(self); // Call previously defined unction
            dest[0] = mp_obj_new_int(value); // This the MicroPython float type, should match with the data type
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

const mp_rom_map_elem_t sdcard_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),    MP_ROM_PTR(&sdcard_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),  MP_ROM_PTR(&sdcard_obj___exit___obj) },
	{ MP_ROM_QSTR(MP_QSTR_readblocks),  MP_ROM_PTR(&sdcard_readBlocks_obj) },
	{ MP_ROM_QSTR(MP_QSTR_writeblocks),  MP_ROM_PTR(&sdcard_writeBlocks_obj) },
	{ MP_ROM_QSTR(MP_QSTR_ioctl),  MP_ROM_PTR(&sdcard_ioctl_obj) },
};
 
MP_DEFINE_CONST_DICT(sdcard_locals_dict, sdcard_locals_dict_table);

const mp_obj_type_t sdcard_type = {
    {&mp_type_type},
    .name = MP_QSTR_SDCard,
    .make_new = sdcard_make_new,
    .locals_dict = (mp_obj_t)&sdcard_locals_dict,
    .attr = sdcard_obj_attr};