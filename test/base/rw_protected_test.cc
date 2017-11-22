// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/rw_protected.h"
#include <catch.hpp>

typedef uint32_t hw_reg;

// some arbitrary registers
#define HW_IO_BUFF ((hw_reg *) 0x23450000) // write-only register
#define HW_IO_STAT ((hw_reg *) 0x12340000) // read-only register

// TEST_CASE("Get error for write-only violation", "[rw_protected_test]") {
// 
//     // unsafe, no compile-time error detection
//     *HW_IO_STAT = 0x1234;
// 
//     // write-only object supporting only a limited set of operations
//     pmt::base::WriteOnly<hw_reg> hw_io_buff(*HW_IO_BUFF);
//     hw_io_buff = 0x17;
//     // this will create a compile-time error, since hw_io_buff is write-only
//     hw_reg other = hw_io_buff;
// }
// 
// TEST_CASE("Get error for read-only violation", "[rw_protected_test]") {
// 
//     // read-only object
//     pmt::base::ReadOnly<hw_reg> hw_io_stat(*HW_IO_STAT);
//     hw_reg other = hw_io_stat;
//     // this will create a compile-time error, since hw_io_stat is read-only
//     hw_io_stat = 0x17;
// }
