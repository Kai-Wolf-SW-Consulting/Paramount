// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the topdirectory.

#ifndef PARAMOUNT_CALLBACK_IMPL_H
#define PARAMOUNT_CALLBACK_IMPL_H

#include "base/callback_types.h"
#include <type_traits>

namespace pmt {
namespace internal {

template <typename T>
struct ConstRef {
    typedef typename ::std::remove_reference<T>::type base_type;
    typedef const base_type& type;
};
}
template <bool del, typename RetType, typename Class,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_0_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)() const;
    inline ConstMemberResultCallback_0_0(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)();
        } else {
            RetType result = (instance_->*method_)();
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};
template <bool del, typename Class>
class ConstMemberResultCallback_0_0<
    del, void, Class,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)() const;
    inline ConstMemberResultCallback_0_0(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)();
        } else {
            (instance_->*method_)();
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType>
inline typename ConstMemberResultCallback_0_0<true, RetType, Caller>::base*
MakeCallback(const Caller* instance, RetType (Callee::*method)() const) {
    return new ConstMemberResultCallback_0_0<true, RetType, Caller>(instance,
                                                                    method);
}

template <typename Caller, typename Callee, typename RetType>
inline typename ConstMemberResultCallback_0_0<false, RetType, Caller>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)() const) {
    return new ConstMemberResultCallback_0_0<false, RetType, Caller>(instance,
                                                                     method);
}
template <bool del, typename RetType, typename Class,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_0_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)();
    inline MemberResultCallback_0_0(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)();
        } else {
            RetType result = (instance_->*method_)();
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
};
template <bool del, typename Class>
class MemberResultCallback_0_0<
    del, void, Class,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)();
    inline MemberResultCallback_0_0(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)();
        } else {
            (instance_->*method_)();
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType>
inline typename MemberResultCallback_0_0<true, RetType, Caller>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)()) {
    return new MemberResultCallback_0_0<true, RetType, Caller>(instance,
                                                               method);
}

template <typename Caller, typename Callee, typename RetType>
inline typename MemberResultCallback_0_0<false, RetType, Caller>::base*
MakePermanentCallback(Caller* instance, RetType (Callee::*method)()) {
    return new MemberResultCallback_0_0<false, RetType, Caller>(instance,
                                                                method);
}
template <bool del, typename RetType>
class FunctionResultCallback_0_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (*Function)();
    inline FunctionResultCallback_0_0(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (*function_)();
        } else {
            RetType result = (*function_)();
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
};
template <bool del>
class FunctionResultCallback_0_0<del, void> : public Callback {
  public:
    typedef Callback base;
    typedef void (*Function)();
    inline FunctionResultCallback_0_0(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (*function_)();
        } else {
            (*function_)();
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
};

template <typename RetType>
inline typename FunctionResultCallback_0_0<true, RetType>::base* MakeCallback(
    RetType (*function)()) {
    return new FunctionResultCallback_0_0<true, RetType>(function);
}

template <typename RetType>
inline typename FunctionResultCallback_0_0<false, RetType>::base*
MakePermanentCallback(RetType (*function)()) {
    return new FunctionResultCallback_0_0<false, RetType>(function);
}
template <bool del, typename RetType, typename Class, typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_0_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(A1) const;
    inline ConstMemberResultCallback_0_1(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(a1);
        } else {
            RetType result = (instance_->*method_)(a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};
template <bool del, typename Class, typename A1>
class ConstMemberResultCallback_0_1<
    del, void, Class, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(A1) const;
    inline ConstMemberResultCallback_0_1(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(a1);
        } else {
            (instance_->*method_)(a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType, typename A1>
inline typename ConstMemberResultCallback_0_1<true, RetType, Caller, A1>::base*
MakeCallback(const Caller* instance, RetType (Callee::*method)(A1) const) {
    return new ConstMemberResultCallback_0_1<true, RetType, Caller, A1>(
        instance, method);
}

template <typename Caller, typename Callee, typename RetType, typename A1>
inline typename ConstMemberResultCallback_0_1<false, RetType, Caller, A1>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(A1) const) {
    return new ConstMemberResultCallback_0_1<false, RetType, Caller, A1>(
        instance, method);
}
template <bool del, typename RetType, typename Class, typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_0_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(A1);
    inline MemberResultCallback_0_1(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(a1);
        } else {
            RetType result = (instance_->*method_)(a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
};
template <bool del, typename Class, typename A1>
class MemberResultCallback_0_1<
    del, void, Class, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(A1);
    inline MemberResultCallback_0_1(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(a1);
        } else {
            (instance_->*method_)(a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType, typename A1>
inline typename MemberResultCallback_0_1<true, RetType, Caller, A1>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(A1)) {
    return new MemberResultCallback_0_1<true, RetType, Caller, A1>(instance,
                                                                   method);
}

template <typename Caller, typename Callee, typename RetType, typename A1>
inline typename MemberResultCallback_0_1<false, RetType, Caller, A1>::base*
MakePermanentCallback(Caller* instance, RetType (Callee::*method)(A1)) {
    return new MemberResultCallback_0_1<false, RetType, Caller, A1>(instance,
                                                                    method);
}
template <bool del, typename RetType, typename A1>
class FunctionResultCallback_0_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (*Function)(A1);
    inline FunctionResultCallback_0_1(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (*function_)(a1);
        } else {
            RetType result = (*function_)(a1);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
};
template <bool del, typename A1>
class FunctionResultCallback_0_1<del, void, A1> : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (*Function)(A1);
    inline FunctionResultCallback_0_1(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (*function_)(a1);
        } else {
            (*function_)(a1);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
};

template <typename RetType, typename A1>
inline typename FunctionResultCallback_0_1<true, RetType, A1>::base*
MakeCallback(RetType (*function)(A1)) {
    return new FunctionResultCallback_0_1<true, RetType, A1>(function);
}

template <typename RetType, typename A1>
inline typename FunctionResultCallback_0_1<false, RetType, A1>::base*
MakePermanentCallback(RetType (*function)(A1)) {
    return new FunctionResultCallback_0_1<false, RetType, A1>(function);
}
template <bool del, typename RetType, typename Class, typename A1, typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_0_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(A1, A2) const;
    inline ConstMemberResultCallback_0_2(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(a1, a2);
        } else {
            RetType result = (instance_->*method_)(a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};
template <bool del, typename Class, typename A1, typename A2>
class ConstMemberResultCallback_0_2<
    del, void, Class, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(A1, A2) const;
    inline ConstMemberResultCallback_0_2(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(a1, a2);
        } else {
            (instance_->*method_)(a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2>
inline
    typename ConstMemberResultCallback_0_2<true, RetType, Caller, A1, A2>::base*
    MakeCallback(const Caller* instance,
                 RetType (Callee::*method)(A1, A2) const) {
    return new ConstMemberResultCallback_0_2<true, RetType, Caller, A1, A2>(
        instance, method);
}

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2>
inline typename ConstMemberResultCallback_0_2<false, RetType, Caller, A1,
                                              A2>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(A1, A2) const) {
    return new ConstMemberResultCallback_0_2<false, RetType, Caller, A1, A2>(
        instance, method);
}
template <bool del, typename RetType, typename Class, typename A1, typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_0_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(A1, A2);
    inline MemberResultCallback_0_2(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(a1, a2);
        } else {
            RetType result = (instance_->*method_)(a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
};
template <bool del, typename Class, typename A1, typename A2>
class MemberResultCallback_0_2<
    del, void, Class, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(A1, A2);
    inline MemberResultCallback_0_2(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(a1, a2);
        } else {
            (instance_->*method_)(a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2>
inline typename MemberResultCallback_0_2<true, RetType, Caller, A1, A2>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(A1, A2)) {
    return new MemberResultCallback_0_2<true, RetType, Caller, A1, A2>(instance,
                                                                       method);
}

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2>
inline typename MemberResultCallback_0_2<false, RetType, Caller, A1, A2>::base*
MakePermanentCallback(Caller* instance, RetType (Callee::*method)(A1, A2)) {
    return new MemberResultCallback_0_2<false, RetType, Caller, A1, A2>(
        instance, method);
}
template <bool del, typename RetType, typename A1, typename A2>
class FunctionResultCallback_0_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (*Function)(A1, A2);
    inline FunctionResultCallback_0_2(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (*function_)(a1, a2);
        } else {
            RetType result = (*function_)(a1, a2);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
};
template <bool del, typename A1, typename A2>
class FunctionResultCallback_0_2<del, void, A1, A2> : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (*Function)(A1, A2);
    inline FunctionResultCallback_0_2(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (*function_)(a1, a2);
        } else {
            (*function_)(a1, a2);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
};

template <typename RetType, typename A1, typename A2>
inline typename FunctionResultCallback_0_2<true, RetType, A1, A2>::base*
MakeCallback(RetType (*function)(A1, A2)) {
    return new FunctionResultCallback_0_2<true, RetType, A1, A2>(function);
}

template <typename RetType, typename A1, typename A2>
inline typename FunctionResultCallback_0_2<false, RetType, A1, A2>::base*
MakePermanentCallback(RetType (*function)(A1, A2)) {
    return new FunctionResultCallback_0_2<false, RetType, A1, A2>(function);
}
template <bool del, typename RetType, typename Class, typename A1, typename A2,
          typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_0_3
    : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(A1, A2, A3) const;
    inline ConstMemberResultCallback_0_3(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};
template <bool del, typename Class, typename A1, typename A2, typename A3>
class ConstMemberResultCallback_0_3<
    del, void, Class, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(A1, A2, A3) const;
    inline ConstMemberResultCallback_0_3(const Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(a1, a2, a3);
        } else {
            (instance_->*method_)(a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2, typename A3>
inline typename ConstMemberResultCallback_0_3<true, RetType, Caller, A1, A2,
                                              A3>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(A1, A2, A3) const) {
    return new ConstMemberResultCallback_0_3<true, RetType, Caller, A1, A2, A3>(
        instance, method);
}

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2, typename A3>
inline typename ConstMemberResultCallback_0_3<false, RetType, Caller, A1, A2,
                                              A3>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(A1, A2, A3) const) {
    return new ConstMemberResultCallback_0_3<false, RetType, Caller, A1, A2,
                                             A3>(instance, method);
}
template <bool del, typename RetType, typename Class, typename A1, typename A2,
          typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_0_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(A1, A2, A3);
    inline MemberResultCallback_0_3(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
};
template <bool del, typename Class, typename A1, typename A2, typename A3>
class MemberResultCallback_0_3<
    del, void, Class, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(A1, A2, A3);
    inline MemberResultCallback_0_3(Class* instance, Method method)
        : instance_(instance), method_(method) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(a1, a2, a3);
        } else {
            (instance_->*method_)(a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
};

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2, typename A3>
inline
    typename MemberResultCallback_0_3<true, RetType, Caller, A1, A2, A3>::base*
    MakeCallback(Caller* instance, RetType (Callee::*method)(A1, A2, A3)) {
    return new MemberResultCallback_0_3<true, RetType, Caller, A1, A2, A3>(
        instance, method);
}

template <typename Caller, typename Callee, typename RetType, typename A1,
          typename A2, typename A3>
inline
    typename MemberResultCallback_0_3<false, RetType, Caller, A1, A2, A3>::base*
    MakePermanentCallback(Caller* instance,
                          RetType (Callee::*method)(A1, A2, A3)) {
    return new MemberResultCallback_0_3<false, RetType, Caller, A1, A2, A3>(
        instance, method);
}
template <bool del, typename RetType, typename A1, typename A2, typename A3>
class FunctionResultCallback_0_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (*Function)(A1, A2, A3);
    inline FunctionResultCallback_0_3(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (*function_)(a1, a2, a3);
        } else {
            RetType result = (*function_)(a1, a2, a3);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
};
template <bool del, typename A1, typename A2, typename A3>
class FunctionResultCallback_0_3<del, void, A1, A2, A3>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (*Function)(A1, A2, A3);
    inline FunctionResultCallback_0_3(Function function)
        : function_(function) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (*function_)(a1, a2, a3);
        } else {
            (*function_)(a1, a2, a3);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
};

template <typename RetType, typename A1, typename A2, typename A3>
inline typename FunctionResultCallback_0_3<true, RetType, A1, A2, A3>::base*
MakeCallback(RetType (*function)(A1, A2, A3)) {
    return new FunctionResultCallback_0_3<true, RetType, A1, A2, A3>(function);
}

template <typename RetType, typename A1, typename A2, typename A3>
inline typename FunctionResultCallback_0_3<false, RetType, A1, A2, A3>::base*
MakePermanentCallback(RetType (*function)(A1, A2, A3)) {
    return new FunctionResultCallback_0_3<false, RetType, A1, A2, A3>(function);
}
template <bool del, typename RetType, typename Class, typename P1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_1_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)(P1) const;
    inline ConstMemberResultCallback_1_0(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)(p1_);
        } else {
            RetType result = (instance_->*method_)(p1_);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1>
class ConstMemberResultCallback_1_0<
    del, void, Class, P1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)(P1) const;
    inline ConstMemberResultCallback_1_0(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)(p1_);
        } else {
            (instance_->*method_)(p1_);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1>
inline typename ConstMemberResultCallback_1_0<true, RetType, Caller, P1>::base*
MakeCallback(const Caller* instance, RetType (Callee::*method)(P1) const,
             typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_0<true, RetType, Caller, P1>(
        instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1>
inline typename ConstMemberResultCallback_1_0<false, RetType, Caller, P1>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1) const,
                      typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_0<false, RetType, Caller, P1>(
        instance, method, p1);
}
template <bool del, typename RetType, typename Class, typename P1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_1_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)(P1);
    inline MemberResultCallback_1_0(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)(p1_);
        } else {
            RetType result = (instance_->*method_)(p1_);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1>
class MemberResultCallback_1_0<
    del, void, Class, P1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)(P1);
    inline MemberResultCallback_1_0(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)(p1_);
        } else {
            (instance_->*method_)(p1_);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1>
inline typename MemberResultCallback_1_0<true, RetType, Caller, P1>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1),
             typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_0<true, RetType, Caller, P1>(instance,
                                                                   method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1>
inline typename MemberResultCallback_1_0<false, RetType, Caller, P1>::base*
MakePermanentCallback(Caller* instance, RetType (Callee::*method)(P1),
                      typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_0<false, RetType, Caller, P1>(instance,
                                                                    method, p1);
}
template <bool del, typename RetType, typename P1>
class FunctionResultCallback_1_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (*Function)(P1);
    inline FunctionResultCallback_1_0(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (*function_)(p1_);
        } else {
            RetType result = (*function_)(p1_);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename P1>
class FunctionResultCallback_1_0<del, void, P1> : public Callback {
  public:
    typedef Callback base;
    typedef void (*Function)(P1);
    inline FunctionResultCallback_1_0(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (*function_)(p1_);
        } else {
            (*function_)(p1_);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename RetType, typename P1>
inline typename FunctionResultCallback_1_0<true, RetType, P1>::base*
MakeCallback(RetType (*function)(P1),
             typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_0<true, RetType, P1>(function, p1);
}

template <typename RetType, typename P1>
inline typename FunctionResultCallback_1_0<false, RetType, P1>::base*
MakePermanentCallback(RetType (*function)(P1),
                      typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_0<false, RetType, P1>(function, p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_1_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(P1, A1) const;
    inline ConstMemberResultCallback_1_1(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(p1_, a1);
        } else {
            RetType result = (instance_->*method_)(p1_, a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1, typename A1>
class ConstMemberResultCallback_1_1<
    del, void, Class, P1, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(P1, A1) const;
    inline ConstMemberResultCallback_1_1(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(p1_, a1);
        } else {
            (instance_->*method_)(p1_, a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1>
inline
    typename ConstMemberResultCallback_1_1<true, RetType, Caller, P1, A1>::base*
    MakeCallback(const Caller* instance,
                 RetType (Callee::*method)(P1, A1) const,
                 typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_1<true, RetType, Caller, P1, A1>(
        instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1>
inline typename ConstMemberResultCallback_1_1<false, RetType, Caller, P1,
                                              A1>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, A1) const,
                      typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_1<false, RetType, Caller, P1, A1>(
        instance, method, p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_1_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(P1, A1);
    inline MemberResultCallback_1_1(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(p1_, a1);
        } else {
            RetType result = (instance_->*method_)(p1_, a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1, typename A1>
class MemberResultCallback_1_1<
    del, void, Class, P1, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(P1, A1);
    inline MemberResultCallback_1_1(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(p1_, a1);
        } else {
            (instance_->*method_)(p1_, a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1>
inline typename MemberResultCallback_1_1<true, RetType, Caller, P1, A1>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, A1),
             typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_1<true, RetType, Caller, P1, A1>(
        instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1>
inline typename MemberResultCallback_1_1<false, RetType, Caller, P1, A1>::base*
MakePermanentCallback(Caller* instance, RetType (Callee::*method)(P1, A1),
                      typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_1<false, RetType, Caller, P1, A1>(
        instance, method, p1);
}
template <bool del, typename RetType, typename P1, typename A1>
class FunctionResultCallback_1_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (*Function)(P1, A1);
    inline FunctionResultCallback_1_1(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (*function_)(p1_, a1);
        } else {
            RetType result = (*function_)(p1_, a1);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename P1, typename A1>
class FunctionResultCallback_1_1<del, void, P1, A1> : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (*Function)(P1, A1);
    inline FunctionResultCallback_1_1(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (*function_)(p1_, a1);
        } else {
            (*function_)(p1_, a1);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename RetType, typename P1, typename A1>
inline typename FunctionResultCallback_1_1<true, RetType, P1, A1>::base*
MakeCallback(RetType (*function)(P1, A1),
             typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_1<true, RetType, P1, A1>(function, p1);
}

template <typename RetType, typename P1, typename A1>
inline typename FunctionResultCallback_1_1<false, RetType, P1, A1>::base*
MakePermanentCallback(RetType (*function)(P1, A1),
                      typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_1<false, RetType, P1, A1>(function, p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename A1,
          typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_1_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(P1, A1, A2) const;
    inline ConstMemberResultCallback_1_2(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(p1_, a1, a2);
        } else {
            RetType result = (instance_->*method_)(p1_, a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1, typename A1, typename A2>
class ConstMemberResultCallback_1_2<
    del, void, Class, P1, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(P1, A1, A2) const;
    inline ConstMemberResultCallback_1_2(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(p1_, a1, a2);
        } else {
            (instance_->*method_)(p1_, a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2>
inline typename ConstMemberResultCallback_1_2<true, RetType, Caller, P1, A1,
                                              A2>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, A1, A2) const,
             typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_2<true, RetType, Caller, P1, A1, A2>(
        instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2>
inline typename ConstMemberResultCallback_1_2<false, RetType, Caller, P1, A1,
                                              A2>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, A1, A2) const,
                      typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_2<false, RetType, Caller, P1, A1,
                                             A2>(instance, method, p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename A1,
          typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_1_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(P1, A1, A2);
    inline MemberResultCallback_1_2(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(p1_, a1, a2);
        } else {
            RetType result = (instance_->*method_)(p1_, a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1, typename A1, typename A2>
class MemberResultCallback_1_2<
    del, void, Class, P1, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(P1, A1, A2);
    inline MemberResultCallback_1_2(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(p1_, a1, a2);
        } else {
            (instance_->*method_)(p1_, a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2>
inline
    typename MemberResultCallback_1_2<true, RetType, Caller, P1, A1, A2>::base*
    MakeCallback(Caller* instance, RetType (Callee::*method)(P1, A1, A2),
                 typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_2<true, RetType, Caller, P1, A1, A2>(
        instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2>
inline
    typename MemberResultCallback_1_2<false, RetType, Caller, P1, A1, A2>::base*
    MakePermanentCallback(Caller* instance,
                          RetType (Callee::*method)(P1, A1, A2),
                          typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_2<false, RetType, Caller, P1, A1, A2>(
        instance, method, p1);
}
template <bool del, typename RetType, typename P1, typename A1, typename A2>
class FunctionResultCallback_1_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (*Function)(P1, A1, A2);
    inline FunctionResultCallback_1_2(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (*function_)(p1_, a1, a2);
        } else {
            RetType result = (*function_)(p1_, a1, a2);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename P1, typename A1, typename A2>
class FunctionResultCallback_1_2<del, void, P1, A1, A2>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (*Function)(P1, A1, A2);
    inline FunctionResultCallback_1_2(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (*function_)(p1_, a1, a2);
        } else {
            (*function_)(p1_, a1, a2);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename RetType, typename P1, typename A1, typename A2>
inline typename FunctionResultCallback_1_2<true, RetType, P1, A1, A2>::base*
MakeCallback(RetType (*function)(P1, A1, A2),
             typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_2<true, RetType, P1, A1, A2>(function,
                                                                     p1);
}

template <typename RetType, typename P1, typename A1, typename A2>
inline typename FunctionResultCallback_1_2<false, RetType, P1, A1, A2>::base*
MakePermanentCallback(RetType (*function)(P1, A1, A2),
                      typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_2<false, RetType, P1, A1, A2>(function,
                                                                      p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename A1,
          typename A2, typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_1_3
    : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(P1, A1, A2, A3) const;
    inline ConstMemberResultCallback_1_3(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(p1_, a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(p1_, a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1, typename A1, typename A2,
          typename A3>
class ConstMemberResultCallback_1_3<
    del, void, Class, P1, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(P1, A1, A2, A3) const;
    inline ConstMemberResultCallback_1_3(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(p1_, a1, a2, a3);
        } else {
            (instance_->*method_)(p1_, a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2, typename A3>
inline typename ConstMemberResultCallback_1_3<true, RetType, Caller, P1, A1, A2,
                                              A3>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, A1, A2, A3) const,
             typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_3<true, RetType, Caller, P1, A1, A2,
                                             A3>(instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2, typename A3>
inline typename ConstMemberResultCallback_1_3<false, RetType, Caller, P1, A1,
                                              A2, A3>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, A1, A2, A3) const,
                      typename internal::ConstRef<P1>::type p1) {
    return new ConstMemberResultCallback_1_3<false, RetType, Caller, P1, A1, A2,
                                             A3>(instance, method, p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename A1,
          typename A2, typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_1_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(P1, A1, A2, A3);
    inline MemberResultCallback_1_3(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(p1_, a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(p1_, a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename Class, typename P1, typename A1, typename A2,
          typename A3>
class MemberResultCallback_1_3<
    del, void, Class, P1, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(P1, A1, A2, A3);
    inline MemberResultCallback_1_3(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1)
        : instance_(instance), method_(method), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(p1_, a1, a2, a3);
        } else {
            (instance_->*method_)(p1_, a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2, typename A3>
inline typename MemberResultCallback_1_3<true, RetType, Caller, P1, A1, A2,
                                         A3>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, A1, A2, A3),
             typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_3<true, RetType, Caller, P1, A1, A2, A3>(
        instance, method, p1);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename A1, typename A2, typename A3>
inline typename MemberResultCallback_1_3<false, RetType, Caller, P1, A1, A2,
                                         A3>::base*
MakePermanentCallback(Caller* instance,
                      RetType (Callee::*method)(P1, A1, A2, A3),
                      typename internal::ConstRef<P1>::type p1) {
    return new MemberResultCallback_1_3<false, RetType, Caller, P1, A1, A2, A3>(
        instance, method, p1);
}
template <bool del, typename RetType, typename P1, typename A1, typename A2,
          typename A3>
class FunctionResultCallback_1_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (*Function)(P1, A1, A2, A3);
    inline FunctionResultCallback_1_3(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (*function_)(p1_, a1, a2, a3);
        } else {
            RetType result = (*function_)(p1_, a1, a2, a3);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};
template <bool del, typename P1, typename A1, typename A2, typename A3>
class FunctionResultCallback_1_3<del, void, P1, A1, A2, A3>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (*Function)(P1, A1, A2, A3);
    inline FunctionResultCallback_1_3(Function function,
                                      typename internal::ConstRef<P1>::type p1)
        : function_(function), p1_(p1) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (*function_)(p1_, a1, a2, a3);
        } else {
            (*function_)(p1_, a1, a2, a3);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
};

template <typename RetType, typename P1, typename A1, typename A2, typename A3>
inline typename FunctionResultCallback_1_3<true, RetType, P1, A1, A2, A3>::base*
MakeCallback(RetType (*function)(P1, A1, A2, A3),
             typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_3<true, RetType, P1, A1, A2, A3>(
        function, p1);
}

template <typename RetType, typename P1, typename A1, typename A2, typename A3>
inline
    typename FunctionResultCallback_1_3<false, RetType, P1, A1, A2, A3>::base*
    MakePermanentCallback(RetType (*function)(P1, A1, A2, A3),
                          typename internal::ConstRef<P1>::type p1) {
    return new FunctionResultCallback_1_3<false, RetType, P1, A1, A2, A3>(
        function, p1);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_2_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)(P1, P2) const;
    inline ConstMemberResultCallback_2_0(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2>
class ConstMemberResultCallback_2_0<
    del, void, Class, P1, P2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)(P1, P2) const;
    inline ConstMemberResultCallback_2_0(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)(p1_, p2_);
        } else {
            (instance_->*method_)(p1_, p2_);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2>
inline
    typename ConstMemberResultCallback_2_0<true, RetType, Caller, P1, P2>::base*
    MakeCallback(const Caller* instance,
                 RetType (Callee::*method)(P1, P2) const,
                 typename internal::ConstRef<P1>::type p1,
                 typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_0<true, RetType, Caller, P1, P2>(
        instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2>
inline typename ConstMemberResultCallback_2_0<false, RetType, Caller, P1,
                                              P2>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_0<false, RetType, Caller, P1, P2>(
        instance, method, p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_2_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)(P1, P2);
    inline MemberResultCallback_2_0(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2>
class MemberResultCallback_2_0<
    del, void, Class, P1, P2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)(P1, P2);
    inline MemberResultCallback_2_0(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)(p1_, p2_);
        } else {
            (instance_->*method_)(p1_, p2_);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2>
inline typename MemberResultCallback_2_0<true, RetType, Caller, P1, P2>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_0<true, RetType, Caller, P1, P2>(
        instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2>
inline typename MemberResultCallback_2_0<false, RetType, Caller, P1, P2>::base*
MakePermanentCallback(Caller* instance, RetType (Callee::*method)(P1, P2),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_0<false, RetType, Caller, P1, P2>(
        instance, method, p1, p2);
}
template <bool del, typename RetType, typename P1, typename P2>
class FunctionResultCallback_2_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (*Function)(P1, P2);
    inline FunctionResultCallback_2_0(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (*function_)(p1_, p2_);
        } else {
            RetType result = (*function_)(p1_, p2_);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename P1, typename P2>
class FunctionResultCallback_2_0<del, void, P1, P2> : public Callback {
  public:
    typedef Callback base;
    typedef void (*Function)(P1, P2);
    inline FunctionResultCallback_2_0(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (*function_)(p1_, p2_);
        } else {
            (*function_)(p1_, p2_);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename RetType, typename P1, typename P2>
inline typename FunctionResultCallback_2_0<true, RetType, P1, P2>::base*
MakeCallback(RetType (*function)(P1, P2),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_0<true, RetType, P1, P2>(function, p1,
                                                                 p2);
}

template <typename RetType, typename P1, typename P2>
inline typename FunctionResultCallback_2_0<false, RetType, P1, P2>::base*
MakePermanentCallback(RetType (*function)(P1, P2),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_0<false, RetType, P1, P2>(function, p1,
                                                                  p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_2_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(P1, P2, A1) const;
    inline ConstMemberResultCallback_2_1(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, a1);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2, typename A1>
class ConstMemberResultCallback_2_1<
    del, void, Class, P1, P2, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(P1, P2, A1) const;
    inline ConstMemberResultCallback_2_1(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, a1);
        } else {
            (instance_->*method_)(p1_, p2_, a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1>
inline typename ConstMemberResultCallback_2_1<true, RetType, Caller, P1, P2,
                                              A1>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, A1) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_1<true, RetType, Caller, P1, P2, A1>(
        instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1>
inline typename ConstMemberResultCallback_2_1<false, RetType, Caller, P1, P2,
                                              A1>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, A1) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_1<false, RetType, Caller, P1, P2,
                                             A1>(instance, method, p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_2_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(P1, P2, A1);
    inline MemberResultCallback_2_1(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, a1);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2, typename A1>
class MemberResultCallback_2_1<
    del, void, Class, P1, P2, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(P1, P2, A1);
    inline MemberResultCallback_2_1(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, a1);
        } else {
            (instance_->*method_)(p1_, p2_, a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1>
inline
    typename MemberResultCallback_2_1<true, RetType, Caller, P1, P2, A1>::base*
    MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2, A1),
                 typename internal::ConstRef<P1>::type p1,
                 typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_1<true, RetType, Caller, P1, P2, A1>(
        instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1>
inline
    typename MemberResultCallback_2_1<false, RetType, Caller, P1, P2, A1>::base*
    MakePermanentCallback(Caller* instance,
                          RetType (Callee::*method)(P1, P2, A1),
                          typename internal::ConstRef<P1>::type p1,
                          typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_1<false, RetType, Caller, P1, P2, A1>(
        instance, method, p1, p2);
}
template <bool del, typename RetType, typename P1, typename P2, typename A1>
class FunctionResultCallback_2_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (*Function)(P1, P2, A1);
    inline FunctionResultCallback_2_1(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (*function_)(p1_, p2_, a1);
        } else {
            RetType result = (*function_)(p1_, p2_, a1);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename P1, typename P2, typename A1>
class FunctionResultCallback_2_1<del, void, P1, P2, A1> : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (*Function)(P1, P2, A1);
    inline FunctionResultCallback_2_1(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (*function_)(p1_, p2_, a1);
        } else {
            (*function_)(p1_, p2_, a1);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename RetType, typename P1, typename P2, typename A1>
inline typename FunctionResultCallback_2_1<true, RetType, P1, P2, A1>::base*
MakeCallback(RetType (*function)(P1, P2, A1),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_1<true, RetType, P1, P2, A1>(function,
                                                                     p1, p2);
}

template <typename RetType, typename P1, typename P2, typename A1>
inline typename FunctionResultCallback_2_1<false, RetType, P1, P2, A1>::base*
MakePermanentCallback(RetType (*function)(P1, P2, A1),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_1<false, RetType, P1, P2, A1>(function,
                                                                      p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename A1, typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_2_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(P1, P2, A1, A2) const;
    inline ConstMemberResultCallback_2_2(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, a1, a2);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2, typename A1,
          typename A2>
class ConstMemberResultCallback_2_2<
    del, void, Class, P1, P2, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(P1, P2, A1, A2) const;
    inline ConstMemberResultCallback_2_2(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, a1, a2);
        } else {
            (instance_->*method_)(p1_, p2_, a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2>
inline typename ConstMemberResultCallback_2_2<true, RetType, Caller, P1, P2, A1,
                                              A2>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, A1, A2) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_2<true, RetType, Caller, P1, P2, A1,
                                             A2>(instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2>
inline typename ConstMemberResultCallback_2_2<false, RetType, Caller, P1, P2,
                                              A1, A2>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, A1, A2) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_2<false, RetType, Caller, P1, P2, A1,
                                             A2>(instance, method, p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename A1, typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_2_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(P1, P2, A1, A2);
    inline MemberResultCallback_2_2(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, a1, a2);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2, typename A1,
          typename A2>
class MemberResultCallback_2_2<
    del, void, Class, P1, P2, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(P1, P2, A1, A2);
    inline MemberResultCallback_2_2(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, a1, a2);
        } else {
            (instance_->*method_)(p1_, p2_, a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2>
inline typename MemberResultCallback_2_2<true, RetType, Caller, P1, P2, A1,
                                         A2>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2, A1, A2),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_2<true, RetType, Caller, P1, P2, A1, A2>(
        instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2>
inline typename MemberResultCallback_2_2<false, RetType, Caller, P1, P2, A1,
                                         A2>::base*
MakePermanentCallback(Caller* instance,
                      RetType (Callee::*method)(P1, P2, A1, A2),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_2<false, RetType, Caller, P1, P2, A1, A2>(
        instance, method, p1, p2);
}
template <bool del, typename RetType, typename P1, typename P2, typename A1,
          typename A2>
class FunctionResultCallback_2_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (*Function)(P1, P2, A1, A2);
    inline FunctionResultCallback_2_2(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (*function_)(p1_, p2_, a1, a2);
        } else {
            RetType result = (*function_)(p1_, p2_, a1, a2);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename P1, typename P2, typename A1, typename A2>
class FunctionResultCallback_2_2<del, void, P1, P2, A1, A2>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (*Function)(P1, P2, A1, A2);
    inline FunctionResultCallback_2_2(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (*function_)(p1_, p2_, a1, a2);
        } else {
            (*function_)(p1_, p2_, a1, a2);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename RetType, typename P1, typename P2, typename A1, typename A2>
inline typename FunctionResultCallback_2_2<true, RetType, P1, P2, A1, A2>::base*
MakeCallback(RetType (*function)(P1, P2, A1, A2),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_2<true, RetType, P1, P2, A1, A2>(
        function, p1, p2);
}

template <typename RetType, typename P1, typename P2, typename A1, typename A2>
inline
    typename FunctionResultCallback_2_2<false, RetType, P1, P2, A1, A2>::base*
    MakePermanentCallback(RetType (*function)(P1, P2, A1, A2),
                          typename internal::ConstRef<P1>::type p1,
                          typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_2<false, RetType, P1, P2, A1, A2>(
        function, p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename A1, typename A2, typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_2_3
    : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(P1, P2, A1, A2, A3) const;
    inline ConstMemberResultCallback_2_3(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2, typename A1,
          typename A2, typename A3>
class ConstMemberResultCallback_2_3<
    del, void, Class, P1, P2, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(P1, P2, A1, A2, A3) const;
    inline ConstMemberResultCallback_2_3(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, a1, a2, a3);
        } else {
            (instance_->*method_)(p1_, p2_, a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2, typename A3>
inline typename ConstMemberResultCallback_2_3<true, RetType, Caller, P1, P2, A1,
                                              A2, A3>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, A1, A2, A3) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_3<true, RetType, Caller, P1, P2, A1,
                                             A2, A3>(instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2, typename A3>
inline typename ConstMemberResultCallback_2_3<false, RetType, Caller, P1, P2,
                                              A1, A2, A3>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, A1, A2, A3) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new ConstMemberResultCallback_2_3<false, RetType, Caller, P1, P2, A1,
                                             A2, A3>(instance, method, p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename A1, typename A2, typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_2_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(P1, P2, A1, A2, A3);
    inline MemberResultCallback_2_3(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename Class, typename P1, typename P2, typename A1,
          typename A2, typename A3>
class MemberResultCallback_2_3<
    del, void, Class, P1, P2, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(P1, P2, A1, A2, A3);
    inline MemberResultCallback_2_3(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2)
        : instance_(instance), method_(method), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, a1, a2, a3);
        } else {
            (instance_->*method_)(p1_, p2_, a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2, typename A3>
inline typename MemberResultCallback_2_3<true, RetType, Caller, P1, P2, A1, A2,
                                         A3>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2, A1, A2, A3),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_3<true, RetType, Caller, P1, P2, A1, A2,
                                        A3>(instance, method, p1, p2);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename A1, typename A2, typename A3>
inline typename MemberResultCallback_2_3<false, RetType, Caller, P1, P2, A1, A2,
                                         A3>::base*
MakePermanentCallback(Caller* instance,
                      RetType (Callee::*method)(P1, P2, A1, A2, A3),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new MemberResultCallback_2_3<false, RetType, Caller, P1, P2, A1, A2,
                                        A3>(instance, method, p1, p2);
}
template <bool del, typename RetType, typename P1, typename P2, typename A1,
          typename A2, typename A3>
class FunctionResultCallback_2_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (*Function)(P1, P2, A1, A2, A3);
    inline FunctionResultCallback_2_3(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (*function_)(p1_, p2_, a1, a2, a3);
        } else {
            RetType result = (*function_)(p1_, p2_, a1, a2, a3);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};
template <bool del, typename P1, typename P2, typename A1, typename A2,
          typename A3>
class FunctionResultCallback_2_3<del, void, P1, P2, A1, A2, A3>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (*Function)(P1, P2, A1, A2, A3);
    inline FunctionResultCallback_2_3(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2)
        : function_(function), p1_(p1), p2_(p2) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (*function_)(p1_, p2_, a1, a2, a3);
        } else {
            (*function_)(p1_, p2_, a1, a2, a3);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
};

template <typename RetType, typename P1, typename P2, typename A1, typename A2,
          typename A3>
inline typename FunctionResultCallback_2_3<true, RetType, P1, P2, A1, A2,
                                           A3>::base*
MakeCallback(RetType (*function)(P1, P2, A1, A2, A3),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_3<true, RetType, P1, P2, A1, A2, A3>(
        function, p1, p2);
}

template <typename RetType, typename P1, typename P2, typename A1, typename A2,
          typename A3>
inline typename FunctionResultCallback_2_3<false, RetType, P1, P2, A1, A2,
                                           A3>::base*
MakePermanentCallback(RetType (*function)(P1, P2, A1, A2, A3),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2) {
    return new FunctionResultCallback_2_3<false, RetType, P1, P2, A1, A2, A3>(
        function, p1, p2);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_3_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)(P1, P2, P3) const;
    inline ConstMemberResultCallback_3_0(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3>
class ConstMemberResultCallback_3_0<
    del, void, Class, P1, P2, P3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)(P1, P2, P3) const;
    inline ConstMemberResultCallback_3_0(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_);
        } else {
            (instance_->*method_)(p1_, p2_, p3_);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3>
inline typename ConstMemberResultCallback_3_0<true, RetType, Caller, P1, P2,
                                              P3>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, P3) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_0<true, RetType, Caller, P1, P2, P3>(
        instance, method, p1, p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3>
inline typename ConstMemberResultCallback_3_0<false, RetType, Caller, P1, P2,
                                              P3>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_0<false, RetType, Caller, P1, P2,
                                             P3>(instance, method, p1, p2, p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_3_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (Class::*Method)(P1, P2, P3);
    inline MemberResultCallback_3_0(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3>
class MemberResultCallback_3_0<
    del, void, Class, P1, P2, P3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback {
  public:
    typedef Callback base;
    typedef void (Class::*Method)(P1, P2, P3);
    inline MemberResultCallback_3_0(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_);
        } else {
            (instance_->*method_)(p1_, p2_, p3_);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3>
inline
    typename MemberResultCallback_3_0<true, RetType, Caller, P1, P2, P3>::base*
    MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2, P3),
                 typename internal::ConstRef<P1>::type p1,
                 typename internal::ConstRef<P2>::type p2,
                 typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_0<true, RetType, Caller, P1, P2, P3>(
        instance, method, p1, p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3>
inline
    typename MemberResultCallback_3_0<false, RetType, Caller, P1, P2, P3>::base*
    MakePermanentCallback(Caller* instance,
                          RetType (Callee::*method)(P1, P2, P3),
                          typename internal::ConstRef<P1>::type p1,
                          typename internal::ConstRef<P2>::type p2,
                          typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_0<false, RetType, Caller, P1, P2, P3>(
        instance, method, p1, p2, p3);
}
template <bool del, typename RetType, typename P1, typename P2, typename P3>
class FunctionResultCallback_3_0 : public ResultCallback<RetType> {
  public:
    typedef ResultCallback<RetType> base;
    typedef RetType (*Function)(P1, P2, P3);
    inline FunctionResultCallback_3_0(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run() override {
        if (!del) {
            return (*function_)(p1_, p2_, p3_);
        } else {
            RetType result = (*function_)(p1_, p2_, p3_);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename P1, typename P2, typename P3>
class FunctionResultCallback_3_0<del, void, P1, P2, P3> : public Callback {
  public:
    typedef Callback base;
    typedef void (*Function)(P1, P2, P3);
    inline FunctionResultCallback_3_0(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run() override {
        if (!del) {
            (*function_)(p1_, p2_, p3_);
        } else {
            (*function_)(p1_, p2_, p3_);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename RetType, typename P1, typename P2, typename P3>
inline typename FunctionResultCallback_3_0<true, RetType, P1, P2, P3>::base*
MakeCallback(RetType (*function)(P1, P2, P3),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_0<true, RetType, P1, P2, P3>(
        function, p1, p2, p3);
}

template <typename RetType, typename P1, typename P2, typename P3>
inline typename FunctionResultCallback_3_0<false, RetType, P1, P2, P3>::base*
MakePermanentCallback(RetType (*function)(P1, P2, P3),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_0<false, RetType, P1, P2, P3>(
        function, p1, p2, p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3, typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_3_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(P1, P2, P3, A1) const;
    inline ConstMemberResultCallback_3_1(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_, a1);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_, a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3,
          typename A1>
class ConstMemberResultCallback_3_1<
    del, void, Class, P1, P2, P3, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(P1, P2, P3, A1) const;
    inline ConstMemberResultCallback_3_1(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_, a1);
        } else {
            (instance_->*method_)(p1_, p2_, p3_, a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1>
inline typename ConstMemberResultCallback_3_1<true, RetType, Caller, P1, P2, P3,
                                              A1>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, P3, A1) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_1<true, RetType, Caller, P1, P2, P3,
                                             A1>(instance, method, p1, p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1>
inline typename ConstMemberResultCallback_3_1<false, RetType, Caller, P1, P2,
                                              P3, A1>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3, A1) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_1<false, RetType, Caller, P1, P2, P3,
                                             A1>(instance, method, p1, p2, p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3, typename A1,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_3_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (Class::*Method)(P1, P2, P3, A1);
    inline MemberResultCallback_3_1(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_, a1);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_, a1);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3,
          typename A1>
class MemberResultCallback_3_1<
    del, void, Class, P1, P2, P3, A1,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (Class::*Method)(P1, P2, P3, A1);
    inline MemberResultCallback_3_1(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_, a1);
        } else {
            (instance_->*method_)(p1_, p2_, p3_, a1);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1>
inline typename MemberResultCallback_3_1<true, RetType, Caller, P1, P2, P3,
                                         A1>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2, P3, A1),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_1<true, RetType, Caller, P1, P2, P3, A1>(
        instance, method, p1, p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1>
inline typename MemberResultCallback_3_1<false, RetType, Caller, P1, P2, P3,
                                         A1>::base*
MakePermanentCallback(Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3, A1),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_1<false, RetType, Caller, P1, P2, P3, A1>(
        instance, method, p1, p2, p3);
}
template <bool del, typename RetType, typename P1, typename P2, typename P3,
          typename A1>
class FunctionResultCallback_3_1 : public ResultCallback1<RetType, A1> {
  public:
    typedef ResultCallback1<RetType, A1> base;
    typedef RetType (*Function)(P1, P2, P3, A1);
    inline FunctionResultCallback_3_1(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1) override {
        if (!del) {
            return (*function_)(p1_, p2_, p3_, a1);
        } else {
            RetType result = (*function_)(p1_, p2_, p3_, a1);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename P1, typename P2, typename P3, typename A1>
class FunctionResultCallback_3_1<del, void, P1, P2, P3, A1>
    : public Callback1<A1> {
  public:
    typedef Callback1<A1> base;
    typedef void (*Function)(P1, P2, P3, A1);
    inline FunctionResultCallback_3_1(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1) override {
        if (!del) {
            (*function_)(p1_, p2_, p3_, a1);
        } else {
            (*function_)(p1_, p2_, p3_, a1);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename RetType, typename P1, typename P2, typename P3, typename A1>
inline typename FunctionResultCallback_3_1<true, RetType, P1, P2, P3, A1>::base*
MakeCallback(RetType (*function)(P1, P2, P3, A1),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_1<true, RetType, P1, P2, P3, A1>(
        function, p1, p2, p3);
}

template <typename RetType, typename P1, typename P2, typename P3, typename A1>
inline
    typename FunctionResultCallback_3_1<false, RetType, P1, P2, P3, A1>::base*
    MakePermanentCallback(RetType (*function)(P1, P2, P3, A1),
                          typename internal::ConstRef<P1>::type p1,
                          typename internal::ConstRef<P2>::type p2,
                          typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_1<false, RetType, P1, P2, P3, A1>(
        function, p1, p2, p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3, typename A1, typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_3_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(P1, P2, P3, A1, A2) const;
    inline ConstMemberResultCallback_3_2(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_, a1, a2);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_, a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3,
          typename A1, typename A2>
class ConstMemberResultCallback_3_2<
    del, void, Class, P1, P2, P3, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(P1, P2, P3, A1, A2) const;
    inline ConstMemberResultCallback_3_2(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2);
        } else {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2>
inline typename ConstMemberResultCallback_3_2<true, RetType, Caller, P1, P2, P3,
                                              A1, A2>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, P3, A1, A2) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_2<true, RetType, Caller, P1, P2, P3,
                                             A1, A2>(instance, method, p1, p2,
                                                     p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2>
inline typename ConstMemberResultCallback_3_2<false, RetType, Caller, P1, P2,
                                              P3, A1, A2>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3, A1, A2) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_2<false, RetType, Caller, P1, P2, P3,
                                             A1, A2>(instance, method, p1, p2,
                                                     p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3, typename A1, typename A2,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_3_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (Class::*Method)(P1, P2, P3, A1, A2);
    inline MemberResultCallback_3_2(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_, a1, a2);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_, a1, a2);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3,
          typename A1, typename A2>
class MemberResultCallback_3_2<
    del, void, Class, P1, P2, P3, A1, A2,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (Class::*Method)(P1, P2, P3, A1, A2);
    inline MemberResultCallback_3_2(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2);
        } else {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2>
inline typename MemberResultCallback_3_2<true, RetType, Caller, P1, P2, P3, A1,
                                         A2>::base*
MakeCallback(Caller* instance, RetType (Callee::*method)(P1, P2, P3, A1, A2),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_2<true, RetType, Caller, P1, P2, P3, A1,
                                        A2>(instance, method, p1, p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2>
inline typename MemberResultCallback_3_2<false, RetType, Caller, P1, P2, P3, A1,
                                         A2>::base*
MakePermanentCallback(Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3, A1, A2),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_2<false, RetType, Caller, P1, P2, P3, A1,
                                        A2>(instance, method, p1, p2, p3);
}
template <bool del, typename RetType, typename P1, typename P2, typename P3,
          typename A1, typename A2>
class FunctionResultCallback_3_2 : public ResultCallback2<RetType, A1, A2> {
  public:
    typedef ResultCallback2<RetType, A1, A2> base;
    typedef RetType (*Function)(P1, P2, P3, A1, A2);
    inline FunctionResultCallback_3_2(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2) override {
        if (!del) {
            return (*function_)(p1_, p2_, p3_, a1, a2);
        } else {
            RetType result = (*function_)(p1_, p2_, p3_, a1, a2);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename P1, typename P2, typename P3, typename A1,
          typename A2>
class FunctionResultCallback_3_2<del, void, P1, P2, P3, A1, A2>
    : public Callback2<A1, A2> {
  public:
    typedef Callback2<A1, A2> base;
    typedef void (*Function)(P1, P2, P3, A1, A2);
    inline FunctionResultCallback_3_2(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2) override {
        if (!del) {
            (*function_)(p1_, p2_, p3_, a1, a2);
        } else {
            (*function_)(p1_, p2_, p3_, a1, a2);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename RetType, typename P1, typename P2, typename P3, typename A1,
          typename A2>
inline typename FunctionResultCallback_3_2<true, RetType, P1, P2, P3, A1,
                                           A2>::base*
MakeCallback(RetType (*function)(P1, P2, P3, A1, A2),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_2<true, RetType, P1, P2, P3, A1, A2>(
        function, p1, p2, p3);
}

template <typename RetType, typename P1, typename P2, typename P3, typename A1,
          typename A2>
inline typename FunctionResultCallback_3_2<false, RetType, P1, P2, P3, A1,
                                           A2>::base*
MakePermanentCallback(RetType (*function)(P1, P2, P3, A1, A2),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_2<false, RetType, P1, P2, P3, A1, A2>(
        function, p1, p2, p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3, typename A1, typename A2, typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class ConstMemberResultCallback_3_3
    : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(P1, P2, P3, A1, A2, A3) const;
    inline ConstMemberResultCallback_3_3(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3,
          typename A1, typename A2, typename A3>
class ConstMemberResultCallback_3_3<
    del, void, Class, P1, P2, P3, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(P1, P2, P3, A1, A2, A3) const;
    inline ConstMemberResultCallback_3_3(
        const Class* instance, Method method,
        typename internal::ConstRef<P1>::type p1,
        typename internal::ConstRef<P2>::type p2,
        typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
        } else {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    const Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2, typename A3>
inline typename ConstMemberResultCallback_3_3<true, RetType, Caller, P1, P2, P3,
                                              A1, A2, A3>::base*
MakeCallback(const Caller* instance,
             RetType (Callee::*method)(P1, P2, P3, A1, A2, A3) const,
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_3<true, RetType, Caller, P1, P2, P3,
                                             A1, A2, A3>(instance, method, p1,
                                                         p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2, typename A3>
inline typename ConstMemberResultCallback_3_3<false, RetType, Caller, P1, P2,
                                              P3, A1, A2, A3>::base*
MakePermanentCallback(const Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3, A1, A2, A3) const,
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new ConstMemberResultCallback_3_3<false, RetType, Caller, P1, P2, P3,
                                             A1, A2, A3>(instance, method, p1,
                                                         p2, p3);
}
template <bool del, typename RetType, typename Class, typename P1, typename P2,
          typename P3, typename A1, typename A2, typename A3,
          typename OnlyIf =
              typename ::std::enable_if<::std::is_compound<Class>::value>::type>
class MemberResultCallback_3_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (Class::*Method)(P1, P2, P3, A1, A2, A3);
    inline MemberResultCallback_3_3(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
        } else {
            RetType result = (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
            method_        = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename Class, typename P1, typename P2, typename P3,
          typename A1, typename A2, typename A3>
class MemberResultCallback_3_3<
    del, void, Class, P1, P2, P3, A1, A2, A3,
    typename ::std::enable_if<::std::is_compound<Class>::value>::type>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (Class::*Method)(P1, P2, P3, A1, A2, A3);
    inline MemberResultCallback_3_3(Class* instance, Method method,
                                    typename internal::ConstRef<P1>::type p1,
                                    typename internal::ConstRef<P2>::type p2,
                                    typename internal::ConstRef<P3>::type p3)
        : instance_(instance), method_(method), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
        } else {
            (instance_->*method_)(p1_, p2_, p3_, a1, a2, a3);
            method_ = nullptr;
            delete this;
        }
    }

  private:
    Class* instance_;
    Method method_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2, typename A3>
inline typename MemberResultCallback_3_3<true, RetType, Caller, P1, P2, P3, A1,
                                         A2, A3>::base*
MakeCallback(Caller* instance,
             RetType (Callee::*method)(P1, P2, P3, A1, A2, A3),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_3<true, RetType, Caller, P1, P2, P3, A1,
                                        A2, A3>(instance, method, p1, p2, p3);
}

template <typename Caller, typename Callee, typename RetType, typename P1,
          typename P2, typename P3, typename A1, typename A2, typename A3>
inline typename MemberResultCallback_3_3<false, RetType, Caller, P1, P2, P3, A1,
                                         A2, A3>::base*
MakePermanentCallback(Caller* instance,
                      RetType (Callee::*method)(P1, P2, P3, A1, A2, A3),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new MemberResultCallback_3_3<false, RetType, Caller, P1, P2, P3, A1,
                                        A2, A3>(instance, method, p1, p2, p3);
}
template <bool del, typename RetType, typename P1, typename P2, typename P3,
          typename A1, typename A2, typename A3>
class FunctionResultCallback_3_3 : public ResultCallback3<RetType, A1, A2, A3> {
  public:
    typedef ResultCallback3<RetType, A1, A2, A3> base;
    typedef RetType (*Function)(P1, P2, P3, A1, A2, A3);
    inline FunctionResultCallback_3_3(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    RetType run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            return (*function_)(p1_, p2_, p3_, a1, a2, a3);
        } else {
            RetType result = (*function_)(p1_, p2_, p3_, a1, a2, a3);
            function_      = nullptr;
            delete this;
            return result;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};
template <bool del, typename P1, typename P2, typename P3, typename A1,
          typename A2, typename A3>
class FunctionResultCallback_3_3<del, void, P1, P2, P3, A1, A2, A3>
    : public Callback3<A1, A2, A3> {
  public:
    typedef Callback3<A1, A2, A3> base;
    typedef void (*Function)(P1, P2, P3, A1, A2, A3);
    inline FunctionResultCallback_3_3(Function function,
                                      typename internal::ConstRef<P1>::type p1,
                                      typename internal::ConstRef<P2>::type p2,
                                      typename internal::ConstRef<P3>::type p3)
        : function_(function), p1_(p1), p2_(p2), p3_(p3) {}
    bool isRepeatable() const override {
        return !del;
    }
    void run(A1 a1, A2 a2, A3 a3) override {
        if (!del) {
            (*function_)(p1_, p2_, p3_, a1, a2, a3);
        } else {
            (*function_)(p1_, p2_, p3_, a1, a2, a3);
            function_ = nullptr;
            delete this;
        }
    }

  private:
    Function function_;
    typename ::std::remove_reference<P1>::type p1_;
    typename ::std::remove_reference<P2>::type p2_;
    typename ::std::remove_reference<P3>::type p3_;
};

template <typename RetType, typename P1, typename P2, typename P3, typename A1,
          typename A2, typename A3>
inline typename FunctionResultCallback_3_3<true, RetType, P1, P2, P3, A1, A2,
                                           A3>::base*
MakeCallback(RetType (*function)(P1, P2, P3, A1, A2, A3),
             typename internal::ConstRef<P1>::type p1,
             typename internal::ConstRef<P2>::type p2,
             typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_3<true, RetType, P1, P2, P3, A1, A2,
                                          A3>(function, p1, p2, p3);
}

template <typename RetType, typename P1, typename P2, typename P3, typename A1,
          typename A2, typename A3>
inline typename FunctionResultCallback_3_3<false, RetType, P1, P2, P3, A1, A2,
                                           A3>::base*
MakePermanentCallback(RetType (*function)(P1, P2, P3, A1, A2, A3),
                      typename internal::ConstRef<P1>::type p1,
                      typename internal::ConstRef<P2>::type p2,
                      typename internal::ConstRef<P3>::type p3) {
    return new FunctionResultCallback_3_3<false, RetType, P1, P2, P3, A1, A2,
                                          A3>(function, p1, p2, p3);
}
}

#endif // PARAMOUNT_CALLBACK_IMPL_H
