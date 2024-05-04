#ifndef INCG_PHI_UNITTEST_TEST_TYPES_HPP
#define INCG_PHI_UNITTEST_TEST_TYPES_HPP

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/nodiscard.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/standard_library.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/assert.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/size_t.hpp>
#include <phi/forward/std/hash.hpp>
#include <phi/type_traits/false_t.hpp>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wused-but-marked-unused")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4624) // 'x': destructor was implicitly defined as deleted
PHI_MSVC_SUPPRESS_WARNING(
        5204) // 'x': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
PHI_MSVC_SUPPRESS_WARNING(
        4265) // 'x': class has virtual functions, but its non-trivial destructor is not virtual; instances of the class may not be destructed correctly

class class_type
{
public:
    ~class_type();
};

template <typename TypeT>
class template_type
{};

template <typename... TypesT>
class variadic_template
{};

template <typename TypeT>
struct public_derived_from : public TypeT
{};

template <typename TypeT>
struct private_derived_from : private TypeT
{};

template <typename TypeT>
struct protected_derived_from : protected TypeT
{};

template <typename TypeT>
struct virtual_derived_from : virtual TypeT
{};

class empty
{};

class not_empty
{
public:
    virtual ~not_empty();
};

struct non_trivial
{
    non_trivial();
    non_trivial(const non_trivial&);
    non_trivial& operator=(const non_trivial&);
    ~non_trivial();
};

union union_type
{};

union non_empty_union
{
    int      x;
    unsigned y;
};

union non_trivial_union
{
    int         i;
    non_trivial n;
};

struct bit_zero
{
    int : 0;
};

struct bit_one
{
    int : 1;
};

struct base
{};

struct derived : public base
{};

struct non_empty_base : public not_empty
{};

struct empty_base : public empty
{};

struct virtual_base : virtual empty
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class polymorphic
{
    virtual void rotate(int);
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class derived_polymorphic : public polymorphic
{};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class abstract
{
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    virtual ~abstract() = 0;
};

struct public_abstract
{
    virtual ~public_abstract() = default;

public:
    virtual void foo() = 0;
};

struct protected_abstract
{
    virtual ~protected_abstract() = default;

protected:
    virtual void foo() = 0;
};

struct private_abstract
{
    virtual ~private_abstract() = default;

private:
    virtual void foo() = 0;
};

template <typename>
struct abstract_template
{
    virtual ~abstract_template() = 0;

    virtual void test() = 0;
};

template <>
struct abstract_template<double>
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct public_abstract_deleted_destructor
{
    ~public_abstract_deleted_destructor() = delete;

public:
    virtual void foo() = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct protected_abstract_deleted_destructor
{
    ~protected_abstract_deleted_destructor() = delete;

protected:
    virtual void foo() = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct private_abstract_deleted_destructor
{
    ~private_abstract_deleted_destructor() = delete;

private:
    virtual void foo() = 0;
};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

class final_type final
{};

class final_derived final : public base
{};

struct public_destructor
{
public:
    ~public_destructor() = default;
};

struct protected_destructor
{
protected:
    ~protected_destructor() = default;
};

struct private_destructor
{
private:
    ~private_destructor() = default;
};

struct virtual_public_destructor
{
public:
    virtual ~virtual_public_destructor() = default;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct virtual_protected_destructor
{
protected:
    virtual ~virtual_protected_destructor() = default;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct virtual_private_destructor
{
private:
    virtual ~virtual_private_destructor() = default;
};

struct pure_public_destructor
{
public:
    virtual ~pure_public_destructor() = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct pure_protected_destructor
{
protected:
    virtual ~pure_protected_destructor() = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct pure_private_destructor
{
private:
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    virtual ~pure_private_destructor() = 0;
};

struct deleted_public_destructor
{
public:
    ~deleted_public_destructor() = delete;
};

struct deleted_protected_destructor
{
protected:
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    ~deleted_protected_destructor() = delete;
};

struct deleted_private_destructor
{
private:
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    ~deleted_private_destructor() = delete;
};

struct deleted_virtual_public_destructor
{
public:
    virtual ~deleted_virtual_public_destructor() = delete;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct deleted_virtual_protected_destructor
{
protected:
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    virtual ~deleted_virtual_protected_destructor() = delete;
};

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct deleted_virtual_private_destructor
{
private:
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    virtual ~deleted_virtual_private_destructor() = delete;
};

struct explicit_class
{
    explicit_class(double&);
    explicit explicit_class(int&);
    explicit_class(double&, int&, double&);
};

struct nothrow_explicit_class
{
    nothrow_explicit_class(double&) PHI_NOEXCEPT;
    explicit nothrow_explicit_class(int&) PHI_NOEXCEPT;
    nothrow_explicit_class(double&, int&, double&) PHI_NOEXCEPT;
};

struct throw_explicit_class
{
    throw_explicit_class(double&) PHI_NOEXCEPT_EXPR(false);
    explicit throw_explicit_class(int&) PHI_NOEXCEPT_EXPR(false);
    throw_explicit_class(double&, int&, double&) PHI_NOEXCEPT_EXPR(false);
};

struct throw_default_class
{
    throw_default_class() PHI_NOEXCEPT_EXPR(false);
};

struct throw_copy_constructible_class
{
    throw_copy_constructible_class(const throw_copy_constructible_class&) PHI_NOEXCEPT_EXPR(false);
};

struct throw_move_constructible_class
{
    throw_move_constructible_class(throw_move_constructible_class&&) PHI_NOEXCEPT_EXPR(false);
};

struct throw_destructor
{
    ~throw_destructor() PHI_NOEXCEPT_EXPR(false);
};

struct noexcept_explicit_class
{
    noexcept_explicit_class(double&) PHI_NOEXCEPT;
    explicit noexcept_explicit_class(int&) PHI_NOEXCEPT;
    noexcept_explicit_class(double&, int&, double&) PHI_NOEXCEPT;
};

struct except_explicit_class
{
    except_explicit_class(double&) PHI_NOEXCEPT_EXPR(false);
    explicit except_explicit_class(int&) PHI_NOEXCEPT_EXPR(false);
    except_explicit_class(double&, int&, double&) PHI_NOEXCEPT_EXPR(false);
};

struct noexcept_default_class
{
    noexcept_default_class() PHI_NOEXCEPT;
};

struct except_default_class
{
    except_default_class() PHI_NOEXCEPT_EXPR(false);
};

struct noexcept_copy_constructible_class
{
    noexcept_copy_constructible_class(const noexcept_copy_constructible_class&) PHI_NOEXCEPT;
};

struct except_copy_constructible_class
{
    except_copy_constructible_class(const except_copy_constructible_class&)
            PHI_NOEXCEPT_EXPR(false);
};

struct noexcept_move_constructible_class
{
    noexcept_move_constructible_class(noexcept_move_constructible_class&&) PHI_NOEXCEPT;
    noexcept_move_constructible_class& operator=(noexcept_move_constructible_class&&) = default;
};

struct except_move_constructible_class
{
    except_move_constructible_class(except_move_constructible_class&&) PHI_NOEXCEPT_EXPR(false);
};

struct noexcept_copy_assign_class
{
    noexcept_copy_assign_class& operator=(const noexcept_copy_assign_class&) PHI_NOEXCEPT;
};

struct except_copy_assign_class
{
    except_copy_assign_class& operator=(const except_copy_assign_class&) PHI_NOEXCEPT_EXPR(false);
};

struct noexcept_move_assign_class
{
    noexcept_move_assign_class(noexcept_move_assign_class&&) = default;
    noexcept_move_assign_class& operator=(noexcept_move_assign_class&&) PHI_NOEXCEPT;
};

struct except_move_assign_class
{
    except_move_assign_class& operator=(except_move_assign_class&&) PHI_NOEXCEPT_EXPR(false);
};

struct deleted_copy_assign_class
{
    deleted_copy_assign_class& operator=(const deleted_copy_assign_class&) = delete;
};

struct deleted_move_assign_class
{
    deleted_move_assign_class& operator=(deleted_move_assign_class&&) = delete;
};

struct noexcept_move_constructible_and_assignable_class
{
    noexcept_move_constructible_and_assignable_class(
            noexcept_move_constructible_and_assignable_class&&) PHI_NOEXCEPT;

    noexcept_move_constructible_and_assignable_class& operator=(
            noexcept_move_constructible_and_assignable_class&&) PHI_NOEXCEPT;
};

struct except_move_constructible_noexcept_move_assign_class
{
    except_move_constructible_noexcept_move_assign_class(
            except_move_constructible_noexcept_move_assign_class&&) PHI_NOEXCEPT_EXPR(false);

    except_move_constructible_noexcept_move_assign_class& operator=(
            except_move_constructible_noexcept_move_assign_class&&) PHI_NOEXCEPT;
};

struct noexcept_move_constructible_except_move_assign_class
{
    noexcept_move_constructible_except_move_assign_class(
            noexcept_move_constructible_except_move_assign_class&&) PHI_NOEXCEPT;

    noexcept_move_constructible_except_move_assign_class& operator=(
            noexcept_move_constructible_except_move_assign_class&&) PHI_NOEXCEPT_EXPR(false);
};

struct except_move_constructible_and_assign_class
{
    except_move_constructible_and_assign_class(except_move_constructible_and_assign_class&&)
            PHI_NOEXCEPT_EXPR(false);

    except_move_constructible_and_assign_class& operator=(
            except_move_constructible_and_assign_class&&) PHI_NOEXCEPT_EXPR(false);
};

template <typename ToT>
struct implicit_to
{
    operator ToT();
};

template <typename ToT>
struct deleted_implicit_to
{
    operator ToT() = delete;
};

template <typename ToT>
struct explicit_to
{
    explicit operator ToT();
};

template <typename ToT>
struct deleted_explicit_to
{
    explicit operator ToT() = delete;
};

struct ellipsis
{
    // NOLINTNEXTLINE(cert-dcl50-cpp,modernize-use-equals-default)
    ellipsis(...)
    {}
};

struct deleted_ellipsis
{
    // NOLINTNEXTLINE(cert-dcl50-cpp)
    deleted_ellipsis(...) = delete;
};

struct copy_constructible_only_type
{
    ~copy_constructible_only_type() = default;
    copy_constructible_only_type(int /*unused*/)
    {}
    copy_constructible_only_type(copy_constructible_only_type&&)                 = delete;
    copy_constructible_only_type(const copy_constructible_only_type&)            = default;
    copy_constructible_only_type& operator=(const copy_constructible_only_type&) = delete;
    copy_constructible_only_type& operator=(copy_constructible_only_type&&)      = delete;
};

struct move_constructible_only_type
{
    ~move_constructible_only_type() = default;
    move_constructible_only_type(int /*unused*/)
    {}
    move_constructible_only_type(const move_constructible_only_type&)            = delete;
    move_constructible_only_type(move_constructible_only_type&&)                 = default;
    move_constructible_only_type& operator=(const move_constructible_only_type&) = delete;
    move_constructible_only_type& operator=(move_constructible_only_type&&)      = delete;
};

struct overloaded_operators
{
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    PHI_NODISCARD int foo()
    {
        return 1;
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    PHI_NODISCARD int foo_c() const
    {
        return 2;
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    PHI_NODISCARD int foo_v() volatile
    {
        return 3;
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    PHI_NODISCARD int foo_cv() const volatile
    {
        return 4;
    }
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-private-field")

struct public_int_member
{
public:
    int m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,readability-identifier-naming)
};

struct protected_int_member
{
protected:
    int m_Member;
};

struct private_int_member
{
private:
    int m_Member;
};

struct public_static_int_member
{
public:
    static int m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

struct protected_static_int_member
{
protected:
    static int m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

struct private_static_int_member
{
private:
    static int m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

template <typename TypeT>
struct public_template_member
{
public:
    TypeT m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,readability-identifier-naming)
};

template <typename TypeT>
struct protected_template_member
{
protected:
    TypeT m_Member;
};

template <typename TypeT>
struct private_template_member
{
private:
    TypeT m_Member;
};

template <typename TypeT>
struct public_static_template_member
{
public:
    static TypeT m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

template <typename TypeT>
struct protected_static_template_member
{
protected:
    static TypeT m_Member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

template <typename TypeT>
struct private_static_template_member
{
private:
    static TypeT member; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT>
class cannot_instantiate
{
    enum
    {
        X = TypeT::ThisExpressionWillBlowUp
    };
};

struct natural_alignment
{
    long        t1;
    long long   t2;
    double      t3;
    long double t4;
};

enum Enum
{
    zero,
    one
};

enum EnumSigned : int
{
    two
};

enum EnumUnsigned : unsigned
{
    three
};

enum class EnumClass
{
    zero,
    one
};

enum struct EnumStruct
{
    zero,
    one
};

using function_type = void();

using function_ptr = void (*)();

using member_object_ptr = int class_type::*;

using member_function_ptr = void (class_type::*)();

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static auto Lambda = []() {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static auto LambdaNoexcept = []() PHI_NOEXCEPT {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static auto LambdaThrows = []() PHI_NOEXCEPT(false) {};

PHI_CLANG_SUPPRESS_WARNING_POP()

using lambda_type = decltype(Lambda);

using lambda_noexcept_type = decltype(LambdaNoexcept);

using lambda_throws_type = decltype(LambdaThrows);

struct incomplete_type;

template <typename TypeT>
struct incomplete_template;

template <typename... TypesT>
struct incomplete_variadic_template;

union incomplete_union;

enum IncompleteEnumSigned : int;

enum IncompleteEnumUnsigned : unsigned int;

enum class IncompleteEnumClass;

enum struct IncompleteEnumStruct;

struct non_default_constructible
{
    non_default_constructible()                                 = delete;
    ~non_default_constructible()                                = default;
    non_default_constructible(const non_default_constructible&) = default;
    non_default_constructible(non_default_constructible&&)      = default;

    non_default_constructible& operator=(const non_default_constructible&) = default;
    non_default_constructible& operator=(non_default_constructible&&)      = default;
};

struct non_copy_constructible
{
    non_copy_constructible()                              = default;
    ~non_copy_constructible()                             = default;
    non_copy_constructible(const non_copy_constructible&) = delete;
    non_copy_constructible(non_copy_constructible&&)      = default;

    non_copy_constructible& operator=(const non_copy_constructible&) = default;
    non_copy_constructible& operator=(non_copy_constructible&&)      = default;
};

struct non_move_constructible
{
    non_move_constructible()                              = default;
    ~non_move_constructible()                             = default;
    non_move_constructible(const non_move_constructible&) = default;
    non_move_constructible(non_move_constructible&&)      = delete;

    non_move_constructible& operator=(const non_move_constructible&) = default;
    non_move_constructible& operator=(non_move_constructible&&)      = default;
};

struct non_copy_assignable
{
    non_copy_assignable()                           = default;
    ~non_copy_assignable()                          = default;
    non_copy_assignable(const non_copy_assignable&) = default;
    non_copy_assignable(non_copy_assignable&&)      = default;

    non_copy_assignable& operator=(const non_copy_assignable&) = delete;
    non_copy_assignable& operator=(non_copy_assignable&&)      = default;
};

struct non_move_assignable
{
    non_move_assignable()                           = default;
    ~non_move_assignable()                          = default;
    non_move_assignable(const non_move_assignable&) = default;
    non_move_assignable(non_move_assignable&&)      = default;

    non_move_assignable& operator=(const non_move_assignable&) = default;
    non_move_assignable& operator=(non_move_assignable&&)      = delete;
};

struct non_assignable
{
    non_assignable()                      = default;
    ~non_assignable()                     = default;
    non_assignable(const non_assignable&) = default;
    non_assignable(non_assignable&&)      = default;

    non_assignable& operator=(const non_assignable&) = delete;
    non_assignable& operator=(non_assignable&&)      = delete;
};

struct non_copyable
{
    non_copyable()                    = default;
    ~non_copyable()                   = default;
    non_copyable(const non_copyable&) = delete;
    non_copyable(non_copyable&&)      = default;

    non_copyable& operator=(const non_copyable&) = delete;
    non_copyable& operator=(non_copyable&&)      = default;
};

struct non_moveable
{
    non_moveable()                    = default;
    ~non_moveable()                   = default;
    non_moveable(const non_moveable&) = default;
    non_moveable(non_moveable&&)      = delete;

    non_moveable& operator=(const non_moveable&) = default;
    non_moveable& operator=(non_moveable&&)      = delete;
};

struct non_constructible
{
    non_constructible()                         = delete;
    ~non_constructible()                        = default;
    non_constructible(const non_constructible&) = delete;
    non_constructible(non_constructible&&)      = delete;

    non_constructible& operator=(const non_constructible&) = delete;
    non_constructible& operator=(non_constructible&&)      = delete;
};

struct non_destructible
{
    non_destructible()                        = default;
    ~non_destructible()                       = delete;
    non_destructible(const non_destructible&) = default;
    non_destructible(non_destructible&&)      = default;

    non_destructible& operator=(const non_destructible&) = default;
    non_destructible& operator=(non_destructible&&)      = default;
};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wattributes")

class tracked
{
    enum class State
    {
        Constructed,
        MovedFrom,
        Destroyed
    };

public:
    PHI_CONSTEXPR tracked() PHI_NOEXCEPT : m_Value{0}, m_State{State::Constructed}
    {}

    PHI_CONSTEXPR explicit tracked(int val) PHI_NOEXCEPT : m_Value{val}, m_State{State::Constructed}
    {}

    PHI_EXTENDED_CONSTEXPR tracked(const tracked& other) PHI_NOEXCEPT : m_Value{other.m_Value},
                                                                        m_State{State::Constructed}
    {
        PHI_RELEASE_ASSERT(other.m_State != State::MovedFrom, "other object is already moved-from");
        PHI_RELEASE_ASSERT(other.m_State != State::Destroyed, "other object is already destroyed");
    }

    PHI_EXTENDED_CONSTEXPR tracked(tracked&& other) PHI_NOEXCEPT : m_Value{other.m_Value},
                                                                   m_State{State::Constructed}
    {
        PHI_RELEASE_ASSERT(other.m_State != State::MovedFrom, "other object is already moved-from");
        PHI_RELEASE_ASSERT(other.m_State != State::Destroyed, "other object is already destroyed");

        other.m_State = State::MovedFrom;
    }

    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    PHI_EXTENDED_CONSTEXPR_CLASS tracked& operator=(const tracked& other) PHI_NOEXCEPT
    {
        PHI_RELEASE_ASSERT(m_State != State::Destroyed, "this object is already destroyed");
        PHI_RELEASE_ASSERT(other.m_State != State::MovedFrom, "other object is already moved-from");
        PHI_RELEASE_ASSERT(other.m_State != State::Destroyed, "other object is already destroyed");

        m_Value = other.m_Value;
        return *this;
    }

    PHI_EXTENDED_CONSTEXPR_CLASS tracked& operator=(tracked&& other) PHI_NOEXCEPT
    {
        PHI_RELEASE_ASSERT(m_State != State::Destroyed, "this object is already destroyed");
        PHI_RELEASE_ASSERT(other.m_State != State::MovedFrom, "other object is already moved-from");
        PHI_RELEASE_ASSERT(other.m_State != State::Destroyed, "other object is already destroyed");

        m_Value       = other.m_Value;
        other.m_State = State::MovedFrom;

        return *this;
    }

    PHI_CONSTEXPR_DESTRUCTOR ~tracked() PHI_NOEXCEPT
    {
        PHI_RELEASE_ASSERT(m_State != State::Destroyed,
                           "~tracked() called on destroyed object - double destroy");

        m_State = State::Destroyed;
    }

    PHI_EXTENDED_CONSTEXPR_CLASS void set_value(int new_val) PHI_NOEXCEPT
    {
        PHI_RELEASE_ASSERT(m_State != State::Destroyed, "set_value() called on destroyed object");
        PHI_RELEASE_ASSERT(m_State != State::MovedFrom, "set_value() called on moved-from object");

        m_Value = new_val;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR_CLASS int value() const PHI_NOEXCEPT
    {
        PHI_RELEASE_ASSERT(m_State != State::Destroyed, "value() called on destroyed object");
        PHI_RELEASE_ASSERT(m_State != State::MovedFrom, "value() called on moved-from object");

        return m_Value;
    }

private:
    int   m_Value;
    State m_State;
};

PHI_GCC_SUPPRESS_WARNING_POP()

struct trap_constructible
{
    trap_constructible()                          = default;
    ~trap_constructible()                         = default;
    trap_constructible(const trap_constructible&) = default;
    trap_constructible(trap_constructible&&)      = default;

    trap_constructible& operator=(const trap_constructible&) = default;
    trap_constructible& operator=(trap_constructible&&)      = default;

    template <typename... ArgsT>
    PHI_CONSTEXPR trap_constructible(ArgsT&&... /*args*/) PHI_NOEXCEPT
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "trap_constructible constructor must not be used");
    }
};

struct trap_implicit_conversion
{
    template <typename TypeT>
    PHI_CONSTEXPR operator TypeT() PHI_NOEXCEPT
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_implicit_conversion::operator TypeT, must never be instantiated");

        return TypeT{};
    }
};

struct trap_comma
{
    template <typename TypeT>
    friend PHI_CONSTEXPR bool operator,(const trap_comma& /*unused*/,
                                        TypeT&& /*unused*/) PHI_NOEXCEPT
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_comma::operator, must never be instantiated");

        return false;
    }

    template <typename TypeT>
    friend PHI_CONSTEXPR bool operator,(TypeT&& /*unused*/,
                                        const trap_comma& /*unused*/) PHI_NOEXCEPT
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_comma::operator, must never be instantiated");

        return false;
    }
};

struct trap_call
{
    template <typename... ArgsT>
    PHI_CONSTEXPR bool operator()(ArgsT&&... /*unused*/) PHI_NOEXCEPT
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "trap_call::operator() must never be instantiated");

        return false;
    }
};

struct trap_self_assign
{
    trap_self_assign()                        = default;
    ~trap_self_assign()                       = default;
    trap_self_assign(const trap_self_assign&) = default;
    trap_self_assign(trap_self_assign&&)      = default;

    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    PHI_EXTENDED_CONSTEXPR trap_self_assign& operator=(const trap_self_assign& other) PHI_NOEXCEPT
    {
        PHI_UNUSED_PARAMETER(other);
        PHI_RELEASE_ASSERT(&other != this, "self-assignment is not allowed");

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR trap_self_assign& operator=(trap_self_assign&& other) PHI_NOEXCEPT
    {
        PHI_UNUSED_PARAMETER(other);
        PHI_RELEASE_ASSERT(&other != this, "self-assignment is not allowed");

        return *this;
    }
};

struct trap_deref
{
    template <typename TypeT>
    PHI_CONSTEXPR TypeT operator*() PHI_NOEXCEPT
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_deref::operator*() must never be instantiated");
        return TypeT{};
    }

    template <typename TypeT>
    PHI_CONSTEXPR TypeT* operator->() PHI_NOEXCEPT
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_deref::operator->() must never be instantiated");
        return TypeT{};
    }
};

struct trap_array_subscript
{
    template <typename TypeT>
    PHI_CONSTEXPR bool operator[](TypeT /*index*/) PHI_NOEXCEPT
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_array_subscript::operator[] must never be instantiated");
        return false;
    }
};

/// Helper struct to test ADL-hijacking in containers.
///
/// The class has some additional operations to be usable in all containers.
struct operator_hijacker
{
    bool operator<(const operator_hijacker& /*other*/) const
    {
        return true;
    }

    bool operator==(const operator_hijacker& /*other*/) const
    {
        return true;
    }

    template <typename TypeT>
    friend void operator&(TypeT&&) = delete;

    template <typename TypeT, typename OtherT>
    friend void operator,(TypeT&&, OtherT&&) = delete;

    template <typename TypeT, typename OtherT>
    friend void operator&&(TypeT&&, OtherT&&) = delete;

    template <typename TypeT, typename OtherT>
    friend void operator||(TypeT&&, OtherT&&) = delete;
};

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <>
struct hash<operator_hijacker>
{
    phi::size_t operator()(const operator_hijacker& /*op_hijacker*/) const
    {
        return 0;
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_UNITTEST_TEST_TYPES_HPP
