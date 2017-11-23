// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_SCOPE_GUARD_H
#define PARAMOUNT_SCOPE_GUARD_H

#include "base/macros.h"
#include <utility>

namespace pmt {
namespace base {

/// This idiom ensures that resources always get released in face of an
/// exception or otherwise not returning normally. |ScopeGuard| can exploit
/// type inference and auto, move semantics as well as lambda functions which
/// can defer any arbitrary code
template <typename Func>
class ScopeGuard {
  public:
    ScopeGuard() = delete;
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&& rhs)
        : func_(std::move(rhs.func_)), isActive_(rhs.isActive_) {
        rhs.dismiss();
    }
    ScopeGuard(Func func) : func_(std::move(func)), isActive_(true) {}
    ~ScopeGuard() {
        if (isActive_) func_();
    }
    void dismiss() {
        isActive_ = false;
    }

  private:
    Func func_;
    bool isActive_;
};

/// This is a classic trick, having a template class, which we want to
/// associate with a template function, because a template function may use
/// type deduction, which the template class is incapable of.
/// Example usage:
///     void fun() {
///         auto buf = malloc(1024 * 1024);
///         auto g1 = scopeGuard([] { free(buf); });
///         // .. use buf here ..
///     }
template <typename Func>
ScopeGuard<Func> scopeGuard(Func func) {
    return ScopeGuard<Func>(std::move(func));
}

namespace internal {
enum class ScopeGuardOnExit {};
template <typename Func>
ScopeGuard<Func> operator+(ScopeGuardOnExit, Func&& fn) {
    return ScopeGuard<Func>(std::forward<Func>(fn));
}
} // namespace internal
} // namespace base
} // namespace pmt

/// This works as follows: |ANONYMOUS_VARIABLE| creates a variable which
/// shouldn't clash with any other variable in the current scope. This variable
/// gets initialized with |ScopeGuardOnExit| plus an unfinished lambda
/// function. Note that we're not interested in |ScopeGuardOnExit| itself, but
/// only need its type. If |SCOPE_EXIT| is used, the user finishes it with {}
/// and inserts the code, which gets executed when the current scope is left.
/// Example usage:
///     void fun() {
///         char name[] = "/tmp/deleteme.XXXXXX";
///         auto fd = mkstemp(name);
///         SCOPE_EXIT { fclose(fd); unlink(name); };
///         // .. use fd here ..
///     }
#define SCOPE_EXIT                              \
    auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = \
        pmt::base::internal::ScopeGuardOnExit() + [&]()

#endif // PARAMOUNT_SCOPE_GUARD_H
