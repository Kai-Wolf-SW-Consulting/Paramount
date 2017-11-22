// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_CMDLINE_FLAGS_H
#define PARAMOUNT_CMDLINE_FLAGS_H

#include "base/integral_types.h"
#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

namespace pmt {

/// Macro for referencing flags
#define FLAG(name) FLAGS_##name

/// Macros for declaring flags
#define DECLARE_bool(name) extern bool FLAG(name)
#define DECLARE_uint16(name) extern uint16 FLAG(name)
#define DECLARE_int32(name) extern int32 FLAG(name)
#define DECLARE_float(name) extern float FLAG(name)
#define DECLARE_double(name) extern double FLAG(name)
#define DECLARE_string(name) extern std::string FLAG(name)

/// Macros for defining flags
#define DEFINE_bool(name, def_val, doc) bool FLAG(name)          = (def_val)
#define DEFINE_uint16(name, def_val, doc) uint16 FLAG(name)      = (def_val)
#define DEFINE_int32(name, def_val, doc) int32 FLAG(name)        = (def_val)
#define DEFINE_float(name, def_val, doc) float FLAG(name)        = (def_val)
#define DEFINE_double(name, def_val, doc) double FLAG(name)      = (def_val)
#define DEFINE_string(name, def_val, doc) std::string FLAG(name) = (def_val)

namespace base {

/// Parses |str| for a 16-bit unsigned integer and writes the result to |value|,
/// if successful.
bool ParseUInt16(const std::string &src, const char *str, uint16 *value);

/// Parses |str| for a 32-bit signed integer and writes the result to |value|,
/// if successful.
bool ParseInt32(const std::string &src, const char *str, int32 *value);

/// Parses a string for a bool flag in the form of '--flag=value' or '--flag'.
/// In the former case, the value is taken as true, as long as it does not start
/// with '0', 'f', or 'F'. In the latter case, the value is taken as true.
bool ParseBoolFlag(const char *str, const char *flag, bool *value);

/// Parses a string for an int32 flag, in the form of '--flag=value'.
/// On success it stores the value of the flag in |value|.
bool ParseInt32Flag(const char *str, const char *flag, int32 *value);

/// Parses a string for an uint16 flag, in the form of '--flag=value'.
/// On success it stores the value of the flag in |value|.
bool ParseUInt16Flag(const char *str, const char *flag, uint16 *value);

/// Parses a string for a double flag, in the form of '--flag=value'.
/// On success it stores the value of the flag in |value|.
bool ParseDoubleFlag(const char *str, const char *flag, double *value);

/// Parses a string for a string flag, in the form of '--flag=value'.
/// On success it stores the value of the flag in |value|.
bool ParseStringFlag(const char *str, const char *flag, std::string *value);

/// Returns true, if the string matches the |flag|.
bool IsFlag(const char *str, const char *flag);
}

} // namespace pmt

#endif // PARAMOUNT_CMDLINE_FLAGS_H
