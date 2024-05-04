#ifndef INCG_PHI_CORE_OBSERVER_PTR_HPP
#define INCG_PHI_CORE_OBSERVER_PTR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/flat_ptr.hpp"
#include "phi/core/move.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/forward/observer_ptr.hpp"
#include "phi/forward/ref_ptr.hpp"
#include "phi/forward/scope_ptr.hpp"
#include "phi/forward/std/hash.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_convertible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wnonnull-compare")
// gcc-6 wrongly complains about ignoring return values
#if PHI_COMPILER_IS_BELOW(GCC, 7, 0, 0)
PHI_GCC_SUPPRESS_WARNING("-Wunused-result")
#endif

// A non owning smart pointer
template <typename TypeT>
class PHI_ATTRIBUTE_POINTER observer_ptr
{
public:
    using this_type       = observer_ptr<TypeT>;
    using not_null_type   = not_null_observer_ptr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    PHI_CONSTEXPR observer_ptr() PHI_NOEXCEPT : m_Ptr(nullptr)
    {}

    ~observer_ptr() = default;

    PHI_CONSTEXPR observer_ptr(nullptr_t) PHI_NOEXCEPT : m_Ptr(nullptr)
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_CONSTEXPR observer_ptr(OtherT* ptr) PHI_NOEXCEPT : m_Ptr(ptr)
    {}

    PHI_CONSTEXPR observer_ptr(const observer_ptr<TypeT>& other) PHI_NOEXCEPT : m_Ptr{other.m_Ptr}
    {}

    PHI_CONSTEXPR observer_ptr(observer_ptr<TypeT>&& other) PHI_NOEXCEPT : m_Ptr{move(other.m_Ptr)}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_CONSTEXPR observer_ptr(const observer_ptr<OtherT>& other) PHI_NOEXCEPT : m_Ptr(other.get())
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_CONSTEXPR observer_ptr(observer_ptr<OtherT>&& other) PHI_NOEXCEPT : m_Ptr(move(other.get()))
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(const not_null_observer_ptr<OtherT>& other) PHI_NOEXCEPT
        : m_Ptr(other.get())
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(not_null_observer_ptr<OtherT>&& other) PHI_NOEXCEPT
        : m_Ptr(move(other.get()))
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(scope_ptr<OtherT>& other) PHI_NOEXCEPT : m_Ptr{other.get()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(not_null_scope_ptr<OtherT>& other) PHI_NOEXCEPT
        : m_Ptr{other.get()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(ref_ptr<OtherT>& other) PHI_NOEXCEPT : m_Ptr{other.get()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(not_null_ref_ptr<OtherT>& other) PHI_NOEXCEPT
        : m_Ptr{other.get()}
    {}

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(nullptr_t) PHI_NOEXCEPT
    {
        m_Ptr = nullptr;

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(OtherT* ptr) PHI_NOEXCEPT
    {
        m_Ptr = ptr;

        return *this;
    }

    observer_ptr<TypeT>& operator=(const observer_ptr<TypeT>& other) = default;

    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    observer_ptr<TypeT>& operator=(observer_ptr<TypeT>&& other) = default;

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(const observer_ptr<OtherT>& other)
            PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(observer_ptr<OtherT>&& other) PHI_NOEXCEPT
    {
        m_Ptr = move(other.get());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(const not_null_observer_ptr<TypeT>& other)
            PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(not_null_observer_ptr<TypeT>&& other)
            PHI_NOEXCEPT
    {
        m_Ptr = move(other.get());

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(
            const not_null_observer_ptr<OtherT>& other) PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(not_null_observer_ptr<OtherT>&& other)
            PHI_NOEXCEPT
    {
        m_Ptr = move(other.get());

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(scope_ptr<OtherT>& other) PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(not_null_scope_ptr<OtherT>& other)
            PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(ref_ptr<OtherT>& other) PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(not_null_ref_ptr<OtherT>& other)
            PHI_NOEXCEPT
    {
        m_Ptr = other.get();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL TypeT* operator->() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL const TypeT* operator->() const
            PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    PHI_CONSTEXPR explicit operator bool() const PHI_NOEXCEPT
    {
        return get() != nullptr;
    }

    PHI_CONSTEXPR explicit operator boolean() const PHI_NOEXCEPT
    {
        return get() != nullptr;
    }

    PHI_CONSTEXPR explicit operator TypeT*() const PHI_NOEXCEPT
    {
        return get();
    }

    template <typename OtherT, enable_if_t<is_convertible<TypeT*, OtherT*>::value, int> = 0>
    PHI_CONSTEXPR explicit operator OtherT*() const PHI_NOEXCEPT
    {
        return get();
    }

    PHI_NODISCARD PHI_CONSTEXPR TypeT* get() const PHI_NOEXCEPT
    {
        return m_Ptr;
    }

    PHI_NODISCARD PHI_CONSTEXPR flat_ptr flat() PHI_NOEXCEPT
    {
        return flat_ptr{get()};
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_flat_ptr not_null_flat() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Trying to create not_null_flat_ptr from nullptr");
        return not_null_flat_ptr{get()};
    }

    template <typename OtherT = TypeT, enable_if_t<is_convertible<TypeT*, OtherT*>::value, int> = 0>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<OtherT> not_null() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Cannot release to not null with nullptr");

        return not_null_observer_ptr<OtherT>(static_cast<OtherT*>(get()));
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* ptr = nullptr) PHI_NOEXCEPT
    {
        m_Ptr = ptr;
    }

    PHI_EXTENDED_CONSTEXPR void swap(observer_ptr& other) PHI_NOEXCEPT
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(observer_ptr<LhsT> lhs, observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
PHI_CONSTEXPR boolean operator==(observer_ptr<LhsT> lhs, nullptr_t) PHI_NOEXCEPT
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
PHI_CONSTEXPR boolean operator==(nullptr_t, observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(observer_ptr<LhsT>          lhs,
                                 not_null_observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs.get();
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(not_null_observer_ptr<LhsT> lhs,
                                 observer_ptr<RhsT>          rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs.get();
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(observer_ptr<LhsT> lhs, RhsT* rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(LhsT* lhs, observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs == rhs.get();
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(observer_ptr<LhsT> lhs, observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
PHI_CONSTEXPR boolean operator!=(observer_ptr<LhsT> lhs, nullptr_t) PHI_NOEXCEPT
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
PHI_CONSTEXPR boolean operator!=(nullptr_t, observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return rhs.get() != nullptr;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(observer_ptr<LhsT>          lhs,
                                 not_null_observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs.get();
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(not_null_observer_ptr<LhsT> lhs,
                                 observer_ptr<RhsT>          rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs.get();
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(observer_ptr<LhsT> lhs, RhsT* rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(LhsT* lhs, observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs != rhs.get();
}

// A non owning smart pointer which may not be null
template <typename TypeT>
class PHI_ATTRIBUTE_POINTER not_null_observer_ptr
{
public:
    using this_type       = not_null_observer_ptr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    not_null_observer_ptr() = delete;

    not_null_observer_ptr(nullptr_t) = delete;

    ~not_null_observer_ptr() = default;

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(OtherT* ptr) PHI_NOEXCEPT
        : m_Ptr(ptr)
    {
        PHI_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr.");
    }

    PHI_CONSTEXPR not_null_observer_ptr(const not_null_observer_ptr<TypeT>& other) PHI_NOEXCEPT
        : m_Ptr{other.get()}
    {}

    PHI_CONSTEXPR not_null_observer_ptr(not_null_observer_ptr<TypeT>&& other) PHI_NOEXCEPT
        : m_Ptr{move(other.get())}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(const not_null_observer_ptr<OtherT>& other)
            PHI_NOEXCEPT : m_Ptr(other.get())
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(not_null_observer_ptr<OtherT>&& other) PHI_NOEXCEPT
        : m_Ptr(other.get())
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(not_null_scope_ptr<OtherT>& other) PHI_NOEXCEPT
        : m_Ptr(other.get())
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(not_null_ref_ptr<OtherT>& other) PHI_NOEXCEPT
        : m_Ptr(other.get())
    {}

    not_null_observer_ptr<TypeT>& operator=(nullptr_t) = delete;

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(
            OtherT* ptr) PHI_NOEXCEPT
    {
        PHI_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");

        m_Ptr = ptr;

        return *this;
    }

    not_null_observer_ptr<TypeT>& operator=(const not_null_observer_ptr<TypeT>& other) = default;

    not_null_observer_ptr<TypeT>& operator=(not_null_observer_ptr<TypeT>&& other) = default;

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(
            const not_null_observer_ptr<OtherT>& other) PHI_NOEXCEPT
    {
        PHI_ASSERT(other.get() != nullptr,
                   "Trying to assign nullptr to phi::not_null_observer_ptr.");

        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(
            not_null_observer_ptr<OtherT>&& other) PHI_NOEXCEPT
    {
        PHI_ASSERT(other.get() != nullptr,
                   "Trying to assign nullptr to phi::not_null_observer_ptr.");

        m_Ptr = move(other.get());

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(
            not_null_scope_ptr<OtherT>& other) PHI_NOEXCEPT
    {
        PHI_ASSERT(other.get() != nullptr,
                   "Trying to assign nullptr to phi::not_null_observer_ptr.");

        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, enable_if_t<is_convertible<OtherT*, TypeT*>::value, int> = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(not_null_ref_ptr<OtherT>& other)
            PHI_NOEXCEPT
    {
        PHI_ASSERT(other.get() != nullptr,
                   "Trying to assign nullptr to phi::not_null_observer_ptr.");

        m_Ptr = other.get();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*() PHI_NOEXCEPT
    {
        PHI_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const PHI_NOEXCEPT
    {
        PHI_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL TypeT* operator->() PHI_NOEXCEPT
    {
        PHI_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL const TypeT* operator->() const
            PHI_NOEXCEPT
    {
        PHI_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    operator bool() = delete;

    operator boolean() = delete;

    PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR explicit operator TypeT*() const PHI_NOEXCEPT
    {
        return get();
    }

    template <typename OtherT, enable_if_t<is_convertible<TypeT*, OtherT*>::value, int> = 0>
    PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR explicit operator OtherT*() const PHI_NOEXCEPT
    {
        return get();
    }

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR TypeT* get() const PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Trying to access a nullptr");

        return m_Ptr;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_flat_ptr not_null_flat() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Trying to create not_null_flat_ptr from nullptr");
        return not_null_flat_ptr{get()};
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* ptr) PHI_NOEXCEPT PHI_ATTRIBUTE_NONNULL
    {
        PHI_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");

        m_Ptr = ptr;
    }

    void reset(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR void swap(not_null_observer_ptr<TypeT>& other) PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");
        PHI_ASSERT(other.m_Ptr != nullptr,
                   "Trying to assign nullptr to phi::not_null_observer_ptr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

private:
    TypeT* m_Ptr;
};

PHI_GCC_SUPPRESS_WARNING_POP()

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(not_null_observer_ptr<LhsT> lhs,
                                 not_null_observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
boolean operator==(not_null_observer_ptr<LhsT>, nullptr_t) = delete;

template <typename RhsT>
boolean operator==(nullptr_t, not_null_observer_ptr<RhsT>) = delete;

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(not_null_observer_ptr<LhsT> lhs, RhsT* rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(LhsT* lhs, not_null_observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs == rhs.get();
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(not_null_observer_ptr<LhsT> lhs,
                                 not_null_observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
boolean operator!=(not_null_observer_ptr<LhsT>, nullptr_t) = delete;

template <typename RhsT>
boolean operator!=(nullptr_t, not_null_observer_ptr<RhsT>) = delete;

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(not_null_observer_ptr<LhsT> lhs, RhsT* rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(LhsT* lhs, not_null_observer_ptr<RhsT> rhs) PHI_NOEXCEPT
{
    return lhs != rhs.get();
}

// make functions

template <typename TypeT>
PHI_NODISCARD PHI_CONSTEXPR observer_ptr<TypeT> make_observer(TypeT* ptr) PHI_NOEXCEPT
{
    return observer_ptr<TypeT>(ptr);
}

template <typename TypeT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR not_null_observer_ptr<TypeT>
                                                  make_not_null_observer(TypeT* ptr) PHI_NOEXCEPT
{
    return not_null_observer_ptr<TypeT>(ptr);
}

template <typename TypeT>
not_null_observer_ptr<TypeT> make_not_null_observer(nullptr_t ptr) = delete;

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT>
struct hash<phi::observer_ptr<TypeT>>
{
    phi::size_t operator()(phi::observer_ptr<TypeT> ptr) const PHI_NOEXCEPT
    {
        return std::hash<TypeT*>()(ptr.get());
    }
};

template <typename TypeT>
struct hash<phi::not_null_observer_ptr<TypeT>>
{
    phi::size_t operator()(phi::not_null_observer_ptr<TypeT> ptr) const PHI_NOEXCEPT
    {
        return std::hash<TypeT*>()(ptr.get());
    }
};

template <>
struct hash<phi::not_null_observer_ptr<nullptr_t>>
{
    phi::size_t operator()(phi::not_null_observer_ptr<nullptr_t> ptr) = delete;
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_OBSERVER_PTR_HPP
