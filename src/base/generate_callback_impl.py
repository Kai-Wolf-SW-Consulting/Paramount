#!/usr/bin/python
# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.


from argparse import ArgumentParser, ArgumentDefaultsHelpFormatter
from abc import ABCMeta, abstractmethod
from datetime import date


class ACallbackBase:
    """Base class for generating different callback types"""
    __metaclass__ = ABCMeta

    def __init__(self, num_params):
        self.num_params = num_params

    def name(self):
        """Generate callback typename with suffixed number or arguments"""
        name = self.__class__.__name__
        return name + str(self.num_params) if self.num_params else name

    def generate(self):
        """Generate callback base type (Callback|ResultCallback)"""
        params = make_enum('P%d', self.num_params) if self.num_params else ""
        cb_def = """class %s {
            public:
              virtual ~%s() {}
              virtual bool isRepeatable() const { return false; }
              virtual %s run(%s) = 0;
            protected:
              %s() {}
        };
        """ % (self.name(), self.name(), self.ret_type(), params, self.name())
        return cb_def

    def serialize(self, out_handle):
        out_handle.write(self.template_decl() + "\n")
        out_handle.write(self.generate() + "\n")

    @abstractmethod
    def ret_type(self):
        pass

    @abstractmethod
    def template_decl(self):
        pass


class Callback(ACallbackBase):
    def template_decl(self):
        if not self.num_params: return ""
        return "template <%s>" % make_enum('typename P%d', self.num_params)

    def ret_type(self):
        return "void"


class ResultCallback(ACallbackBase):
    def template_decl(self):
        appendix = ""
        if self.num_params:
            appendix += ", " + make_enum('typename P%d', self.num_params)
        return "template <typename RetType%s>" % appendix

    def ret_type(self):
        return "RetType"


class CallbackKind:
    """Currently there are three types of callbacks supported"""
    ConstMember, Member, Function = range(3)


class ACallback:
    """Base class for generating different callback categories"""
    __metaclass__ = ABCMeta

    def __init__(self, num_pb_args, num_ct_args):
        self.num_pb_args = num_pb_args
        self.num_ct_args = num_ct_args

    def name(self):
        name = self.__class__.__name__
        if self.num_pb_args >= 0: name += "_%d" % self.num_pb_args
        if self.num_ct_args >= 0: name += "_%d" % self.num_ct_args
        return name

    def template_decl(self, from_result_cb):
        p = ["bool del"]
        if from_result_cb: p.append("typename RetType")
        if self.kind() is not CallbackKind.Function: p.append("typename Class")
        if self.num_pb_args:
            p.append(make_enum("typename P%d", self.num_pb_args))
        if self.num_ct_args:
            p.append(make_enum("typename A%d", self.num_ct_args))
        if from_result_cb and not self.kind() is CallbackKind.Function:
            p.append("typename OnlyIf = " + self.compound_type())
        return ", ".join(p)

    def parent_class(self, from_result_cb):
        cb = "ResultCallback" if from_result_cb else "Callback"
        if self.num_ct_args: cb += str(self.num_ct_args)
        templ_args = []
        if from_result_cb: templ_args.append("RetType")
        if self.num_ct_args:
            templ_args.append(make_enum("A%d", self.num_ct_args))
        if templ_args:
            return "public %s<%s>" % (cb, ", ".join(templ_args))
        return "public %s" % cb

    def class_templ_spec(self, from_result_cb):
        if from_result_cb: return ""
        p = ["del", "void"]
        if not self.kind() is CallbackKind.Function:
            p.append("Class")
        if self.num_pb_args: p.append(make_enum("P%d", self.num_pb_args))
        if self.num_ct_args: p.append(make_enum("A%d", self.num_ct_args))
        if not self.kind() is CallbackKind.Function:
            p.append(self.compound_type())
        return "<%s>" % ", ".join(p)

    def class_members(self):
        instance = "Class* instance_;"
        if self.kind() is CallbackKind.ConstMember:
            instance = "const " + instance
        instance += "\nMethod method_;"
        if self.kind() is CallbackKind.Function:
            instance = "Function function_;"
        members = []
        if self.num_pb_args:
            instance += make_enum_pair(
                "\ntypename ::std::remove_reference<P%d>::type p%d_;",
                self.num_pb_args, "")
        return instance

    def run_method(self, from_result_cb):
        ret_type = "RetType" if from_result_cb else "void"
        ret_call = "RetType result =" if from_result_cb else ""
        ret = "return" if from_result_cb else ""
        ret_result = "return result;" if from_result_cb else ""
        run_args = ""
        if self.num_ct_args:
            run_args = make_enum_pair("A%d a%d", self.num_ct_args)
        run_params = ""
        if self.num_pb_args: run_params += make_enum("p%d_", self.num_pb_args)
        if self.num_ct_args:
            if self.num_pb_args: run_params += ", "
            run_params += make_enum("a%d", self.num_ct_args)
        instance = "method_"
        if self.kind() is CallbackKind.Function: instance = "function_"
        run_call = ""
        if self.kind() is CallbackKind.Function:
            run_call = "(*%s)(%s)" % (instance, run_params)
        else:
            run_call = "(instance_->*%s)(%s)" % (instance, run_params)
        run_def = """%s run(%s) override {
            if (!del) {
                %s %s;
            } else {
                %s %s;
                %s = nullptr;
                delete this;
                %s
            }
        }
        """ % (ret_type, run_args, ret, run_call, ret_call, run_call, instance,
               ret_result)
        return run_def

    def generate(self, from_result_cb):
        """Generate callback type (ConstMember*, Member*, Function*)"""
        cb_def = """template <%s> class %s%s : %s {
            public:
              typedef %s base;
              typedef %s;
              inline %s {}
              bool isRepeatable() const override { return !del; }
              %s
            private:
              %s
        };
        """

        return cb_def % (
            self.template_decl(from_result_cb), self.name(),
            self.class_templ_spec(from_result_cb),
            self.parent_class(from_result_cb),
            self.parent_class(from_result_cb).replace("public", ""),
            self.method_signature(from_result_cb), self.ctor(),
            self.run_method(from_result_cb), self.class_members())

    def api(self, deletable):
        delete = "false"
        cb_fn = "MakePermanentCallback"
        caller = "RetType (*function)"
        cb_args = ["instance", "method"]
        if self.kind() is CallbackKind.Function:
            cb_args = ["function"]
        pb_args = ""
        if self.num_pb_args:
            pb_args = ", " + make_enum_pair(
                "typename internal::ConstRef<P%d>::type p%d", self.num_pb_args)
            cb_args.append(make_enum("p%d", self.num_pb_args))

        cb_args = ", ".join(cb_args)
        cb_params = []
        if self.num_pb_args:
            cb_params.append(make_enum("P%d", self.num_pb_args))
        if self.num_ct_args:
            cb_params.append(make_enum("A%d", self.num_ct_args))
        cb_params = ", ".join(cb_params)
        cb_sig = ""
        if self.kind() is CallbackKind.ConstMember:
            cb_sig = "const Caller* instance, RetType (Callee::*method)(%s) const" % cb_params
        elif self.kind() is CallbackKind.Member:
            cb_sig = "Caller* instance, RetType (Callee::*method)(%s)" % cb_params
        elif self.kind() is CallbackKind.Function:
            cb_sig = "RetType (*function)(%s)" % cb_params
        if deletable:
            delete = "true"
            cb_fn = "MakeCallback"
        temp_decl, templ_spec = [], [delete, "RetType"]
        if not self.kind() is CallbackKind.Function:
            temp_decl.append("typename Caller, typename Callee")
            templ_spec.append("Caller")
            caller = "Caller* instance, RetType (Callee::*method)"
        if self.kind() is CallbackKind.ConstMember:
            caller = "const " + caller
        temp_decl.append("typename RetType")
        if self.num_pb_args:
            temp_decl.append(make_enum("typename P%d", self.num_pb_args))
            templ_spec.append(make_enum("P%d", self.num_pb_args))
        if self.num_ct_args:
            temp_decl.append(make_enum("typename A%d", self.num_ct_args))
            templ_spec.append(make_enum("A%d", self.num_ct_args))
        cb_call = """
        template <%s>
        inline typename %s<%s>::base* %s(%s %s) {
            return new %s<%s>(%s);
        }
        """ % (", ".join(temp_decl), self.name(), ", ".join(templ_spec), cb_fn,
               cb_sig, pb_args, self.name(), ", ".join(templ_spec), cb_args)
        return cb_call

    def serialize(self, out_handle):
        for t in [True, False]:
            out_handle.write(self.generate(t))
        for t in [True, False]:
            out_handle.write(self.api(t))

    def compound_type(self):
        return "typename ::std::enable_if<::std::is_compound<Class>::value>::type"

    @abstractmethod
    def kind(self):
        pass

    @abstractmethod
    def method_signature(self, from_result_cb):
        pass

    @abstractmethod
    def ctor(self):
        pass


class ConstMemberResultCallback(ACallback):
    def kind(self):
        return CallbackKind.ConstMember

    def method_signature(self, from_result_cb):
        ret_type = "RetType" if from_result_cb else "void"
        p = []
        if self.num_pb_args: p.append(make_enum("P%d", self.num_pb_args))
        if self.num_ct_args: p.append(make_enum("A%d", self.num_ct_args))
        return "%s (Class::*Method)(%s) const" % (ret_type, ", ".join(p))

    def ctor(self):
        p, m = [], []
        if self.num_pb_args:
            p.append(
                make_enum_pair("typename internal::ConstRef<P%d>::type p%d",
                               self.num_pb_args))
            m.append(make_enum_pair("p%d_(p%d)", self.num_pb_args))
            return """%s(const Class* instance, Method method, %s)
            : instance_(instance), method_(method), %s
            """ % (self.name(), ", ".join(p), ", ".join(m))
        return """%s(const Class* instance, Method method)
        : instance_(instance), method_(method)""" % self.name()


class MemberResultCallback(ACallback):
    def kind(self):
        return CallbackKind.Member

    def method_signature(self, from_result_cb):
        ret_type = "RetType" if from_result_cb else "void"
        p = []
        if self.num_pb_args: p.append(make_enum("P%d", self.num_pb_args))
        if self.num_ct_args: p.append(make_enum("A%d", self.num_ct_args))
        return "%s (Class::*Method)(%s)" % (ret_type, ", ".join(p))

    def ctor(self):
        p, m = [], []
        if self.num_pb_args:
            p.append(
                make_enum_pair("typename internal::ConstRef<P%d>::type p%d",
                               self.num_pb_args))
            m.append(make_enum_pair("p%d_(p%d)", self.num_pb_args))
            return """%s(Class* instance, Method method, %s)
            : instance_(instance), method_(method), %s
            """ % (self.name(), ", ".join(p), ", ".join(m))
        return """%s(Class* instance, Method method)
        : instance_(instance), method_(method)""" % self.name()


class FunctionResultCallback(ACallback):
    def kind(self):
        return CallbackKind.Function

    def method_signature(self, from_result_cb):
        ret_type = "RetType" if from_result_cb else "void"
        p = []
        if self.num_pb_args: p.append(make_enum("P%d", self.num_pb_args))
        if self.num_ct_args: p.append(make_enum("A%d", self.num_ct_args))
        return "%s (*Function)(%s)" % (ret_type, ", ".join(p))

    def ctor(self):
        p, m = [], []
        if self.num_pb_args:
            p.append(
                make_enum_pair("typename internal::ConstRef<P%d>::type p%d",
                               self.num_pb_args))
            m.append(make_enum_pair("p%d_(p%d)", self.num_pb_args))
            return """%s(Function function, %s)
            : function_(function), %s
            """ % (self.name(), ", ".join(p), ", ".join(m))
        return """%s(Function function) : function_(function)""" % self.name()


def make_enum(ele, till, delimiter=", "):
    """
    Create list of strings with consecutive numbering as follows:
    enumeration('param%d', 3) -> 'param1, param2, param3'
    """
    return delimiter.join([ele % (i + 1) for i in range(till)])


def make_enum_pair(ele, till, delimiter=", "):
    """
    Create list of pair of strings with consecutive numbering as follows:
    make_enumerated_pair('P%d p%d', 3) -> 'P1 p1, P2 p2, P3 p3'
    """
    return delimiter.join(ele % (i + 1, i + 1) for i in range(till))


def write_copyright_header(out_handle):
    out_handle.write(
        "// Copyright (c) %d, Kai Wolf. All rights reserved.\n"
        "// Use of this source code is governed by a personal license "
        "that can be\n// found in the LICENSE file in the top"
        "directory.\n\n" % date.today().year)


if __name__ == "__main__":
    parser = ArgumentParser(formatter_class=ArgumentDefaultsHelpFormatter)
    parser.add_argument("--num-callbacks",
                        type=int,
                        default=3,
                        help="Number of callback types to generate")
    parser.add_argument("--cb-types-filename",
                        default="callback_types.h",
                        help="Name of the cb_types header file")
    parser.add_argument("--cb-impl-filename",
                        default="callback_impl.h",
                        help="Name of the cb implementation header file")
    args = parser.parse_args()

    # write callback base classes
    with open(args.cb_types_filename, 'w') as f:
        write_copyright_header(f)
        f.write("#ifndef PARAMOUNT_CALLBACK_TYPES_H\n"
                "#define PARAMOUNT_CALLBACK_TYPES_H\n\n"
                "namespace pmt {\n\n")
        for idx in range(args.num_callbacks + 1):
            Callback(idx).serialize(f)
            ResultCallback(idx).serialize(f)
        f.write("}\n\n#endif")

    # write callback specializations for every pre-bound/call-time combination
    with open(args.cb_impl_filename, 'w') as f:
        write_copyright_header(f)
        f.write("#ifndef PARAMOUNT_CALLBACK_IMPL_H\n"
                "#define PARAMOUNT_CALLBACK_IMPL_H\n\n"
                "#include <type_traits>\n#include \"base/%s\"\n\n" %
                args.cb_types_filename)
        f.write(
            "namespace pmt {\nnamespace internal {\n\n"
            "template <typename T> struct ConstRef {\n"
            "typedef typename ::std::remove_reference<T>::type base_type;\n"
            "typedef const base_type& type;\n};}")
        for pb_args in range(args.num_callbacks + 1):
            for ct_args in range(args.num_callbacks + 1):
                ConstMemberResultCallback(pb_args, ct_args).serialize(f)
                MemberResultCallback(pb_args, ct_args).serialize(f)
                FunctionResultCallback(pb_args, ct_args).serialize(f)
        f.write("}\n\n#endif")
