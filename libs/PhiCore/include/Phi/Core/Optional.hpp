// This file is heavily inspired by Sy Brands Optional library https://github.com/TartanLlama/Optional
// licensed under CC0 https://github.com/TartanLlama/Optional/blob/master/COPYING
// Original file at https://github.com/TartanLlama/Optional/blob/master/include/tl/Optional.hpp

#ifndef INCG_PHI_CORE_OPTIONAL_HPP
#define INCG_PHI_CORE_OPTIONAL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Core/AddressOf.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Invoke.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/TypeTraits/conjunction.hpp"
#include "Phi/TypeTraits/decay.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/invoke_result.hpp"
#include "Phi/TypeTraits/is_assignable.hpp"
#include "Phi/TypeTraits/is_constructible.hpp"
#include "Phi/TypeTraits/is_convertible.hpp"
#include "Phi/TypeTraits/is_copy_assignable.hpp"
#include "Phi/TypeTraits/is_copy_constructible.hpp"
#include "Phi/TypeTraits/is_lvalue_reference.hpp"
#include "Phi/TypeTraits/is_move_assignable.hpp"
#include "Phi/TypeTraits/is_move_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_move_assignable.hpp"
#include "Phi/TypeTraits/is_nothrow_move_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_swappable.hpp"
#include "Phi/TypeTraits/is_scalar.hpp"
#include "Phi/TypeTraits/is_swappable.hpp"
#include "Phi/TypeTraits/is_trivially_copy_assignable.hpp"
#include "Phi/TypeTraits/is_trivially_copy_constructible.hpp"
#include "Phi/TypeTraits/is_trivially_destructible.hpp"
#include "Phi/TypeTraits/is_trivially_move_assignable.hpp"
#include "Phi/TypeTraits/is_trivially_move_constructible.hpp"
#include "Phi/TypeTraits/is_void.hpp"
#include "Phi/TypeTraits/remove_const.hpp"
#include "Phi/TypeTraits/void_t.hpp"
#include <functional>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

/// Used to represent an Optional with no data; essentially a bool
struct monostate
{};

///  A tag type to tell Optional to construct its value in-place
struct in_place_t
{
    explicit in_place_t() = default;
};
/// A tag to tell Optional to construct its value in-place
static constexpr in_place_t in_place{};

template <typename TypeT>
class Optional;

namespace detail
{
    // Check if invoking F for some Us returns void
    template <typename FuncT, typename = void, typename... ArgsT>
    struct returns_void_impl;

    template <typename FuncT, typename... ArgsT>
    struct returns_void_impl<FuncT, void_t<invoke_result_t<FuncT, ArgsT...>>, ArgsT...>
        : public is_void<invoke_result_t<FuncT, ArgsT...>>
    {};

    template <typename FuncT, typename... ArgsT>
    using returns_void = returns_void_impl<FuncT, void, ArgsT...>;

    template <typename TypeT, typename... ArgsT>
    using enable_if_ret_void = enable_if_t<returns_void<TypeT&&, ArgsT...>::value>;

    template <typename TypeT, typename... ArgsT>
    using disable_if_ret_void = enable_if_t<!returns_void<TypeT&&, ArgsT...>::value>;

    template <typename TypeT, typename OtherT>
    using enable_forward_value = enable_if_t<is_constructible_v<TypeT, OtherT&&> &&
                                             !is_same_v<decay_t<OtherT>, in_place_t> &&
                                             !is_same_v<Optional<TypeT>, decay_t<OtherT>>>;

    template <typename TypeT, typename OtherT>
    using enable_assign_forward =
            enable_if_t<!is_same_v<Optional<TypeT>, decay_t<OtherT>> &&
                        !conjunction<is_scalar<TypeT>, is_same<TypeT, decay_t<OtherT>>>::value &&
                        is_constructible<TypeT, OtherT>::value &&
                        is_assignable<TypeT&, OtherT>::value>;

    template <typename TypeT, typename Type2T, typename OtherT>
    using enable_from_other =
            enable_if_t<is_constructible<TypeT, OtherT>::value &&
                        !is_constructible<TypeT, Optional<Type2T>&>::value &&
                        !is_constructible<TypeT, Optional<Type2T>&&>::value &&
                        !is_constructible<TypeT, const Optional<Type2T>&>::value &&
                        !is_constructible<TypeT, const Optional<Type2T>&&>::value &&
                        !is_convertible<Optional<Type2T>&, TypeT>::value &&
                        !is_convertible<Optional<Type2T>&&, TypeT>::value &&
                        !is_convertible<const Optional<Type2T>&, TypeT>::value &&
                        !is_convertible<const Optional<Type2T>&&, TypeT>::value>;

    template <typename TypeT, typename Type2T, typename OtherT>
    using enable_assign_from_other =
            enable_if_t<is_constructible<TypeT, OtherT>::value &&
                        is_assignable<TypeT&, OtherT>::value &&
                        !is_constructible<TypeT, Optional<Type2T>&>::value &&
                        !is_constructible<TypeT, Optional<Type2T>&&>::value &&
                        !is_constructible<TypeT, const Optional<Type2T>&>::value &&
                        !is_constructible<TypeT, const Optional<Type2T>&&>::value &&
                        !is_convertible<Optional<Type2T>&, TypeT>::value &&
                        !is_convertible<Optional<Type2T>&&, TypeT>::value &&
                        !is_convertible<const Optional<Type2T>&, TypeT>::value &&
                        !is_convertible<const Optional<Type2T>&&, TypeT>::value &&
                        !is_assignable<TypeT&, Optional<Type2T>&>::value &&
                        !is_assignable<TypeT&, Optional<Type2T>&&>::value &&
                        !is_assignable<TypeT&, const Optional<Type2T>&>::value &&
                        !is_assignable<TypeT&, const Optional<Type2T>&&>::value>;

    // Trait for checking if a type is a phi::Optional
    template <typename TypeT>
    struct is_optional_impl : false_type
    {};

    template <typename TypeT>
    struct is_optional_impl<Optional<TypeT>> : true_type
    {};

    template <typename TypeT>
    using is_optional = is_optional_impl<decay_t<TypeT>>;

    // The storage base manages the actual storage, and correctly propagates
    // trivial destruction from T. This case is for when T is not trivially
    // destructible.
    template <typename TypeT, bool = is_trivially_destructible<TypeT>::value>
    struct optional_storage_base
    {
        constexpr optional_storage_base() noexcept
            : m_dummy()
            , m_has_value(false)
        {}

        template <typename... ArgsT>
        constexpr optional_storage_base(in_place_t, ArgsT&&... args)
            : m_Value(phi::forward<ArgsT>(args)...)
            , m_has_value(true)
        {}

        ~optional_storage_base()
        {
            if (m_has_value)
            {
                m_Value.~TypeT();
                m_has_value = false;
            }
        }

        struct dummy
        {};

        union
        {
            dummy m_dummy;
            TypeT m_Value;
        };

        bool m_has_value;
    };

    // This case is for when T is trivially destructible.
    template <typename TypeT>
    struct optional_storage_base<TypeT, true>
    {
        constexpr optional_storage_base() noexcept
            : m_dummy()
            , m_has_value(false)
        {}

        template <typename... OtherT>
        constexpr optional_storage_base(in_place_t, OtherT&&... u)
            : m_Value(phi::forward<OtherT>(u)...)
            , m_has_value(true)
        {}

        // No destructor, so this class is trivially destructible

        struct dummy
        {};

        union
        {
            dummy m_dummy;
            TypeT m_Value;
        };

        bool m_has_value = false;
    };

    // This base class provides some handy member functions which can be used in
    // further derived classes
    template <typename TypeT>
    struct optional_operations_base : optional_storage_base<TypeT>
    {
        using optional_storage_base<TypeT>::optional_storage_base;

        void hard_reset() noexcept
        {
            get().~TypeT();
            this->m_has_value = false;
        }

        template <typename... ArgsT>
        void construct(ArgsT&&... args) noexcept
        {
            new (phi::addressof(this->m_Value)) TypeT(phi::forward<ArgsT>(args)...);
            this->m_has_value = true;
        }

        template <typename OptT>
        void assign(OptT&& rhs)
        {
            if (this->has_value())
            {
                if (rhs.has_value())
                {
                    this->m_Value = phi::forward<OptT>(rhs).get();
                }
                else
                {
                    this->m_Value.~TypeT();
                    this->m_has_value = false;
                }
            }

            else if (rhs.has_value())
            {
                construct(phi::forward<OptT>(rhs).get());
            }
        }

        PHI_NODISCARD constexpr bool has_value() const
        {
            return this->m_has_value;
        }

        PHI_NODISCARD constexpr TypeT& get() &
        {
            return this->m_Value;
        }

        PHI_NODISCARD constexpr const TypeT& get() const&
        {
            return this->m_Value;
        }

        PHI_NODISCARD constexpr TypeT&& get() &&
        {
            return phi::move(this->m_Value);
        }

        PHI_NODISCARD constexpr const TypeT&& get() const&&
        {
            return phi::move(this->m_Value);
        }
    };

    // This class manages conditionally having a trivial copy constructor
    // This specialization is for when T is trivially copy constructible
    template <typename TypeT, bool = is_trivially_copy_constructible<TypeT>::value>
    struct optional_copy_base : optional_operations_base<TypeT>
    {
        using optional_operations_base<TypeT>::optional_operations_base;
    };

    // This specialization is for when T is not trivially copy constructible
    template <typename TypeT>
    struct optional_copy_base<TypeT, false> : optional_operations_base<TypeT>
    {
        using optional_operations_base<TypeT>::optional_operations_base;

        optional_copy_base() = default;

        optional_copy_base(const optional_copy_base& rhs)
        {
            if (rhs.has_value())
            {
                this->construct(rhs.get());
            }
            else
            {
                this->m_has_value = false;
            }
        }

        optional_copy_base(optional_copy_base&& rhs) = default;

        optional_copy_base& operator=(const optional_copy_base& rhs) = default;

        optional_copy_base& operator=(optional_copy_base&& rhs) = default;
    };

    // This class manages conditionally having a trivial move constructor.
    template <typename TypeT, bool = is_trivially_move_constructible<TypeT>::value>
    struct optional_move_base : optional_copy_base<TypeT>
    {
        using optional_copy_base<TypeT>::optional_copy_base;
    };

    template <typename TypeT>
    struct optional_move_base<TypeT, false> : optional_copy_base<TypeT>
    {
        using optional_copy_base<TypeT>::optional_copy_base;

        optional_move_base()                              = default;
        optional_move_base(const optional_move_base& rhs) = default;

        optional_move_base(optional_move_base&& rhs) noexcept(
                is_nothrow_move_constructible<TypeT>::value)
        {
            if (rhs.has_value())
            {
                this->construct(phi::move(rhs.get()));
            }
            else
            {
                this->m_has_value = false;
            }
        }
        optional_move_base& operator=(const optional_move_base& rhs) = default;
        optional_move_base& operator=(optional_move_base&& rhs) = default;
    };

    // This class manages conditionally having a trivial copy assignment operator
    template <typename TypeT,
              bool = is_trivially_copy_assignable<TypeT>::value&& is_trivially_copy_constructible<
                      TypeT>::value&& is_trivially_destructible<TypeT>::value>
    struct optional_copy_assign_base : public optional_move_base<TypeT>
    {
        using optional_move_base<TypeT>::optional_move_base;
    };

    template <typename TypeT>
    struct optional_copy_assign_base<TypeT, false> : public optional_move_base<TypeT>
    {
        using optional_move_base<TypeT>::optional_move_base;

        optional_copy_assign_base()                                     = default;
        optional_copy_assign_base(const optional_copy_assign_base& rhs) = default;

        optional_copy_assign_base(optional_copy_assign_base&& rhs) = default;
        optional_copy_assign_base& operator=(const optional_copy_assign_base& rhs)
        {
            this->assign(rhs);
            return *this;
        }
        optional_copy_assign_base& operator=(optional_copy_assign_base&& rhs) = default;
    };

    // This class manages conditionally having a trivial move assignment operator
    template <typename TypeT,
              bool = is_trivially_destructible<TypeT>::value&& is_trivially_move_constructible<
                      TypeT>::value&& is_trivially_move_assignable<TypeT>::value>
    struct optional_move_assign_base : public optional_copy_assign_base<TypeT>
    {
        using optional_copy_assign_base<TypeT>::optional_copy_assign_base;
    };

    template <typename TypeT>
    struct optional_move_assign_base<TypeT, false> : public optional_copy_assign_base<TypeT>
    {
        using optional_copy_assign_base<TypeT>::optional_copy_assign_base;

        optional_move_assign_base()                                     = default;
        optional_move_assign_base(const optional_move_assign_base& rhs) = default;

        optional_move_assign_base(optional_move_assign_base&& rhs) = default;

        optional_move_assign_base& operator=(const optional_move_assign_base& rhs) = default;

        optional_move_assign_base& operator=(optional_move_assign_base&& rhs) noexcept(
                is_nothrow_move_constructible<TypeT>::value&&
                        is_nothrow_move_assignable<TypeT>::value)
        {
            this->assign(phi::move(rhs));
            return *this;
        }
    };

    // optional_delete_ctor_base will conditionally delete copy and move
    // constructors depending on whether T is copy/move constructible
    template <typename TypeT, bool EnableCopy = is_copy_constructible<TypeT>::value,
              bool EnableMove = is_move_constructible<TypeT>::value>
    struct optional_delete_ctor_base
    {
        optional_delete_ctor_base()                                     = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)     = default;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept = default;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, true, false>
    {
        optional_delete_ctor_base()                                     = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)     = default;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept = delete;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, false, true>
    {
        optional_delete_ctor_base()                                     = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)     = delete;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept = default;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, false, false>
    {
        optional_delete_ctor_base()                                     = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)     = delete;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept = delete;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    // optional_delete_assign_base will conditionally delete copy and move
    // constructors depending on whether TypeT is copy/move constructible + assignable
    template <typename TypeT,
              bool EnableCopy =
                      (is_copy_constructible<TypeT>::value && is_copy_assignable<TypeT>::value),
              bool EnableMove =
                      (is_move_constructible<TypeT>::value && is_move_assignable<TypeT>::value)>
    struct optional_delete_assign_base
    {
        optional_delete_assign_base()                                       = default;
        optional_delete_assign_base(const optional_delete_assign_base&)     = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = default;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, true, false>
    {
        optional_delete_assign_base()                                       = default;
        optional_delete_assign_base(const optional_delete_assign_base&)     = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = default;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = delete;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, false, true>
    {
        optional_delete_assign_base()                                       = default;
        optional_delete_assign_base(const optional_delete_assign_base&)     = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = delete;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, false, false>
    {
        optional_delete_assign_base()                                       = default;
        optional_delete_assign_base(const optional_delete_assign_base&)     = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = delete;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = delete;
    };
} // namespace detail

/// A tag type to represent an empty Optional
struct nullopt_t
{
    struct do_not_use
    {};

    constexpr explicit nullopt_t(do_not_use, do_not_use) noexcept
    {}
};

/// Represents an empty Optional
static constexpr nullopt_t nullopt{nullopt_t::do_not_use{}, nullopt_t::do_not_use{}};

/// An Optional object is an object that contains the storage for another
/// object and manages the lifetime of this contained object, if any. The
/// contained object may be initialized after the Optional object has been
/// initialized, and may be destroyed before the Optional object has been
/// destroyed. The initialization state of the contained object is tracked by
/// the Optional object.
template <typename TypeT>
class Optional : private detail::optional_move_assign_base<TypeT>,
                 private detail::optional_delete_ctor_base<TypeT>,
                 private detail::optional_delete_assign_base<TypeT>
{
    using base = detail::optional_move_assign_base<TypeT>;

    static_assert(!is_same<TypeT, in_place_t>::value,
                  "instantiation of Optional with in_place_t is ill-formed");
    static_assert(!is_same<decay_t<TypeT>, nullopt_t>::value,
                  "instantiation of Optional with nullopt_t is ill-formed");

public:
    using this_type  = Optional<TypeT>;
    using value_type = TypeT;

    /// Constructs an Optional that does not contain a value.
    constexpr Optional() noexcept = default;

    constexpr Optional(nullopt_t) noexcept
    {}

    /// Copy constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed Optional is empty.
    constexpr Optional(const Optional& rhs) = default;

    /// Move constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed Optional is empty.
    constexpr Optional(Optional&& rhs) = default;

    /// Constructs the stored value in-place using the given arguments.
    template <typename... ArgsT>
    constexpr explicit Optional(enable_if_t<is_constructible<TypeT, ArgsT...>::value, in_place_t>,
                                ArgsT&&... args)
        : base(in_place, phi::forward<ArgsT>(args)...)
    {}

    template <typename OtherT, typename... ArgsT>
    constexpr explicit Optional(
            enable_if_t<is_constructible<TypeT, std::initializer_list<OtherT>&, ArgsT&&...>::value,
                        in_place_t>,
            std::initializer_list<OtherT> il, ArgsT&&... args)
    {
        this->construct(il, phi::forward<ArgsT>(args)...);
    }

    /// Constructs the stored value with `u`.
    template <typename OtherT                                      = TypeT,
              enable_if_t<is_convertible<OtherT&&, TypeT>::value>* = nullptr,
              detail::enable_forward_value<TypeT, OtherT>*         = nullptr>
    constexpr Optional(OtherT&& other)
        : base(in_place, phi::forward<OtherT>(other))
    {}

    template <typename OtherT                                       = TypeT,
              enable_if_t<!is_convertible<OtherT&&, TypeT>::value>* = nullptr,
              detail::enable_forward_value<TypeT, OtherT>*          = nullptr>
    constexpr explicit Optional(OtherT&& other)
        : base(in_place, phi::forward<OtherT>(other))
    {}

    /// Converting copy constructor.
    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, const OtherT&>* = nullptr,
              enable_if_t<is_convertible<const OtherT&, TypeT>::value>* = nullptr>
    Optional(const Optional<OtherT>& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(*rhs);
        }
    }

    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, const OtherT&>* = nullptr,
              enable_if_t<!is_convertible<const OtherT&, TypeT>::value>* = nullptr>
    explicit Optional(const Optional<OtherT>& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(*rhs);
        }
    }

    /// Converting move constructor.
    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, OtherT&&>* = nullptr,
              enable_if_t<is_convertible<OtherT&&, TypeT>::value>* = nullptr>
    Optional(Optional<OtherT>&& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(phi::move(*rhs));
        }
    }

    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, OtherT&&>* = nullptr,
              enable_if_t<!is_convertible<OtherT&&, TypeT>::value>* = nullptr>
    explicit Optional(Optional<OtherT>&& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(phi::move(*rhs));
        }
    }

    /// Destroys the stored value if there is one.
    ~Optional() = default;

    /// Assignment to empty.
    ///
    /// Destroys the current value if there is one.
    Optional& operator=(nullopt_t) noexcept
    {
        if (has_value())
        {
            this->m_Value.~TypeT();
            this->m_has_value = false;
        }

        return *this;
    }

    /// Copy assignment.
    ///
    /// Copies the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    Optional& operator=(const Optional& rhs) = default;

    /// Move assignment.
    ///
    /// Moves the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    Optional& operator=(Optional&& rhs) = default;

    /// Assigns the stored value from `u`, destroying the old value if there was
    /// one.
    template <typename OtherT = TypeT, detail::enable_assign_forward<TypeT, OtherT>* = nullptr>
    Optional& operator=(OtherT&& other)
    {
        if (has_value())
        {
            this->m_Value = phi::forward<OtherT>(other);
        }
        else
        {
            this->construct(phi::forward<OtherT>(other));
        }

        return *this;
    }

    /// Converting copy assignment operator.
    ///
    /// Copies the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    template <typename OtherT,
              detail::enable_assign_from_other<TypeT, OtherT, const OtherT&>* = nullptr>
    Optional& operator=(const Optional<OtherT>& rhs)
    {
        if (has_value())
        {
            if (rhs.has_value())
            {
                this->m_Value = *rhs;
            }
            else
            {
                this->hard_reset();
            }
        }

        if (rhs.has_value())
        {
            this->construct(*rhs);
        }

        return *this;
    }

    // TODO check exception guarantee
    /// Converting move assignment operator.
    ///
    /// Moves the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    template <typename OtherT, detail::enable_assign_from_other<TypeT, OtherT, OtherT>* = nullptr>
    Optional& operator=(Optional<OtherT>&& rhs)
    {
        if (has_value())
        {
            if (rhs.has_value())
            {
                this->m_Value = phi::move(*rhs);
            }
            else
            {
                this->hard_reset();
            }
        }

        if (rhs.has_value())
        {
            this->construct(phi::move(*rhs));
        }

        return *this;
    }

    /// Constructs the value in-place, destroying the current one if there is
    /// one.
    template <typename... ArgsT>
    TypeT& emplace(ArgsT&&... args)
    {
        static_assert(is_constructible<TypeT, ArgsT&&...>::value,
                      "TypeT must be constructible with ArgsT");

        *this = nullopt;
        this->construct(phi::forward<ArgsT>(args)...);
        return value();
    }

    template <typename OtherT, typename... ArgsT>
    enable_if_t<is_constructible<TypeT, std::initializer_list<OtherT>&, ArgsT&&...>::value, TypeT&>
    emplace(std::initializer_list<OtherT> il, ArgsT&&... args)
    {
        *this = nullopt;
        this->construct(il, phi::forward<ArgsT>(args)...);
        return value();
    }

    /// Swaps this Optional with the other.
    ///
    /// If neither optionals have a value, nothing happens.
    /// If both have a value, the values are swapped.
    /// If one has a value, it is moved to the other and the movee is left
    /// valueless.
    void swap(Optional& rhs) noexcept(
            is_nothrow_move_constructible<TypeT>::value&& is_nothrow_swappable<TypeT>::value)
    {
        using std::swap;
        if (has_value())
        {
            if (rhs.has_value())
            {
                swap(**this, *rhs);
            }
            else
            {
                new (phi::addressof(rhs.m_Value)) TypeT(phi::move(this->m_Value));
                this->m_Value.TypeT::~TypeT();
            }
        }
        else if (rhs.has_value())
        {
            new (phi::addressof(this->m_Value)) TypeT(phi::move(rhs.m_Value));
            rhs.m_Value.TypeT::~TypeT();
        }

        swap(this->m_has_value, rhs.m_has_value);
    }

    /// Returns a pointer to the stored value
    constexpr const TypeT* operator->() const
    {
        return phi::addressof(this->m_Value);
    }

    constexpr TypeT* operator->()
    {
        return phi::addressof(this->m_Value);
    }

    /// Returns the stored value
    constexpr TypeT& operator*() &
    {
        return this->m_Value;
    }

    constexpr const TypeT& operator*() const&
    {
        return this->m_Value;
    }

    constexpr TypeT&& operator*() &&
    {
        return phi::move(this->m_Value);
    }

    constexpr const TypeT&& operator*() const&&
    {
        return phi::move(this->m_Value);
    }

    /// Returns whether or not the Optional has a value
    PHI_NODISCARD constexpr bool has_value() const noexcept
    {
        return this->m_has_value;
    }

    constexpr explicit operator bool() const noexcept
    {
        return this->m_has_value;
    }

    /// Returns the contained value if there is one, otherwise throws bad_optional_access
    constexpr TypeT& value() &
    {
        if (has_value())
        {
            return this->m_Value;
        }

        PHI_DBG_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD constexpr const TypeT& value() const&
    {
        if (has_value())
        {
            return this->m_Value;
        }

        PHI_DBG_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD constexpr TypeT&& value() &&
    {
        if (has_value())
        {
            return phi::move(this->m_Value);
        }

        PHI_DBG_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD constexpr const TypeT&& value() const&&
    {
        if (has_value())
        {
            return phi::move(this->m_Value);
        }

        PHI_DBG_ASSERT_NOT_REACHED();
    }

    /// Returns the stored value if there is one, otherwise returns `u`
    template <typename OtherT>
    constexpr TypeT value_or(OtherT&& other) const&
    {
        static_assert(is_copy_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be copy constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(other));
    }

    template <typename OtherT>
    constexpr TypeT value_or(OtherT&& other) &&
    {
        static_assert(is_move_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be move constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(other));
    }

    /// Destroys the stored value if one exists, making the Optional empty
    void reset() noexcept
    {
        if (has_value())
        {
            this->m_Value.~TypeT();
            this->m_has_value = false;
        }
    }

    /// Carries out some operation which returns an Optional on the stored
    /// object if there is one.
    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) &
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) &&
    {
        using result = invoke_result_t<FuncT, TypeT&&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) const&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) const&&
    {
        using result = invoke_result_t<FuncT, const TypeT&&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             result(nullopt);
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    constexpr auto map(FuncT&& f) &
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) &&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) const&
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) const&&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    constexpr auto transform(FuncT&& f) &
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) &&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) const&
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) const&&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    /// Calls `f` if the Optional is empty
    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) &
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) &
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) &&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) &&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) const&
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) const&
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) const&&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) const&&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    /// Maps the stored value with `f` if there is one, otherwise returns `other`.
    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& other) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& other) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& other) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& other) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other);
    }

    /// Maps the stored value with `f` if there is one, otherwise calls
    /// `other` and returns the result.
    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other)();
    }

    /// Returns `other` if `*this` has a value, otherwise an empty Optional.
    template <typename OtherT>
    constexpr Optional<typename decay<OtherT>::type> conjunction(OtherT&& other) const
    {
        using result = Optional<decay_t<OtherT>>;
        return has_value() ? result{other} : result{nullopt};
    }

    /// Returns `rhs` if `*this` is empty, otherwise the current value.
    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) &
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) const&
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) &&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) const&&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) &
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) const&
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) &&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) const&&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

    /// Takes the value out of the Optional, leaving it empty
    Optional take()
    {
        Optional ret = phi::move(*this);
        reset();
        return ret;
    }
};

/// Compares two Optional objects
template <typename TypeT, typename OtherT>
inline constexpr bool operator==(const Optional<TypeT>& lhs, const Optional<OtherT>& rhs)
{
    return lhs.has_value() == rhs.has_value() && (!lhs.has_value() || *lhs == *rhs);
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator!=(const Optional<TypeT>& lhs, const Optional<OtherT>& rhs)
{
    return lhs.has_value() != rhs.has_value() || (lhs.has_value() && *lhs != *rhs);
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator<(const Optional<TypeT>& lhs, const Optional<OtherT>& rhs)
{
    return rhs.has_value() && (!lhs.has_value() || *lhs < *rhs);
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator>(const Optional<TypeT>& lhs, const Optional<OtherT>& rhs)
{
    return lhs.has_value() && (!rhs.has_value() || *lhs > *rhs);
}
template <typename TypeT, typename OtherT>
inline constexpr bool operator<=(const Optional<TypeT>& lhs, const Optional<OtherT>& rhs)
{
    return !lhs.has_value() || (rhs.has_value() && *lhs <= *rhs);
}
template <typename TypeT, typename OtherT>
inline constexpr bool operator>=(const Optional<TypeT>& lhs, const Optional<OtherT>& rhs)
{
    return !rhs.has_value() || (lhs.has_value() && *lhs >= *rhs);
}

/// Compares an Optional to a `nullopt`
template <typename TypeT>
inline constexpr bool operator==(const Optional<TypeT>& lhs, nullopt_t) noexcept
{
    return !lhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator==(nullopt_t, const Optional<TypeT>& rhs) noexcept
{
    return !rhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator!=(const Optional<TypeT>& lhs, nullopt_t) noexcept
{
    return lhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator!=(nullopt_t, const Optional<TypeT>& rhs) noexcept
{
    return rhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator<(const Optional<TypeT>&, nullopt_t) noexcept
{
    return false;
}

template <typename TypeT>
inline constexpr bool operator<(nullopt_t, const Optional<TypeT>& rhs) noexcept
{
    return rhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator<=(const Optional<TypeT>& lhs, nullopt_t) noexcept
{
    return !lhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator<=(nullopt_t, const Optional<TypeT>&) noexcept
{
    return true;
}

template <typename TypeT>
inline constexpr bool operator>(const Optional<TypeT>& lhs, nullopt_t) noexcept
{
    return lhs.has_value();
}

template <typename TypeT>
inline constexpr bool operator>(nullopt_t, const Optional<TypeT>&) noexcept
{
    return false;
}

template <typename TypeT>
inline constexpr bool operator>=(const Optional<TypeT>&, nullopt_t) noexcept
{
    return true;
}

template <typename TypeT>
inline constexpr bool operator>=(nullopt_t, const Optional<TypeT>& rhs) noexcept
{
    return !rhs.has_value();
}

/// Compares the Optional with a value.
template <typename TypeT, typename OtherT>
inline constexpr bool operator==(const Optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs == rhs : false;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator==(const OtherT& lhs, const Optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs == *rhs : false;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator!=(const Optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs != rhs : true;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator!=(const OtherT& lhs, const Optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs != *rhs : true;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator<(const Optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs < rhs : true;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator<(const OtherT& lhs, const Optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs < *rhs : false;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator<=(const Optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs <= rhs : true;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator<=(const OtherT& lhs, const Optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs <= *rhs : false;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator>(const Optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs > rhs : false;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator>(const OtherT& lhs, const Optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs > *rhs : true;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator>=(const Optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs >= rhs : false;
}

template <typename TypeT, typename OtherT>
inline constexpr bool operator>=(const OtherT& lhs, const Optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs >= *rhs : true;
}

template <typename TypeT, enable_if_t<is_move_constructible<TypeT>::value>* = nullptr,
          enable_if_t<is_swappable<TypeT>::value>* = nullptr>
void swap(Optional<TypeT>& lhs, Optional<TypeT>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
    return lhs.swap(rhs);
}

namespace detail
{
    struct i_am_secret
    {};
} // namespace detail

template <typename TypeT = detail::i_am_secret, typename OtherT,
          typename RetT =
                  conditional_t<is_same<TypeT, detail::i_am_secret>::value, decay_t<OtherT>, TypeT>>
inline constexpr Optional<RetT> make_optional(OtherT&& v)
{
    return Optional<RetT>(phi::forward<OtherT>(v));
}

template <typename TypeT, typename... ArgsT>
inline constexpr Optional<TypeT> make_optional(ArgsT&&... args)
{
    return Optional<TypeT>(in_place, phi::forward<ArgsT>(args)...);
}

template <typename TypeT, typename OtherT, typename... ArgsT>
inline constexpr Optional<TypeT> make_optional(std::initializer_list<OtherT> il, ArgsT&&... args)
{
    return Optional<TypeT>(in_place, il, phi::forward<ArgsT>(args)...);
}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
template <typename TypeT>
Optional(TypeT) -> Optional<TypeT>;
#endif

/// \exclude
namespace detail
{
    template <typename OptT, typename FuncT,
              typename RetT = decltype(phi::invoke(phi::declval<FuncT>(), *phi::declval<OptT>())),
              enable_if_t<!is_void<RetT>::value>* = nullptr>
    constexpr auto optional_map_impl(OptT&& opt, FuncT&& func)
    {
        return opt.has_value() ? phi::invoke(phi::forward<FuncT>(func), *phi::forward<OptT>(opt)) :
                                 Optional<RetT>(nullopt);
    }

    template <typename OptT, typename FuncT,
              typename RetT = decltype(phi::invoke(phi::declval<FuncT>(), *phi::declval<OptT>())),
              enable_if_t<is_void<RetT>::value>* = nullptr>
    auto optional_map_impl(OptT&& opt, FuncT&& func)
    {
        if (opt.has_value())
        {
            phi::invoke(phi::forward<FuncT>(func), *phi::forward<OptT>(opt));
            return make_optional(monostate{});
        }

        return Optional<monostate>(nullopt);
    }
} // namespace detail

/// Specialization for when `T` is a reference. `Optional<T&>` acts similarly
/// to a `T*`, but provides more operations and shows intent more clearly.
template <typename TypeT>
class Optional<TypeT&>
{
public:
    using this_type  = Optional<TypeT&>;
    using value_type = TypeT&;

    /// Constructs an Optional that does not contain a value.
    constexpr Optional() noexcept
        : m_Value(nullptr)
    {}

    constexpr Optional(nullopt_t) noexcept
        : m_Value(nullptr)
    {}

    /// Copy constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed Optional is empty.
    constexpr Optional(const Optional& rhs) noexcept = default;

    /// Move constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed Optional is empty.
    constexpr Optional(Optional&& rhs) = default;

    /// Constructs the stored value with `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    constexpr Optional(OtherT&& u) noexcept
        : m_Value(phi::addressof(u))
    {
        static_assert(is_lvalue_reference<OtherT>::value, "OtherT must be an lvalue");
    }

    template <typename OtherT>
    constexpr explicit Optional(const Optional<OtherT>& rhs) noexcept
        : Optional(*rhs)
    {}

    /// No-op
    ~Optional() = default;

    /// Assignment to empty.
    ///
    /// Destroys the current value if there is one.
    Optional& operator=(nullopt_t) noexcept
    {
        m_Value = nullptr;
        return *this;
    }

    /// Copy assignment.
    ///
    /// Rebinds this Optional to the referee of `rhs` if there is one. Otherwise
    /// resets the stored value in `*this`.
    Optional& operator=(const Optional& rhs) = default;

    /// Rebinds this Optional to `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    Optional& operator=(OtherT&& u)
    {
        static_assert(is_lvalue_reference<OtherT>::value, "OtherT must be an lvalue");
        m_Value = phi::addressof(u);
        return *this;
    }

    /// Converting copy assignment operator.
    ///
    /// Rebinds this Optional to the referee of `rhs` if there is one. Otherwise
    /// resets the stored value in `*this`.
    template <typename OtherT>
    Optional& operator=(const Optional<OtherT>& rhs) noexcept
    {
        m_Value = phi::addressof(rhs.value());
        return *this;
    }

    /// Rebinds this Optional to `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    Optional& emplace(OtherT&& u) noexcept
    {
        return *this = phi::forward<OtherT>(u);
    }

    void swap(Optional& rhs) noexcept
    {
        std::swap(m_Value, rhs.m_Value);
    }

    /// Returns a pointer to the stored value
    constexpr const TypeT* operator->() const noexcept
    {
        return m_Value;
    }

    constexpr TypeT* operator->() noexcept
    {
        return m_Value;
    }

    /// Returns the stored value
    constexpr TypeT& operator*() noexcept
    {
        return *m_Value;
    }

    constexpr const TypeT& operator*() const noexcept
    {
        return *m_Value;
    }

    PHI_NODISCARD constexpr bool has_value() const noexcept
    {
        return m_Value != nullptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return m_Value != nullptr;
    }

    /// Returns the contained value if there is one, otherwise throws bad_optional_access
    PHI_NODISCARD constexpr TypeT& value()
    {
        if (has_value())
        {
            return *m_Value;
        }

        PHI_DBG_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD constexpr const TypeT& value() const
    {
        if (has_value())
        {
            return *m_Value;
        }

        PHI_DBG_ASSERT_NOT_REACHED();
    }

    /// Returns the stored value if there is one, otherwise returns `u`
    template <typename OtherT>
    PHI_NODISCARD constexpr TypeT value_or(OtherT&& u) const& noexcept
    {
        static_assert(is_copy_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be copy constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(u));
    }

    /// \group value_or
    template <typename OtherT>
    PHI_NODISCARD constexpr TypeT value_or(OtherT&& u) && noexcept
    {
        static_assert(is_move_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be move constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(u));
    }

    /// Destroys the stored value if one exists, making the Optional empty
    void reset() noexcept
    {
        m_Value = nullptr;
    }

    /// Carries out some operation which returns an Optional on the stored
    /// object if there is one.
    template <typename FuncT>
    constexpr auto and_then(FuncT&& func) &
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(func), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) &&
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) const&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) const&&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an Optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    constexpr auto map(FuncT&& f) &
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) &&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) const&
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) const&&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    constexpr auto transform(FuncT&& f) &
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) &&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) const&
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) const&&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    /// Calls `f` if the Optional is empty
    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) &
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) &
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) &&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) &&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) const&
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> constexpr or_else(FuncT&& f) const&
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) const&&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    Optional<TypeT> or_else(FuncT&& f) const&&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    /// Maps the stored value with `f` if there is one, otherwise returns `u`
    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& u) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : phi::forward<OtherT>(u);
    }

    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& u) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u);
    }

    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& u) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : phi::forward<OtherT>(u);
    }

    template <typename FuncT, typename OtherT>
    OtherT map_or(FuncT&& f, OtherT&& u) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u);
    }

    /// Maps the stored value with `f` if there is one, otherwise calls
    /// `u` and returns the result.
    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(u)();
    }

    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u)();
    }

    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(u)();
    }

    template <typename FuncT, typename OtherT>
    invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u)();
    }

    /// Returns `u` if `*this` has a value, otherwise an empty Optional.
    template <typename OtherT>
    constexpr Optional<typename decay<OtherT>::type> conjunction(OtherT&& u) const
    {
        using result = Optional<decay_t<OtherT>>;
        return has_value() ? result{u} : result{nullopt};
    }

    /// Returns `rhs` if `*this` is empty, otherwise the current value.
    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) &
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) const&
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) &&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(const Optional& rhs) const&&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) &
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) const&
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) &&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

    PHI_NODISCARD constexpr Optional disjunction(Optional&& rhs) const&&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

    /// Takes the value out of the Optional, leaving it empty
    Optional take()
    {
        Optional ret = phi::move(*this);
        reset();
        return ret;
    }

private:
    TypeT* m_Value;
};

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    // TODO SFINAE
    template <typename TypeT>
    struct hash<phi::Optional<TypeT>>
    {
        std::size_t operator()(const phi::Optional<TypeT>& optional) const
        {
            if (!optional.has_value())
            {
                return 0;
            }

            return std::hash<remove_const_t<TypeT>>()(optional.value());
        }
    };
} // namespace std

#endif // INCG_PHI_CORE_OPTIONAL_HPP
