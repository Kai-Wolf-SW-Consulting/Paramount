// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_INTEGRAL_TYPES_H
#define PARAMOUNT_INTEGRAL_TYPES_H

#include "base/macros.h"

namespace pmt {

// Following are basic integer type definitions for various platforms including
// Windows, Mac and Linux

// signed integer types with width of 8, 16, 32 or 64 bits respectively
using int8  = signed char;
using int16 = short;
using int32 = int;
#if defined(OS_WINDOWS)
  typedef __int64 int64;
#else
  using int64  = long long;
#endif

// unsigned integer types with with of 8, 16, 32 or 64 bits respectively
using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
#if defined(OS_WINDOWS)
  typedef unsigned __int64 uint64;
#else
  using uint64 = unsigned long long;
#endif

// long long macros to be used because gcc and vc++ use different suffixes and
// different size specifiers in format strings
#undef GG_LONGLONG
#undef GG_ULONGLONG
#undef GG_LL_FORMAT

#if defined(OS_WINDOWS)
// long long suffixes for MSVC
#  define GG_LONGLONG(x) x##I64
#  define GG_ULONGLONG(x) x##UI64
// length modifier in printf format string for int64's (e.g. within %d)
#  define GG_LL_FORMAT "I64"
#  define GG_LL_FORMAT_W L"I64"
#else
#  define GG_LONGLONG(x) x##LL
#  define GG_ULONGLONG(x) x##ULL
#  define GG_LL_FORMAT "ll"
#  define GG_LL_FORMAT_W L"ll"
#endif

static const uint8 kUINT8max   = (static_cast<uint8>(0xFF));
static const uint16 kUINT16max = (static_cast<uint16>(0xFFFF));
static const uint32 kUINT32max = ((uint32) 0xFFFFFFFF);
static const uint64 kUINT64max = ((uint64) GG_LONGLONG(0xFFFFFFFFFFFFFFFF));
static const int8 kINT8min     = (static_cast<int8>(~0x7F));
static const int8 kINT8max     = (static_cast<int8>(0x7F));
static const int16 kINT16min   = (static_cast<int16>(~0x7FFF));
static const int16 kINT16max   = (static_cast<int16>(0x7FFF));
static const int32 kINT32min   = ((int32) ~0x7FFFFFFF);
static const int32 kINT32max   = ((int32) 0x7FFFFFFF);
static const int64 kINT64min   = ((int64) GG_LONGLONG(~0x7FFFFFFFFFFFFFFF));
static const int64 kINT64max   = ((int64) GG_LONGLONG(0x7FFFFFFFFFFFFFFF));

} // namespace pmt

#endif // PARAMOUNT_INTEGRAL_TYPES_H
