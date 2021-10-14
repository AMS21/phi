#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/add_pointer.hpp>
#include <vector>

template <typename T, typename U = T*>
void test_add_pointer()
{
    CHECK_SAME_TYPE(typename phi::add_pointer<T>::type, U);
    CHECK_SAME_TYPE(const typename phi::add_pointer<T>::type, const U);
    CHECK_SAME_TYPE(volatile typename phi::add_pointer<T>::type, volatile U);
    CHECK_SAME_TYPE(const volatile typename phi::add_pointer<T>::type, const volatile U);

    CHECK_SAME_TYPE(phi::add_pointer_t<T>, U);
    CHECK_SAME_TYPE(const phi::add_pointer_t<T>, const U);
    CHECK_SAME_TYPE(volatile phi::add_pointer_t<T>, volatile U);
    CHECK_SAME_TYPE(const volatile phi::add_pointer_t<T>, const volatile U);
}

template <typename F>
void test_function0()
{
    CHECK_SAME_TYPE(F*, typename phi::add_pointer<F>::type);
    CHECK_SAME_TYPE(F*, phi::add_pointer_t<F>);
}

template <typename F>
void test_function1()
{
    CHECK_SAME_TYPE(F, typename phi::add_pointer<F>::type);
    CHECK_SAME_TYPE(F, phi::add_pointer_t<F>);
}

struct Foo
{};

TEST_CASE("add_pointer")
{
    test_add_pointer<Foo, Foo*>();

    test_add_pointer<void, void*>();
    test_add_pointer<phi::nullptr_t, phi::nullptr_t*>();
    test_add_pointer<bool, bool*>();
    test_add_pointer<char, char*>();
    test_add_pointer<signed char, signed char*>();
    test_add_pointer<unsigned char, unsigned char*>();
    test_add_pointer<short, short*>();
    test_add_pointer<unsigned short, unsigned short*>();
    test_add_pointer<int, int*>();
    test_add_pointer<unsigned int, unsigned int*>();
    test_add_pointer<long, long*>();
    test_add_pointer<unsigned long, unsigned long*>();
    test_add_pointer<long long, long long*>();
    test_add_pointer<unsigned long long, unsigned long long*>();
    test_add_pointer<float, float*>();
    test_add_pointer<double, double*>();
    test_add_pointer<long double, long double*>();
    test_add_pointer<char8_t, char8_t*>();
    test_add_pointer<char16_t, char16_t*>();
    test_add_pointer<char32_t, char32_t*>();
    test_add_pointer<wchar_t, wchar_t*>();

    test_add_pointer<phi::Boolean, phi::Boolean*>();
    test_add_pointer<phi::Integer<signed char>, phi::Integer<signed char>*>();
    test_add_pointer<phi::Integer<unsigned char>, phi::Integer<unsigned char>*>();
    test_add_pointer<phi::Integer<short>, phi::Integer<short>*>();
    test_add_pointer<phi::Integer<unsigned short>, phi::Integer<unsigned short>*>();
    test_add_pointer<phi::Integer<int>, phi::Integer<int>*>();
    test_add_pointer<phi::Integer<unsigned int>, phi::Integer<unsigned int>*>();
    test_add_pointer<phi::Integer<long>, phi::Integer<long>*>();
    test_add_pointer<phi::Integer<unsigned long>, phi::Integer<unsigned long>*>();
    test_add_pointer<phi::Integer<long long>, phi::Integer<long long>*>();
    test_add_pointer<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>*>();
    test_add_pointer<phi::FloatingPoint<float>, phi::FloatingPoint<float>*>();
    test_add_pointer<phi::FloatingPoint<double>, phi::FloatingPoint<double>*>();
    test_add_pointer<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>*>();

    test_add_pointer<std::vector<int>, std::vector<int>*>();
    test_add_pointer<phi::ScopePtr<int>, phi::ScopePtr<int>*>();

    test_add_pointer<int&, int*>();
    test_add_pointer<const int&, const int*>();
    test_add_pointer<volatile int&, volatile int*>();
    test_add_pointer<const volatile int&, const volatile int*>();
    test_add_pointer<int&&, int*>();
    test_add_pointer<const int&&, const int*>();
    test_add_pointer<volatile int&&, volatile int*>();
    test_add_pointer<const volatile int&&, const volatile int*>();
    test_add_pointer<int*, int**>();
    test_add_pointer<const int*, const int**>();
    test_add_pointer<volatile int*, volatile int**>();
    test_add_pointer<const volatile int*, const volatile int**>();
    test_add_pointer<int**, int***>();
    test_add_pointer<const int**>();
    test_add_pointer<volatile int**>();
    test_add_pointer<const volatile int**>();
    test_add_pointer<int*&, int**>();
    test_add_pointer<const int*&, const int**>();
    test_add_pointer<volatile int*&, volatile int**>();
    test_add_pointer<const volatile int*&, const volatile int**>();
    test_add_pointer<int*&&, int**>();
    test_add_pointer<const int*&&, const int**>();
    test_add_pointer<volatile int*&&, volatile int**>();
    test_add_pointer<const volatile int*&&, const volatile int**>();
    test_add_pointer<void*>();
    test_add_pointer<char[3]>();
    test_add_pointer<char[]>();
    test_add_pointer<char* [3]>();
    test_add_pointer<char*[]>();
    test_add_pointer<int(*)[3]>();
    test_add_pointer<int(*)[]>();
    test_add_pointer<int(&)[3], int(*)[3]>();
    test_add_pointer<int(&)[], int(*)[]>();
    test_add_pointer<int(&&)[3], int(*)[3]>();
    test_add_pointer<int(&&)[], int(*)[]>();
    test_add_pointer<char[3][2]>();
    test_add_pointer<char[][2]>();
    test_add_pointer<char* [3][2]>();
    test_add_pointer<char*[][2]>();
    test_add_pointer<int(*)[3][2]>();
    test_add_pointer<int(*)[][2]>();
    test_add_pointer<int(&)[3][2], int(*)[3][2]>();
    test_add_pointer<int(&)[][2], int(*)[][2]>();
    test_add_pointer<int(&&)[3][2], int(*)[3][2]>();
    test_add_pointer<int(&&)[][2], int(*)[][2]>();
    test_add_pointer<Class>();
    test_add_pointer<Class[]>();
    test_add_pointer<Class[2]>();
    test_add_pointer<Struct>();
    test_add_pointer<TemplateClass<void>>();
    test_add_pointer<TemplateClass<int>>();
    test_add_pointer<TemplateClass<Class>>();
    test_add_pointer<TemplateClass<incomplete_type>>();
    test_add_pointer<TemplateStruct<void>>();
    test_add_pointer<TemplateStruct<int>>();
    test_add_pointer<TemplateStruct<Class>>();
    test_add_pointer<TemplateStruct<incomplete_type>>();
    test_add_pointer<VariadicTemplateClass<>>();
    test_add_pointer<VariadicTemplateClass<void>>();
    test_add_pointer<VariadicTemplateClass<int>>();
    test_add_pointer<VariadicTemplateClass<Class>>();
    test_add_pointer<VariadicTemplateClass<incomplete_type>>();
    test_add_pointer<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_add_pointer<VariadicTemplateStruct<>>();
    test_add_pointer<VariadicTemplateStruct<void>>();
    test_add_pointer<VariadicTemplateStruct<int>>();
    test_add_pointer<VariadicTemplateStruct<Class>>();
    test_add_pointer<VariadicTemplateStruct<incomplete_type>>();
    test_add_pointer<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_add_pointer<PublicDerviedFromTemplate<Base>>();
    test_add_pointer<PublicDerviedFromTemplate<Derived>>();
    test_add_pointer<PublicDerviedFromTemplate<Class>>();
    test_add_pointer<PrivateDerviedFromTemplate<Base>>();
    test_add_pointer<PrivateDerviedFromTemplate<Derived>>();
    test_add_pointer<PrivateDerviedFromTemplate<Class>>();
    test_add_pointer<ProtectedDerviedFromTemplate<Base>>();
    test_add_pointer<ProtectedDerviedFromTemplate<Derived>>();
    test_add_pointer<ProtectedDerviedFromTemplate<Class>>();
    test_add_pointer<Union>();
    test_add_pointer<NonEmptyUnion>();
    test_add_pointer<Empty>();
    test_add_pointer<NotEmpty>();
    test_add_pointer<bit_zero>();
    test_add_pointer<bit_one>();
    test_add_pointer<Base>();
    test_add_pointer<Derived>();
    test_add_pointer<Abstract>();
    test_add_pointer<AbstractTemplate<int>>();
    test_add_pointer<AbstractTemplate<double>>();
    test_add_pointer<AbstractTemplate<Class>>();
    test_add_pointer<AbstractTemplate<incomplete_type>>();
    test_add_pointer<Final>();
    test_add_pointer<Enum>();
    test_add_pointer<EnumSigned>();
    test_add_pointer<EnumUnsigned>();
    test_add_pointer<EnumClass>();
    test_add_pointer<EnumStruct>();
    test_add_pointer<Function>();
    test_add_pointer<FunctionPtr>();
    test_add_pointer<MemberObjectPtr>();
    test_add_pointer<MemberFunctionPtr>();
    test_add_pointer<incomplete_type>();
    test_add_pointer<IncompleteTemplate<void>>();
    test_add_pointer<IncompleteTemplate<int>>();
    test_add_pointer<IncompleteTemplate<Class>>();
    test_add_pointer<IncompleteTemplate<incomplete_type>>();
    test_add_pointer<IncompleteVariadicTemplate<>>();
    test_add_pointer<IncompleteVariadicTemplate<void>>();
    test_add_pointer<IncompleteVariadicTemplate<int>>();
    test_add_pointer<IncompleteVariadicTemplate<Class>>();
    test_add_pointer<IncompleteVariadicTemplate<incomplete_type>>();
    test_add_pointer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_pointer<int Class::*>();
    test_add_pointer<float Class::*>();
    test_add_pointer<void * Class::*>();
    test_add_pointer<int * Class::*>();
    test_add_pointer<int Class::*&, int Class::**>();
    test_add_pointer<float Class::*&, float Class::**>();
    test_add_pointer<void * Class::*&, void * Class::**>();
    test_add_pointer<int * Class::*&, int * Class::**>();
    test_add_pointer<int Class::*&&, int Class::**>();
    test_add_pointer<float Class::*&&, float Class::**>();
    test_add_pointer<void * Class::*&&, void * Class::**>();
    test_add_pointer<int * Class::*&&, int * Class::**>();
    test_add_pointer<int Class::*const>();
    test_add_pointer<float Class::*const>();
    test_add_pointer<void * Class::*const>();
    test_add_pointer<int Class::*const&, int Class::*const*>();
    test_add_pointer<float Class::*const&, float Class::*const*>();
    test_add_pointer<void * Class::*const&, void * Class::*const*>();
    test_add_pointer<int Class::*const&&, int Class::*const*>();
    test_add_pointer<float Class::*const&&, float Class::*const*>();
    test_add_pointer<void * Class::*const&&, void * Class::*const*>();
    test_add_pointer<int Class::*volatile>();
    test_add_pointer<float Class::*volatile>();
    test_add_pointer<void * Class::*volatile>();
    test_add_pointer<int Class::*volatile&, int Class::*volatile*>();
    test_add_pointer<float Class::*volatile&, float Class::*volatile*>();
    test_add_pointer<void * Class::*volatile&, void * Class::*volatile*>();
    test_add_pointer<int Class::*volatile&&, int Class::*volatile*>();
    test_add_pointer<float Class::*volatile&&, float Class::*volatile*>();
    test_add_pointer<void * Class::*volatile&&, void * Class::*volatile*>();
    test_add_pointer<int Class::*const volatile>();
    test_add_pointer<float Class::*const volatile>();
    test_add_pointer<void * Class::*const volatile>();
    test_add_pointer<int Class::*const volatile&, int Class::*const volatile*>();
    test_add_pointer<float Class::*const volatile&, float Class::*const volatile*>();
    test_add_pointer<void * Class::*const volatile&, void * Class::*const volatile*>();
    test_add_pointer<int Class::*const volatile&&, int Class::*const volatile*>();
    test_add_pointer<float Class::*const volatile&&, float Class::*const volatile*>();
    test_add_pointer<void * Class::*const volatile&&, void * Class::*const volatile*>();
    test_add_pointer<NonCopyable>();
    test_add_pointer<NonMoveable>();
    test_add_pointer<NonConstructible>();
    test_add_pointer<Tracked>();
    test_add_pointer<TrapConstructible>();
    test_add_pointer<TrapImplicitConversion>();
    test_add_pointer<TrapComma>();
    test_add_pointer<TrapCall>();
    test_add_pointer<TrapSelfAssign>();

    test_add_pointer<void(), void (*)()>();
    test_add_pointer<void()&, void()&>();
    test_add_pointer<void()&&, void() &&>();
    test_add_pointer<void() const, void() const>();
    test_add_pointer<void() const&, void() const&>();
    test_add_pointer<void() const&&, void() const&&>();
    test_add_pointer<void() noexcept, void (*)() noexcept>();
    test_add_pointer<void()& noexcept, void()& noexcept>();
    test_add_pointer<void()&& noexcept, void()&& noexcept>();
    test_add_pointer<void() const noexcept, void() const noexcept>();
    test_add_pointer<void() const& noexcept, void() const& noexcept>();
    test_add_pointer<void() const&& noexcept, void() const&& noexcept>();

    test_add_pointer<void(int), void (*)(int)>();
    test_add_pointer<void(int)&, void(int)&>();
    test_add_pointer<void(int)&&, void(int) &&>();
    test_add_pointer<void(int) const, void(int) const>();
    test_add_pointer<void(int) const&, void(int) const&>();
    test_add_pointer<void(int) const&&, void(int) const&&>();
    test_add_pointer<void(int) noexcept, void (*)(int) noexcept>();
    test_add_pointer<void(int)& noexcept, void(int)& noexcept>();
    test_add_pointer<void(int)&& noexcept, void(int)&& noexcept>();
    test_add_pointer<void(int) const noexcept, void(int) const noexcept>();
    test_add_pointer<void(int) const& noexcept, void(int) const& noexcept>();
    test_add_pointer<void(int) const&& noexcept, void(int) const&& noexcept>();

    test_add_pointer<void(...), void (*)(...)>();
    test_add_pointer<void(...)&, void(...)&>();
    test_add_pointer<void(...)&&, void(...) &&>();
    test_add_pointer<void(...) const, void(...) const>();
    test_add_pointer<void(...) const&, void(...) const&>();
    test_add_pointer<void(...) const&&, void(...) const&&>();
    test_add_pointer<void(...) noexcept, void (*)(...) noexcept>();
    test_add_pointer<void(...)& noexcept, void(...)& noexcept>();
    test_add_pointer<void(...)&& noexcept, void(...)&& noexcept>();
    test_add_pointer<void(...) const noexcept, void(...) const noexcept>();
    test_add_pointer<void(...) const& noexcept, void(...) const& noexcept>();
    test_add_pointer<void(...) const&& noexcept, void(...) const&& noexcept>();

    test_add_pointer<void(int, ...), void (*)(int, ...)>();
    test_add_pointer<void(int, ...)&, void(int, ...)&>();
    test_add_pointer<void(int, ...)&&, void(int, ...) &&>();
    test_add_pointer<void(int, ...) const, void(int, ...) const>();
    test_add_pointer<void(int, ...) const&, void(int, ...) const&>();
    test_add_pointer<void(int, ...) const&&, void(int, ...) const&&>();
    test_add_pointer<void(int, ...) noexcept, void (*)(int, ...) noexcept>();
    test_add_pointer<void(int, ...)& noexcept, void(int, ...)& noexcept>();
    test_add_pointer<void(int, ...)&& noexcept, void(int, ...)&& noexcept>();
    test_add_pointer<void(int, ...) const noexcept, void(int, ...) const noexcept>();
    test_add_pointer<void(int, ...) const& noexcept, void(int, ...) const& noexcept>();
    test_add_pointer<void(int, ...) const&& noexcept, void(int, ...) const&& noexcept>();

    test_add_pointer<int(), int (*)()>();
    test_add_pointer<int()&, int()&>();
    test_add_pointer<int()&&, int() &&>();
    test_add_pointer<int() const, int() const>();
    test_add_pointer<int() const&, int() const&>();
    test_add_pointer<int() const&&, int() const&&>();
    test_add_pointer<int() noexcept, int (*)() noexcept>();
    test_add_pointer<int()& noexcept, int()& noexcept>();
    test_add_pointer<int()&& noexcept, int()&& noexcept>();
    test_add_pointer<int() const noexcept, int() const noexcept>();
    test_add_pointer<int() const& noexcept, int() const& noexcept>();
    test_add_pointer<int() const&& noexcept, int() const&& noexcept>();

    test_add_pointer<int(int), int (*)(int)>();
    test_add_pointer<int(int)&, int(int)&>();
    test_add_pointer<int(int)&&, int(int) &&>();
    test_add_pointer<int(int) const, int(int) const>();
    test_add_pointer<int(int) const&, int(int) const&>();
    test_add_pointer<int(int) const&&, int(int) const&&>();
    test_add_pointer<int(int) noexcept, int (*)(int) noexcept>();
    test_add_pointer<int(int)& noexcept, int(int)& noexcept>();
    test_add_pointer<int(int)&& noexcept, int(int)&& noexcept>();
    test_add_pointer<int(int) const noexcept, int(int) const noexcept>();
    test_add_pointer<int(int) const& noexcept, int(int) const& noexcept>();
    test_add_pointer<int(int) const&& noexcept, int(int) const&& noexcept>();

    test_add_pointer<int(...), int (*)(...)>();
    test_add_pointer<int(...)&, int(...)&>();
    test_add_pointer<int(...)&&, int(...) &&>();
    test_add_pointer<int(...) const, int(...) const>();
    test_add_pointer<int(...) const&, int(...) const&>();
    test_add_pointer<int(...) const&&, int(...) const&&>();
    test_add_pointer<int(...) noexcept, int (*)(...) noexcept>();
    test_add_pointer<int(...)& noexcept, int(...)& noexcept>();
    test_add_pointer<int(...)&& noexcept, int(...)&& noexcept>();
    test_add_pointer<int(...) const noexcept, int(...) const noexcept>();
    test_add_pointer<int(...) const& noexcept, int(...) const& noexcept>();
    test_add_pointer<int(...) const&& noexcept, int(...) const&& noexcept>();

    test_add_pointer<int(int, ...), int (*)(int, ...)>();
    test_add_pointer<int(int, ...)&, int(int, ...)&>();
    test_add_pointer<int(int, ...)&&, int(int, ...) &&>();
    test_add_pointer<int(int, ...) const, int(int, ...) const>();
    test_add_pointer<int(int, ...) const&, int(int, ...) const&>();
    test_add_pointer<int(int, ...) const&&, int(int, ...) const&&>();
    test_add_pointer<int(int, ...) noexcept, int (*)(int, ...) noexcept>();
    test_add_pointer<int(int, ...)& noexcept, int(int, ...)& noexcept>();
    test_add_pointer<int(int, ...)&& noexcept, int(int, ...)&& noexcept>();
    test_add_pointer<int(int, ...) const noexcept, int(int, ...) const noexcept>();
    test_add_pointer<int(int, ...) const& noexcept, int(int, ...) const& noexcept>();
    test_add_pointer<int(int, ...) const&& noexcept, int(int, ...) const&& noexcept>();

    test_add_pointer<void (*)()>();
    test_add_pointer<void (*)() noexcept>();

    test_add_pointer<void (*)(int)>();
    test_add_pointer<void (*)(int) noexcept>();

    test_add_pointer<void (*)(...)>();
    test_add_pointer<void (*)(...) noexcept>();

    test_add_pointer<void (*)(int, ...)>();
    test_add_pointer<void (*)(int, ...) noexcept>();

    test_add_pointer<int (*)()>();
    test_add_pointer<int (*)() noexcept>();

    test_add_pointer<int (*)(int)>();
    test_add_pointer<int (*)(int) noexcept>();

    test_add_pointer<int (*)(...)>();
    test_add_pointer<int (*)(...) noexcept>();

    test_add_pointer<int (*)(int, ...)>();
    test_add_pointer<int (*)(int, ...) noexcept>();

    test_add_pointer<void (&)(), void (*)()>();
    test_add_pointer<void (&)() noexcept, void (*)() noexcept>();

    test_add_pointer<void (&)(int), void (*)(int)>();
    test_add_pointer<void (&)(int) noexcept, void (*)(int) noexcept>();

    test_add_pointer<void (&)(...), void (*)(...)>();
    test_add_pointer<void (&)(...) noexcept, void (*)(...) noexcept>();

    test_add_pointer<void (&)(int, ...), void (*)(int, ...)>();
    test_add_pointer<void (&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_add_pointer<int (&)(), int (*)()>();
    test_add_pointer<int (&)() noexcept, int (*)() noexcept>();

    test_add_pointer<int (&)(int), int (*)(int)>();
    test_add_pointer<int (&)(int) noexcept, int (*)(int) noexcept>();

    test_add_pointer<int (&)(...), int (*)(...)>();
    test_add_pointer<int (&)(...) noexcept, int (*)(...) noexcept>();

    test_add_pointer<int (&)(int, ...), int (*)(int, ...)>();
    test_add_pointer<int (&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_add_pointer<void(&&)(), void (*)()>();
    test_add_pointer<void(&&)() noexcept, void (*)() noexcept>();

    test_add_pointer<void(&&)(int), void (*)(int)>();
    test_add_pointer<void(&&)(int) noexcept, void (*)(int) noexcept>();

    test_add_pointer<void(&&)(...), void (*)(...)>();
    test_add_pointer<void(&&)(...) noexcept, void (*)(...) noexcept>();

    test_add_pointer<void(&&)(int, ...), void (*)(int, ...)>();
    test_add_pointer<void(&&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_add_pointer<int(&&)(), int (*)()>();
    test_add_pointer<int(&&)() noexcept, int (*)() noexcept>();

    test_add_pointer<int(&&)(int), int (*)(int)>();
    test_add_pointer<int(&&)(int) noexcept, int (*)(int) noexcept>();

    test_add_pointer<int(&&)(...), int (*)(...)>();
    test_add_pointer<int(&&)(...) noexcept, int (*)(...) noexcept>();

    test_add_pointer<int(&&)(int, ...), int (*)(int, ...)>();
    test_add_pointer<int(&&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_add_pointer<void (Class::*)()>();
    test_add_pointer<void (Class::*)()&>();
    test_add_pointer<void (Class::*)() &&>();
    test_add_pointer<void (Class::*)() const>();
    test_add_pointer<void (Class::*)() const&>();
    test_add_pointer<void (Class::*)() const&&>();
    test_add_pointer<void (Class::*)() noexcept>();
    test_add_pointer<void (Class::*)()& noexcept>();
    test_add_pointer<void (Class::*)()&& noexcept>();
    test_add_pointer<void (Class::*)() const noexcept>();
    test_add_pointer<void (Class::*)() const& noexcept>();
    test_add_pointer<void (Class::*)() const&& noexcept>();

    test_add_pointer<void (Class::*)(int)>();
    test_add_pointer<void (Class::*)(int)&>();
    test_add_pointer<void (Class::*)(int) &&>();
    test_add_pointer<void (Class::*)(int) const>();
    test_add_pointer<void (Class::*)(int) const&>();
    test_add_pointer<void (Class::*)(int) const&&>();
    test_add_pointer<void (Class::*)(int) noexcept>();
    test_add_pointer<void (Class::*)(int)& noexcept>();
    test_add_pointer<void (Class::*)(int)&& noexcept>();
    test_add_pointer<void (Class::*)(int) const noexcept>();
    test_add_pointer<void (Class::*)(int) const& noexcept>();
    test_add_pointer<void (Class::*)(int) const&& noexcept>();

    test_add_pointer<void (Class::*)(...)>();
    test_add_pointer<void (Class::*)(...)&>();
    test_add_pointer<void (Class::*)(...) &&>();
    test_add_pointer<void (Class::*)(...) const>();
    test_add_pointer<void (Class::*)(...) const&>();
    test_add_pointer<void (Class::*)(...) const&&>();
    test_add_pointer<void (Class::*)(...) noexcept>();
    test_add_pointer<void (Class::*)(...)& noexcept>();
    test_add_pointer<void (Class::*)(...)&& noexcept>();
    test_add_pointer<void (Class::*)(...) const noexcept>();
    test_add_pointer<void (Class::*)(...) const& noexcept>();
    test_add_pointer<void (Class::*)(...) const&& noexcept>();

    test_add_pointer<void (Class::*)(int, ...)>();
    test_add_pointer<void (Class::*)(int, ...)&>();
    test_add_pointer<void (Class::*)(int, ...) &&>();
    test_add_pointer<void (Class::*)(int, ...) const>();
    test_add_pointer<void (Class::*)(int, ...) const&>();
    test_add_pointer<void (Class::*)(int, ...) const&&>();
    test_add_pointer<void (Class::*)(int, ...) noexcept>();
    test_add_pointer<void (Class::*)(int, ...)& noexcept>();
    test_add_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_add_pointer<void (Class::*)(int, ...) const noexcept>();
    test_add_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_add_pointer<void (Class::*)(int, ...) const&& noexcept>();

    test_add_pointer<int (Class::*)()>();
    test_add_pointer<int (Class::*)()&>();
    test_add_pointer<int (Class::*)() &&>();
    test_add_pointer<int (Class::*)() const>();
    test_add_pointer<int (Class::*)() const&>();
    test_add_pointer<int (Class::*)() const&&>();
    test_add_pointer<int (Class::*)() noexcept>();
    test_add_pointer<int (Class::*)()& noexcept>();
    test_add_pointer<int (Class::*)()&& noexcept>();
    test_add_pointer<int (Class::*)() const noexcept>();
    test_add_pointer<int (Class::*)() const& noexcept>();
    test_add_pointer<int (Class::*)() const&& noexcept>();

    test_add_pointer<int (Class::*)(int)>();
    test_add_pointer<int (Class::*)(int)&>();
    test_add_pointer<int (Class::*)(int) &&>();
    test_add_pointer<int (Class::*)(int) const>();
    test_add_pointer<int (Class::*)(int) const&>();
    test_add_pointer<int (Class::*)(int) const&&>();
    test_add_pointer<int (Class::*)(int) noexcept>();
    test_add_pointer<int (Class::*)(int)& noexcept>();
    test_add_pointer<int (Class::*)(int)&& noexcept>();
    test_add_pointer<int (Class::*)(int) const noexcept>();
    test_add_pointer<int (Class::*)(int) const& noexcept>();
    test_add_pointer<int (Class::*)(int) const&& noexcept>();

    test_add_pointer<int (Class::*)(...)>();
    test_add_pointer<int (Class::*)(...)&>();
    test_add_pointer<int (Class::*)(...) &&>();
    test_add_pointer<int (Class::*)(...) const>();
    test_add_pointer<int (Class::*)(...) const&>();
    test_add_pointer<int (Class::*)(...) const&&>();
    test_add_pointer<int (Class::*)(...) noexcept>();
    test_add_pointer<int (Class::*)(...)& noexcept>();
    test_add_pointer<int (Class::*)(...)&& noexcept>();
    test_add_pointer<int (Class::*)(...) const noexcept>();
    test_add_pointer<int (Class::*)(...) const& noexcept>();
    test_add_pointer<int (Class::*)(...) const&& noexcept>();

    test_add_pointer<int (Class::*)(int, ...)>();
    test_add_pointer<int (Class::*)(int, ...)&>();
    test_add_pointer<int (Class::*)(int, ...) &&>();
    test_add_pointer<int (Class::*)(int, ...) const>();
    test_add_pointer<int (Class::*)(int, ...) const&>();
    test_add_pointer<int (Class::*)(int, ...) const&&>();
    test_add_pointer<int (Class::*)(int, ...) noexcept>();
    test_add_pointer<int (Class::*)(int, ...)& noexcept>();
    test_add_pointer<int (Class::*)(int, ...)&& noexcept>();
    test_add_pointer<int (Class::*)(int, ...) const noexcept>();
    test_add_pointer<int (Class::*)(int, ...) const& noexcept>();
    test_add_pointer<int (Class::*)(int, ...) const&& noexcept>();

    //  LWG 2101 specifically talks about add_pointer and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<FunctionPtr>();
    test_function0<void()>();
    test_function1<void() const>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const&>();
    test_function1<void() const&&>();

    test_function0<void() noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void()& noexcept>();
    test_function1<void()&& noexcept>();
    test_function1<void() const& noexcept>();
    test_function1<void() const&& noexcept>();

    //  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_function0<MemberFunctionPtr>();
    test_function0<void (Foo::*)()>();
    test_function0<void (Foo::*)() const>();
    test_function0<void (Foo::*)()&>();
    test_function0<void (Foo::*)() &&>();
    test_function0<void (Foo::*)() const&>();
    test_function0<void (Foo::*)() const&&>();

    test_function0<void (Foo::*)() noexcept>();
    test_function0<void (Foo::*)() const noexcept>();
    test_function0<void (Foo::*)()& noexcept>();
    test_function0<void (Foo::*)()&& noexcept>();
    test_function0<void (Foo::*)() const& noexcept>();
    test_function0<void (Foo::*)() const&& noexcept>();
}
