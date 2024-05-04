#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/invoke_result.hpp>
#include <phi/type_traits/is_invocable.hpp>
#include <phi/type_traits/is_invocable_r.hpp>
#include <phi/type_traits/is_same.hpp>
#include <functional>
#include <memory>
#include <type_traits>

// NOTE: gcc-6 does not have 'std::invoke_result'
#if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
#    define TEST_HAS_STD_INVOKE_RESULT() 1
#else
#    define TEST_HAS_STD_INVOKE_RESULT() 0
#endif

#if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0)
PHI_GCC_SUPPRESS_WARNING("-Wvolatile")
#endif

PHI_MSVC_SUPPRESS_WARNING(
        5215) // 'name' a function parameter with a volatile qualified type is deprecated in C++20

#if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wdeprecated-volatile")
#endif

struct S
{
    using FreeFunc = short (*)(long);

    operator FreeFunc() const;
    double                 operator()(char, int&);
    double const&          operator()(char, int&) const;
    double volatile&       operator()(char, int&) volatile;
    double const volatile& operator()(char, int&) const volatile;
};

struct SD : public S
{};

struct NotDerived
{};

struct wat
{
    wat& operator*()
    {
        return *this;
    }
    void foo();
};

struct F
{};

struct FD : public F
{};

template <typename TypeT>
struct Voider
{
    using type = void;
};

template <typename TypeT, typename = void>
struct HasType : public phi::false_type
{};

template <typename TypeT>
struct HasType<TypeT, typename Voider<typename TypeT::type>::type> : public phi::true_type
{};

template <typename TypeT, typename OtherT>
struct test_invoke_result;

template <typename FnT, typename... ArgsT, typename RetT>
struct test_invoke_result<FnT(ArgsT...), RetT>
{
    static void call()
    {
#if PHI_HAS_WORKING_IS_INVOCABLE()
        STATIC_REQUIRE(phi::is_invocable<FnT, ArgsT...>::value);
        STATIC_REQUIRE(phi::is_invocable_r<RetT, FnT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
        STATIC_REQUIRE(phi::is_invocable_v<FnT, ArgsT...>);
        STATIC_REQUIRE(phi::is_invocable_r_v<RetT, FnT, ArgsT...>);
#    endif

        CHECK_SAME_TYPE(RetT, typename phi::invoke_result<FnT, ArgsT...>::type);
        CHECK_SAME_TYPE(RetT, phi::invoke_result_t<FnT, ArgsT...>);

        // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && TEST_HAS_STD_INVOKE_RESULT()
        CHECK_SAME_TYPE(typename phi::invoke_result<FnT, ArgsT...>::type,
                        typename std::invoke_result<FnT, ArgsT...>::type);
        CHECK_SAME_TYPE(phi::invoke_result_t<FnT, ArgsT...>,
                        typename std::invoke_result<FnT, ArgsT...>::type);
#    endif
#endif
    }
};

template <typename TypeT, typename OtherT>
void test_result_of()
{
    test_invoke_result<TypeT, OtherT>::call();
}

template <typename TypeT>
struct test_invoke_no_result;

template <typename FnT, typename... ArgsT>
struct test_invoke_no_result<FnT(ArgsT...)>
{
    static void call()
    {
#if PHI_HAS_WORKING_IS_INVOCABLE()
        STATIC_REQUIRE_FALSE(phi::is_invocable<FnT, ArgsT...>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
        STATIC_REQUIRE_FALSE(phi::is_invocable_v<FnT, ArgsT...>);
#    endif

        STATIC_REQUIRE_FALSE(HasType<phi::invoke_result<FnT, ArgsT...>>::value);

        // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && TEST_HAS_STD_INVOKE_RESULT()
        STATIC_REQUIRE_FALSE(HasType<std::invoke_result<FnT, ArgsT...>>::value);
#    endif
#endif
    }
};

template <typename TypeT>
void test_no_result()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE_FALSE(HasType<phi::invoke_result<TypeT>>::value);
    test_invoke_no_result<TypeT>::call();

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && TEST_HAS_STD_INVOKE_RESULT()
    STATIC_REQUIRE_FALSE(HasType<std::invoke_result<TypeT>>::value);
#    endif
#endif
}

TEST_CASE("invoke_result")
{
    using ND = NotDerived;
    {
        // functor object
        test_result_of<S(int), short>();
        test_result_of<S&(unsigned char, int&), double>();
        test_result_of<S const&(unsigned char, int&), double const&>();
        test_result_of<S volatile&(unsigned char, int&), double volatile&>();
        test_result_of<S const volatile&(unsigned char, int&), double const volatile&>();
    }
    {
        // pointer to function
        using RF0  = bool (&)();
        using RF1  = bool* (&)(int);
        using RF2  = bool& (&)(int, int);
        using RF3  = const bool& (&)(int, int, int);
        using RF4  = bool (&)(int, ...);
        using PF0  = bool (*)();
        using PF1  = bool* (*)(int);
        using PF2  = bool& (*)(int, int);
        using PF3  = const bool& (*)(int, int, int);
        using PF4  = bool (*)(int, ...);
        using PRF0 = bool (*&)();
        using PRF1 = bool* (*&)(int);
        using PRF2 = bool& (*&)(int, int);
        using PRF3 = const bool& (*&)(int, int, int);
        using PRF4 = bool (*&)(int, ...);

        test_result_of<RF0(), bool>();
        test_result_of<RF1(int), bool*>();
        test_result_of<RF2(int, long), bool&>();
        test_result_of<RF3(int, long, int), bool const&>();
        test_result_of<RF4(int, float, void*), bool>();
        test_result_of<PF0(), bool>();
        test_result_of<PF1(int), bool*>();
        test_result_of<PF2(int, long), bool&>();
        test_result_of<PF3(int, long, int), bool const&>();
        test_result_of<PF4(int, float, void*), bool>();
        test_result_of<PRF0(), bool>();
        test_result_of<PRF1(int), bool*>();
        test_result_of<PRF2(int, long), bool&>();
        test_result_of<PRF3(int, long, int), bool const&>();
        test_result_of<PRF4(int, float, void*), bool>();
    }
    {
        // pointer to member function
        using PMS0 = int (S::*)();
        using PMS1 = int* (S::*)(long);
        using PMS2 = int& (S::*)(long, int);
        using PMS3 = const int& (S::*)(int, ...);

        test_result_of<PMS0(S), int>();
        test_result_of<PMS0(S&), int>();
        test_result_of<PMS0(S*), int>();
        test_result_of<PMS0(S*&), int>();
        test_result_of<PMS0(std::reference_wrapper<S>), int>();
        test_result_of<PMS0(const std::reference_wrapper<S>&), int>();
        test_result_of<PMS0(std::reference_wrapper<SD>), int>();
        test_result_of<PMS0(const std::reference_wrapper<SD>&), int>();
        test_result_of<PMS0(std::unique_ptr<S>), int>();
        test_result_of<PMS0(std::unique_ptr<SD>), int>();
        test_no_result<PMS0(const S&)>();
        test_no_result<PMS0(volatile S&)>();
        test_no_result<PMS0(const volatile S&)>();
        test_no_result<PMS0(ND&)>();
        test_no_result<PMS0(const ND&)>();
        test_no_result<PMS0(std::unique_ptr<S const>)>();
        test_no_result<PMS0(std::reference_wrapper<S const>)>();
        test_no_result<PMS0(std::reference_wrapper<ND>)>();
        test_no_result<PMS0(std::unique_ptr<ND>)>();

        test_result_of<PMS1(S, int), int*>();
        test_result_of<PMS1(S&, int), int*>();
        test_result_of<PMS1(S*, int), int*>();
        test_result_of<PMS1(S*&, int), int*>();
        test_result_of<PMS1(std::unique_ptr<S>, int), int*>();
        test_result_of<PMS1(std::unique_ptr<SD>, int), int*>();
        test_result_of<PMS1(std::reference_wrapper<S>, int), int*>();
        test_result_of<PMS1(const std::reference_wrapper<S>&, int), int*>();
        test_result_of<PMS1(std::reference_wrapper<SD>, int), int*>();
        test_result_of<PMS1(const std::reference_wrapper<SD>&, int), int*>();
        test_no_result<PMS1(const S&, int)>();
        test_no_result<PMS1(volatile S&, int)>();
        test_no_result<PMS1(const volatile S&, int)>();
        test_no_result<PMS1(ND&, int)>();
        test_no_result<PMS1(const ND&, int)>();
        test_no_result<PMS1(std::unique_ptr<S const>, int)>();
        test_no_result<PMS1(std::reference_wrapper<S const>, int)>();
        test_no_result<PMS1(std::reference_wrapper<ND>, int)>();
        test_no_result<PMS1(std::unique_ptr<ND>, int)>();

        test_result_of<PMS2(S, int, int), int&>();
        test_result_of<PMS2(S&, int, int), int&>();
        test_result_of<PMS2(S*, int, int), int&>();
        test_result_of<PMS2(S*&, int, int), int&>();
        test_result_of<PMS2(std::unique_ptr<S>, int, int), int&>();
        test_result_of<PMS2(std::unique_ptr<SD>, int, int), int&>();
        test_result_of<PMS2(std::reference_wrapper<S>, int, int), int&>();
        test_result_of<PMS2(const std::reference_wrapper<S>&, int, int), int&>();
        test_result_of<PMS2(std::reference_wrapper<SD>, int, int), int&>();
        test_result_of<PMS2(const std::reference_wrapper<SD>&, int, int), int&>();
        test_no_result<PMS2(const S&, int, int)>();
        test_no_result<PMS2(volatile S&, int, int)>();
        test_no_result<PMS2(const volatile S&, int, int)>();
        test_no_result<PMS2(std::unique_ptr<S const>, int, int)>();
        test_no_result<PMS2(std::reference_wrapper<S const>, int, int)>();
        test_no_result<PMS2(const ND&, int, int)>();
        test_no_result<PMS2(std::reference_wrapper<ND>, int, int)>();
        test_no_result<PMS2(std::unique_ptr<ND>, int, int)>();

        test_result_of<PMS3(S&, int), const int&>();
        test_result_of<PMS3(S&, int, long), const int&>();

        using PMS0C = int (S::*)() const;
        using PMS1C = int* (S::*)(long) const;
        using PMS2C = int& (S::*)(long, int) const;
        using PMS3C = const int& (S::*)(int, ...) const;
        test_result_of<PMS0C(S), int>();
        test_result_of<PMS0C(S&), int>();
        test_result_of<PMS0C(const S&), int>();
        test_result_of<PMS0C(S*), int>();
        test_result_of<PMS0C(const S*), int>();
        test_result_of<PMS0C(S*&), int>();
        test_result_of<PMS0C(const S*&), int>();
        test_result_of<PMS0C(std::unique_ptr<S>), int>();
        test_result_of<PMS0C(std::unique_ptr<SD>), int>();
        test_result_of<PMS0C(std::reference_wrapper<S>), int>();
        test_result_of<PMS0C(std::reference_wrapper<const S>), int>();
        test_result_of<PMS0C(const std::reference_wrapper<S>&), int>();
        test_result_of<PMS0C(const std::reference_wrapper<const S>&), int>();
        test_result_of<PMS0C(std::reference_wrapper<SD>), int>();
        test_result_of<PMS0C(std::reference_wrapper<const SD>), int>();
        test_result_of<PMS0C(const std::reference_wrapper<SD>&), int>();
        test_result_of<PMS0C(const std::reference_wrapper<const SD>&), int>();
        test_no_result<PMS0C(volatile S&)>();
        test_no_result<PMS0C(const volatile S&)>();

        test_result_of<PMS1C(S, int), int*>();
        test_result_of<PMS1C(S&, int), int*>();
        test_result_of<PMS1C(const S&, int), int*>();
        test_result_of<PMS1C(S*, int), int*>();
        test_result_of<PMS1C(const S*, int), int*>();
        test_result_of<PMS1C(S*&, int), int*>();
        test_result_of<PMS1C(const S*&, int), int*>();
        test_result_of<PMS1C(std::unique_ptr<S>, int), int*>();
        test_no_result<PMS1C(volatile S&, int)>();
        test_no_result<PMS1C(const volatile S&, int)>();

        test_result_of<PMS2C(S, int, int), int&>();
        test_result_of<PMS2C(S&, int, int), int&>();
        test_result_of<PMS2C(const S&, int, int), int&>();
        test_result_of<PMS2C(S*, int, int), int&>();
        test_result_of<PMS2C(const S*, int, int), int&>();
        test_result_of<PMS2C(S*&, int, int), int&>();
        test_result_of<PMS2C(const S*&, int, int), int&>();
        test_result_of<PMS2C(std::unique_ptr<S>, int, int), int&>();
        test_no_result<PMS2C(volatile S&, int, int)>();
        test_no_result<PMS2C(const volatile S&, int, int)>();

        test_result_of<PMS3C(S&, int), const int&>();
        test_result_of<PMS3C(S&, int, long), const int&>();

        using PMS0V = int (S::*)() volatile;
        using PMS1V = int* (S::*)(long) volatile;
        using PMS2V = int& (S::*)(long, int) volatile;
        using PMS3V = const int& (S::*)(int, ...) volatile;

        test_result_of<PMS0V(S), int>();
        test_result_of<PMS0V(S&), int>();
        test_result_of<PMS0V(volatile S&), int>();
        test_result_of<PMS0V(S*), int>();
        test_result_of<PMS0V(volatile S*), int>();
        test_result_of<PMS0V(S*&), int>();
        test_result_of<PMS0V(volatile S*&), int>();
        test_result_of<PMS0V(std::unique_ptr<S>), int>();
        test_no_result<PMS0V(const S&)>();
        test_no_result<PMS0V(const volatile S&)>();

        test_result_of<PMS1V(S, int), int*>();
        test_result_of<PMS1V(S&, int), int*>();
        test_result_of<PMS1V(volatile S&, int), int*>();
        test_result_of<PMS1V(S*, int), int*>();
        test_result_of<PMS1V(volatile S*, int), int*>();
        test_result_of<PMS1V(S*&, int), int*>();
        test_result_of<PMS1V(volatile S*&, int), int*>();
        test_result_of<PMS1V(std::unique_ptr<S>, int), int*>();
        test_no_result<PMS1V(const S&, int)>();
        test_no_result<PMS1V(const volatile S&, int)>();

        test_result_of<PMS2V(S, int, int), int&>();
        test_result_of<PMS2V(S&, int, int), int&>();
        test_result_of<PMS2V(volatile S&, int, int), int&>();
        test_result_of<PMS2V(S*, int, int), int&>();
        test_result_of<PMS2V(volatile S*, int, int), int&>();
        test_result_of<PMS2V(S*&, int, int), int&>();
        test_result_of<PMS2V(volatile S*&, int, int), int&>();
        test_result_of<PMS2V(std::unique_ptr<S>, int, int), int&>();
        test_no_result<PMS2V(const S&, int, int)>();
        test_no_result<PMS2V(const volatile S&, int, int)>();

        test_result_of<PMS3V(S&, int), const int&>();
        test_result_of<PMS3V(S&, int, long), const int&>();

        using PMS0CV = int (S::*)() const volatile;
        using PMS1CV = int* (S::*)(long) const volatile;
        using PMS2CV = int& (S::*)(long, int) const volatile;
        using PMS3CV = const int& (S::*)(int, ...) const volatile;
        test_result_of<PMS0CV(S), int>();
        test_result_of<PMS0CV(S&), int>();
        test_result_of<PMS0CV(const S&), int>();
        test_result_of<PMS0CV(volatile S&), int>();
        test_result_of<PMS0CV(const volatile S&), int>();
        test_result_of<PMS0CV(S*), int>();
        test_result_of<PMS0CV(const S*), int>();
        test_result_of<PMS0CV(volatile S*), int>();
        test_result_of<PMS0CV(const volatile S*), int>();
        test_result_of<PMS0CV(S*&), int>();
        test_result_of<PMS0CV(const S*&), int>();
        test_result_of<PMS0CV(volatile S*&), int>();
        test_result_of<PMS0CV(const volatile S*&), int>();
        test_result_of<PMS0CV(std::unique_ptr<S>), int>();

        test_result_of<PMS1CV(S, int), int*>();
        test_result_of<PMS1CV(S&, int), int*>();
        test_result_of<PMS1CV(const S&, int), int*>();
        test_result_of<PMS1CV(volatile S&, int), int*>();
        test_result_of<PMS1CV(const volatile S&, int), int*>();
        test_result_of<PMS1CV(S*, int), int*>();
        test_result_of<PMS1CV(const S*, int), int*>();
        test_result_of<PMS1CV(volatile S*, int), int*>();
        test_result_of<PMS1CV(const volatile S*, int), int*>();
        test_result_of<PMS1CV(S*&, int), int*>();
        test_result_of<PMS1CV(const S*&, int), int*>();
        test_result_of<PMS1CV(volatile S*&, int), int*>();
        test_result_of<PMS1CV(const volatile S*&, int), int*>();
        test_result_of<PMS1CV(std::unique_ptr<S>, int), int*>();

        test_result_of<PMS2CV(S, int, int), int&>();
        test_result_of<PMS2CV(S&, int, int), int&>();
        test_result_of<PMS2CV(const S&, int, int), int&>();
        test_result_of<PMS2CV(volatile S&, int, int), int&>();
        test_result_of<PMS2CV(const volatile S&, int, int), int&>();
        test_result_of<PMS2CV(S*, int, int), int&>();
        test_result_of<PMS2CV(const S*, int, int), int&>();
        test_result_of<PMS2CV(volatile S*, int, int), int&>();
        test_result_of<PMS2CV(const volatile S*, int, int), int&>();
        test_result_of<PMS2CV(S*&, int, int), int&>();
        test_result_of<PMS2CV(const S*&, int, int), int&>();
        test_result_of<PMS2CV(volatile S*&, int, int), int&>();
        test_result_of<PMS2CV(const volatile S*&, int, int), int&>();
        test_result_of<PMS2CV(std::unique_ptr<S>, int, int), int&>();

        test_result_of<PMS3CV(S&, int), const int&>();
        test_result_of<PMS3CV(S&, int, long), const int&>();
    }
    {
        // pointer to member data
        using PMD = char S::*;

        test_result_of<PMD(S&), char&>();
        test_result_of<PMD(S*), char&>();
        test_result_of<PMD(S* const), char&>();
        test_result_of<PMD(const S&), const char&>();
        test_result_of<PMD(const S*), const char&>();
        test_result_of<PMD(volatile S&), volatile char&>();
        test_result_of<PMD(volatile S*), volatile char&>();
        test_result_of<PMD(const volatile S&), const volatile char&>();
        test_result_of<PMD(const volatile S*), const volatile char&>();
        test_result_of<PMD(SD&), char&>();
        test_result_of<PMD(SD const&), const char&>();
        test_result_of<PMD(SD*), char&>();
        test_result_of<PMD(const SD*), const char&>();
        test_result_of<PMD(std::unique_ptr<S>), char&>();
        test_result_of<PMD(std::unique_ptr<S const>), const char&>();
        test_result_of<PMD(std::reference_wrapper<S>), char&>();
        test_result_of<PMD(std::reference_wrapper<S const>), const char&>();
        test_no_result<PMD(ND&)>();
    }
    {
        using PMD = char F::*;

        test_invoke_result<PMD(F&), char&>();
        test_invoke_result<PMD(F const&), char const&>();
        test_invoke_result<PMD(F volatile&), char volatile&>();
        test_invoke_result<PMD(F const volatile&), char const volatile&>();

        test_invoke_result<PMD(F&&), char&&>();
        test_invoke_result<PMD(F const&&), char const&&>();
        test_invoke_result<PMD(F volatile&&), char volatile&&>();
        test_invoke_result<PMD(F const volatile&&), char const volatile&&>();

        test_invoke_result<PMD(F), char&&>();
        test_invoke_result<PMD(F const), char&&>();
        test_invoke_result<PMD(F volatile), char&&>();
        test_invoke_result<PMD(F const volatile), char&&>();

        test_invoke_result<PMD(FD&), char&>();
        test_invoke_result<PMD(FD const&), char const&>();
        test_invoke_result<PMD(FD volatile&), char volatile&>();
        test_invoke_result<PMD(FD const volatile&), char const volatile&>();

        test_invoke_result<PMD(FD&&), char&&>();
        test_invoke_result<PMD(FD const&&), char const&&>();
        test_invoke_result<PMD(FD volatile&&), char volatile&&>();
        test_invoke_result<PMD(FD const volatile&&), char const volatile&&>();

        test_invoke_result<PMD(FD), char&&>();
        test_invoke_result<PMD(FD const), char&&>();
        test_invoke_result<PMD(FD volatile), char&&>();
        test_invoke_result<PMD(FD const volatile), char&&>();

        test_invoke_result<PMD(std::unique_ptr<F>), char&>();
        test_invoke_result<PMD(std::unique_ptr<F const>), const char&>();
        test_invoke_result<PMD(std::unique_ptr<FD>), char&>();
        test_invoke_result<PMD(std::unique_ptr<FD const>), const char&>();

        test_invoke_result<PMD(std::reference_wrapper<F>), char&>();
        test_invoke_result<PMD(std::reference_wrapper<F const>), const char&>();
        test_invoke_result<PMD(std::reference_wrapper<FD>), char&>();
        test_invoke_result<PMD(std::reference_wrapper<FD const>), const char&>();
    }
    {
        test_invoke_result<int (F::*(F&))()&, int>();
        test_invoke_result<int (F::*(F&))() const&, int>();
        test_invoke_result<int (F::*(F&))() volatile&, int>();
        test_invoke_result<int (F::*(F&))() const volatile&, int>();
        test_invoke_result<int (F::*(F const&))() const&, int>();
        test_invoke_result<int (F::*(F const&))() const volatile&, int>();
        test_invoke_result<int (F::*(F volatile&))() volatile&, int>();
        test_invoke_result<int (F::*(F volatile&))() const volatile&, int>();
        test_invoke_result<int (F::*(F const volatile&))() const volatile&, int>();

        test_invoke_result<int (F::*(F&&))()&&, int>();
        test_invoke_result<int (F::*(F&&))() const&&, int>();
        test_invoke_result<int (F::*(F&&))() volatile&&, int>();
        test_invoke_result<int (F::*(F&&))() const volatile&&, int>();
        test_invoke_result<int (F::*(F const&&))() const&&, int>();
        test_invoke_result<int (F::*(F const&&))() const volatile&&, int>();
        test_invoke_result<int (F::*(F volatile&&))() volatile&&, int>();
        test_invoke_result<int (F::*(F volatile&&))() const volatile&&, int>();
        test_invoke_result<int (F::*(F const volatile&&))() const volatile&&, int>();

        test_invoke_result<int (F::*(F))()&&, int>();
        test_invoke_result<int (F::*(F))() const&&, int>();
        test_invoke_result<int (F::*(F))() volatile&&, int>();
        test_invoke_result<int (F::*(F))() const volatile&&, int>();
        test_invoke_result<int (F::*(F const))() const&&, int>();
        test_invoke_result<int (F::*(F const))() const volatile&&, int>();
        test_invoke_result<int (F::*(F volatile))() volatile&&, int>();
        test_invoke_result<int (F::*(F volatile))() const volatile&&, int>();
        test_invoke_result<int (F::*(F const volatile))() const volatile&&, int>();
    }
    {
        test_invoke_result<int (F::*(FD&))()&, int>();
        test_invoke_result<int (F::*(FD&))() const&, int>();
        test_invoke_result<int (F::*(FD&))() volatile&, int>();
        test_invoke_result<int (F::*(FD&))() const volatile&, int>();
        test_invoke_result<int (F::*(FD const&))() const&, int>();
        test_invoke_result<int (F::*(FD const&))() const volatile&, int>();
        test_invoke_result<int (F::*(FD volatile&))() volatile&, int>();
        test_invoke_result<int (F::*(FD volatile&))() const volatile&, int>();
        test_invoke_result<int (F::*(FD const volatile&))() const volatile&, int>();

        test_invoke_result<int (F::*(FD&&))()&&, int>();
        test_invoke_result<int (F::*(FD&&))() const&&, int>();
        test_invoke_result<int (F::*(FD&&))() volatile&&, int>();
        test_invoke_result<int (F::*(FD&&))() const volatile&&, int>();
        test_invoke_result<int (F::*(FD const&&))() const&&, int>();
        test_invoke_result<int (F::*(FD const&&))() const volatile&&, int>();
        test_invoke_result<int (F::*(FD volatile&&))() volatile&&, int>();
        test_invoke_result<int (F::*(FD volatile&&))() const volatile&&, int>();
        test_invoke_result<int (F::*(FD const volatile&&))() const volatile&&, int>();

        test_invoke_result<int (F::*(FD))()&&, int>();
        test_invoke_result<int (F::*(FD))() const&&, int>();
        test_invoke_result<int (F::*(FD))() volatile&&, int>();
        test_invoke_result<int (F::*(FD))() const volatile&&, int>();
        test_invoke_result<int (F::*(FD const))() const&&, int>();
        test_invoke_result<int (F::*(FD const))() const volatile&&, int>();
        test_invoke_result<int (F::*(FD volatile))() volatile&&, int>();
        test_invoke_result<int (F::*(FD volatile))() const volatile&&, int>();
        test_invoke_result<int (F::*(FD const volatile))() const volatile&&, int>();
    }
    {
        test_invoke_result<int (F::*(std::reference_wrapper<F>))(), int>();
        test_invoke_result<int (F::*(std::reference_wrapper<const F>))() const, int>();
        test_invoke_result<int (F::*(std::unique_ptr<F>))(), int>();
        test_invoke_result<int (F::*(std::unique_ptr<const F>))() const, int>();
        test_invoke_result<int (F::*(phi::scope_ptr<F>))(), int>();
        test_invoke_result<int (F::*(phi::scope_ptr<const F>))() const, int>();
    }
    {
        test_invoke_result<decltype (&wat::foo)(wat), void>();
    }
}
