// This file is heavily inspired by Sy Brands Optional library https://github.com/TartanLlama/Optional
// licensed under CC0 https://github.com/TartanLlama/Optional/blob/master/COPYING
// Original file at https://github.com/TartanLlama/Optional/blob/master/include/tl/Optional.hpp

#ifndef INCG_PHI_CORE_OPTIONAL_HPP
#define INCG_PHI_CORE_OPTIONAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/address_of.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/declval.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/invoke.hpp"
#include "phi/core/move.hpp"
#include "phi/type_traits/conjunction.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/invoke_result.hpp"
#include "phi/type_traits/is_assignable.hpp"
#include "phi/type_traits/is_constructible.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_copy_assignable.hpp"
#include "phi/type_traits/is_copy_constructible.hpp"
#include "phi/type_traits/is_lvalue_reference.hpp"
#include "phi/type_traits/is_move_assignable.hpp"
#include "phi/type_traits/is_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_swappable.hpp"
#include "phi/type_traits/is_scalar.hpp"
#include "phi/type_traits/is_swappable.hpp"
#include "phi/type_traits/is_trivially_copy_assignable.hpp"
#include "phi/type_traits/is_trivially_copy_constructible.hpp"
#include "phi/type_traits/is_trivially_destructible.hpp"
#include "phi/type_traits/is_trivially_move_assignable.hpp"
#include "phi/type_traits/is_trivially_move_constructible.hpp"
#include "phi/type_traits/is_void.hpp"
#include "phi/type_traits/remove_const.hpp"
#include "phi/type_traits/void_t.hpp"
#include <functional>

#if PHI_HAS_WORKING_IS_CONSTRUCTIBLE() && PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE() &&             \
        PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE() &&                                             \
        PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_ASSIGNABLE() &&                                          \
        PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE() &&                                       \
        PHI_HAS_WORKING_IS_TRIVIALLY_COPY_ASSIGNABLE() &&                                          \
        PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE() &&                                       \
        PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE() && PHI_HAS_WORKING_IS_MOVE_CONSTRUCTIBLE() &&   \
        PHI_HAS_WORKING_IS_SCALAR() && PHI_HAS_WORKING_IS_INVOCABLE()

#    define PHI_HAS_WORKING_OPTIONAL() 1

DETAIL_PHI_BEGIN_NAMESPACE()

/// Used to represent an optional with no data; essentially a bool
struct monostate
{};

///  A tag type to tell optional to construct its value in-place
struct in_place_t
{
    explicit in_place_t() = default;
};
/// A tag to tell optional to construct its value in-place
static PHI_CONSTEXPR in_place_t in_place{};

template <typename TypeT>
class optional;

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
    using enable_forward_value = enable_if_t<is_constructible<TypeT, OtherT&&>::value &&
                                             !is_same<decay_t<OtherT>, in_place_t>::value &&
                                             !is_same<optional<TypeT>, decay_t<OtherT>>::value>;

    template <typename TypeT, typename OtherT>
    using enable_assign_forward =
            enable_if_t<!is_same<optional<TypeT>, decay_t<OtherT>>::value &&
                        !conjunction<is_scalar<TypeT>, is_same<TypeT, decay_t<OtherT>>>::value &&
                        is_constructible<TypeT, OtherT>::value &&
                        is_assignable<TypeT&, OtherT>::value>;

    template <typename TypeT, typename Type2T, typename OtherT>
    using enable_from_other =
            enable_if_t<is_constructible<TypeT, OtherT>::value &&
                        !is_constructible<TypeT, optional<Type2T>&>::value &&
                        !is_constructible<TypeT, optional<Type2T>&&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&&>::value &&
                        !is_convertible<optional<Type2T>&, TypeT>::value &&
                        !is_convertible<optional<Type2T>&&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&&, TypeT>::value>;

    template <typename TypeT, typename Type2T, typename OtherT>
    using enable_assign_from_other =
            enable_if_t<is_constructible<TypeT, OtherT>::value &&
                        is_assignable<TypeT&, OtherT>::value &&
                        !is_constructible<TypeT, optional<Type2T>&>::value &&
                        !is_constructible<TypeT, optional<Type2T>&&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&&>::value &&
                        !is_convertible<optional<Type2T>&, TypeT>::value &&
                        !is_convertible<optional<Type2T>&&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&&, TypeT>::value &&
                        !is_assignable<TypeT&, optional<Type2T>&>::value &&
                        !is_assignable<TypeT&, optional<Type2T>&&>::value &&
                        !is_assignable<TypeT&, const optional<Type2T>&>::value &&
                        !is_assignable<TypeT&, const optional<Type2T>&&>::value>;

    // Trait for checking if a type is a phi::optional
    template <typename TypeT>
    struct is_optional_impl : false_type
    {};

    template <typename TypeT>
    struct is_optional_impl<optional<TypeT>> : true_type
    {};

    template <typename TypeT>
    using is_optional = is_optional_impl<decay_t<TypeT>>;

    PHI_MSVC_SUPPRESS_WARNING_PUSH()
    PHI_MSVC_SUPPRESS_WARNING(4583) // 'x': destructor is not implicitly called
    PHI_MSVC_SUPPRESS_WARNING(4582) // 'x': constructor is not implicitly called

    // The storage base manages the actual storage, and correctly propagates
    // trivial destruction from T. This case is for when T is not trivially
    // destructible.
    template <typename TypeT, bool = is_trivially_destructible<TypeT>::value>
    struct optional_storage_base
    {
        PHI_CONSTEXPR optional_storage_base() PHI_NOEXCEPT : m_dummy(), m_has_value(false)
        {}

        template <typename... ArgsT>
        PHI_CONSTEXPR optional_storage_base(in_place_t /*unused*/, ArgsT&&... args)
            : m_value(phi::forward<ArgsT>(args)...)
            , m_has_value(true)
        {}

        ~optional_storage_base()
        {
            if (m_has_value)
            {
                m_value.~TypeT();
                m_has_value = false;
            }
        }

        struct dummy
        {};

        union
        {
            dummy m_dummy;
            TypeT m_value;
        };

        bool m_has_value;
    };

    // This case is for when T is trivially destructible.
    template <typename TypeT>
    struct optional_storage_base<TypeT, true>
    {
        PHI_CONSTEXPR optional_storage_base() PHI_NOEXCEPT
            : m_dummy(),
              m_has_value(false) // NOLINT(cppcoreguidelines-use-default-member-init)
        {}

        template <typename... OtherT>
        PHI_CONSTEXPR optional_storage_base(in_place_t /*unused*/, OtherT&&... other)
            : m_value(phi::forward<OtherT>(other)...)
            , m_has_value(true)
        {}

        // No destructor, so this class is trivially destructible

        struct dummy
        {};

        union
        {
            dummy m_dummy;
            TypeT m_value;
        };

        bool m_has_value = false;
    };

    PHI_MSVC_SUPPRESS_WARNING_POP()

    // This base class provides some handy member functions which can be used in
    // further derived classes
    template <typename TypeT>
    struct optional_operations_base : public optional_storage_base<TypeT>
    {
        using optional_storage_base<TypeT>::optional_storage_base;

        void hard_reset() PHI_NOEXCEPT
        {
            get().~TypeT();
            this->m_has_value = false;
        }

        template <typename... ArgsT>
        void construct(ArgsT&&... args) PHI_NOEXCEPT
        {
            new (address_of(this->m_value)) TypeT(phi::forward<ArgsT>(args)...);
            this->m_has_value = true;
        }

        template <typename OptT>
        void assign(OptT&& rhs)
        {
            if (this->has_value())
            {
                if (rhs.has_value())
                {
                    this->m_value = phi::forward<OptT>(rhs).get();
                }
                else
                {
                    this->m_value.~TypeT();
                    this->m_has_value = false;
                }
            }

            else if (rhs.has_value())
            {
                construct(phi::forward<OptT>(rhs).get());
            }
        }

        PHI_NODISCARD PHI_CONSTEXPR bool has_value() const
        {
            return this->m_has_value;
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& get() &
        {
            return this->m_value;
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& get() const&
        {
            return this->m_value;
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT&& get() &&
        {
            return move(this->m_value);
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT&& get() const&&
        {
            return move(this->m_value);
        }
    };

    // This class manages conditionally having a trivial copy constructor
    // This specialization is for when T is trivially copy constructible
    template <typename TypeT, bool = is_trivially_copy_constructible<TypeT>::value>
    struct optional_copy_base : public optional_operations_base<TypeT>
    {
        using optional_operations_base<TypeT>::optional_operations_base;
    };

    // This specialization is for when T is not trivially copy constructible
    template <typename TypeT>
    struct optional_copy_base<TypeT, false> : public optional_operations_base<TypeT>
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
    struct optional_move_base : public optional_copy_base<TypeT>
    {
        using optional_copy_base<TypeT>::optional_copy_base;
    };

    template <typename TypeT>
    struct optional_move_base<TypeT, false> : public optional_copy_base<TypeT>
    {
        using optional_copy_base<TypeT>::optional_copy_base;

        optional_move_base()                              = default;
        optional_move_base(const optional_move_base& rhs) = default;

        optional_move_base(optional_move_base&& rhs)
                PHI_NOEXCEPT_EXPR(is_nothrow_move_constructible<TypeT>::value)
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
        optional_move_base& operator=(optional_move_base&& rhs)      = default;
    };

    // This class manages conditionally having a trivial copy assignment operator
    template <typename TypeT, bool = is_trivially_copy_assignable<TypeT>::value &&
                                     is_trivially_copy_constructible<TypeT>::value &&
                                     is_trivially_destructible<TypeT>::value>
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
    template <typename TypeT, bool = is_trivially_destructible<TypeT>::value &&
                                     is_trivially_move_constructible<TypeT>::value &&
                                     is_trivially_move_assignable<TypeT>::value>
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

        optional_move_assign_base& operator=(optional_move_assign_base&& rhs)
                PHI_NOEXCEPT_EXPR(is_nothrow_move_constructible<TypeT>::value&&
                                          is_nothrow_move_assignable<TypeT>::value)
        {
            this->assign(move(rhs));
            return *this;
        }
    };

    // optional_delete_ctor_base will conditionally delete copy and move
    // constructors depending on whether T is copy/move constructible
    template <typename TypeT, bool EnableCopy = is_copy_constructible<TypeT>::value,
              bool EnableMove = is_move_constructible<TypeT>::value>
    struct optional_delete_ctor_base
    {
        optional_delete_ctor_base()                                            = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)            = default;
        optional_delete_ctor_base(optional_delete_ctor_base&&)                 = default;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&)      = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, true, false>
    {
        optional_delete_ctor_base()                                            = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)            = default;
        optional_delete_ctor_base(optional_delete_ctor_base&&)                 = delete;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&)      = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, false, true>
    {
        optional_delete_ctor_base()                                            = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)            = delete;
        optional_delete_ctor_base(optional_delete_ctor_base&&)                 = default;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&)      = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, false, false>
    {
        optional_delete_ctor_base()                                            = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)            = delete;
        optional_delete_ctor_base(optional_delete_ctor_base&&)                 = delete;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&) = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&)      = default;
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
        optional_delete_assign_base()                                              = default;
        optional_delete_assign_base(const optional_delete_assign_base&)            = default;
        optional_delete_assign_base(optional_delete_assign_base&&)                 = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = default;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&)      = default;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, true, false>
    {
        optional_delete_assign_base()                                              = default;
        optional_delete_assign_base(const optional_delete_assign_base&)            = default;
        optional_delete_assign_base(optional_delete_assign_base&&)                 = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = default;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&)      = delete;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, false, true>
    {
        optional_delete_assign_base()                                              = default;
        optional_delete_assign_base(const optional_delete_assign_base&)            = default;
        optional_delete_assign_base(optional_delete_assign_base&&)                 = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = delete;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&)      = default;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, false, false>
    {
        optional_delete_assign_base()                                              = default;
        optional_delete_assign_base(const optional_delete_assign_base&)            = default;
        optional_delete_assign_base(optional_delete_assign_base&&)                 = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&) = delete;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&)      = delete;
    };
} // namespace detail

/// A tag type to represent an empty optional
struct nullopt_t
{
    struct do_not_use
    {};

    PHI_CONSTEXPR explicit nullopt_t(do_not_use, do_not_use) PHI_NOEXCEPT
    {}
};

/// Represents an empty optional
static PHI_CONSTEXPR nullopt_t nullopt{nullopt_t::do_not_use{}, nullopt_t::do_not_use{}};

/// An optional object is an object that contains the storage for another
/// object and manages the lifetime of this contained object, if any. The
/// contained object may be initialized after the optional object has been
/// initialized, and may be destroyed before the optional object has been
/// destroyed. The initialization state of the contained object is tracked by
/// the optional object.
template <typename TypeT>
class optional : private detail::optional_move_assign_base<TypeT>,
                 private detail::optional_delete_ctor_base<TypeT>,
                 private detail::optional_delete_assign_base<TypeT>
{
    using base = detail::optional_move_assign_base<TypeT>;

    static_assert(!is_same<TypeT, in_place_t>::value,
                  "instantiation of optional with in_place_t is ill-formed");
    static_assert(!is_same<decay_t<TypeT>, nullopt_t>::value,
                  "instantiation of optional with nullopt_t is ill-formed");

public:
    using this_type  = optional<TypeT>;
    using value_type = TypeT;

    /// Constructs an optional that does not contain a value.
    optional() = default;

    PHI_CONSTEXPR optional(nullopt_t) PHI_NOEXCEPT
    {}

    /// Copy constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    PHI_CONSTEXPR optional(const optional& rhs) = default;

    /// Move constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    PHI_CONSTEXPR optional(optional&& rhs) = default;

    /// Constructs the stored value in-place using the given arguments.
    template <typename... ArgsT>
    PHI_CONSTEXPR explicit optional(
            enable_if_t<is_constructible<TypeT, ArgsT...>::value, in_place_t>, ArgsT&&... args)
        : base(in_place, forward<ArgsT>(args)...)
    {}

    template <typename OtherT, typename... ArgsT>
    PHI_EXTENDED_CONSTEXPR explicit optional(
            enable_if_t<is_constructible<TypeT, std::initializer_list<OtherT>&, ArgsT&&...>::value,
                        in_place_t>,
            std::initializer_list<OtherT> il, ArgsT&&... args)
    {
        this->construct(il, forward<ArgsT>(args)...);
    }

    /// Constructs the stored value with `u`.
    template <typename OtherT                                      = TypeT,
              enable_if_t<is_convertible<OtherT&&, TypeT>::value>* = nullptr,
              detail::enable_forward_value<TypeT, OtherT>*         = nullptr>
    PHI_CONSTEXPR optional(OtherT&& other)
        : base(in_place, phi::forward<OtherT>(other))
    {}

    template <typename OtherT                                       = TypeT,
              enable_if_t<!is_convertible<OtherT&&, TypeT>::value>* = nullptr,
              detail::enable_forward_value<TypeT, OtherT>*          = nullptr>
    PHI_CONSTEXPR explicit optional(OtherT&& other)
        : base(in_place, forward<OtherT>(other))
    {}

    /// Converting copy constructor.
    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, const OtherT&>* = nullptr,
              enable_if_t<is_convertible<const OtherT&, TypeT>::value>* = nullptr>
    optional(const optional<OtherT>& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(*rhs);
        }
    }

    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, const OtherT&>* = nullptr,
              enable_if_t<!is_convertible<const OtherT&, TypeT>::value>* = nullptr>
    explicit optional(const optional<OtherT>& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(*rhs);
        }
    }

    /// Converting move constructor.
    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, OtherT&&>* = nullptr,
              enable_if_t<is_convertible<OtherT&&, TypeT>::value>* = nullptr>
    optional(optional<OtherT>&& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(move(*rhs));
        }
    }

    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, OtherT&&>* = nullptr,
              enable_if_t<!is_convertible<OtherT&&, TypeT>::value>* = nullptr>
    explicit optional(optional<OtherT>&& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(move(*rhs));
        }
    }

    /// Destroys the stored value if there is one.
    ~optional() = default;

    /// Assignment to empty.
    ///
    /// Destroys the current value if there is one.
    optional& operator=(nullopt_t) PHI_NOEXCEPT
    {
        if (has_value())
        {
            this->m_value.~TypeT();
            this->m_has_value = false;
        }

        return *this;
    }

    /// Copy assignment.
    ///
    /// Copies the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    optional& operator=(const optional& rhs) = default;

    /// Move assignment.
    ///
    /// Moves the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    optional& operator=(optional&& rhs) = default;

    /// Assigns the stored value from `u`, destroying the old value if there was
    /// one.
    template <typename OtherT = TypeT, detail::enable_assign_forward<TypeT, OtherT>* = nullptr>
    optional& operator=(OtherT&& other)
    {
        if (has_value())
        {
            this->m_value = forward<OtherT>(other);
        }
        else
        {
            this->construct(forward<OtherT>(other));
        }

        return *this;
    }

    /// Converting copy assignment operator.
    ///
    /// Copies the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    template <typename OtherT,
              detail::enable_assign_from_other<TypeT, OtherT, const OtherT&>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& operator=(const optional<OtherT>& rhs)
    {
        if (has_value())
        {
            if (rhs.has_value())
            {
                this->m_value = *rhs;
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
    PHI_EXTENDED_CONSTEXPR optional& operator=(optional<OtherT>&& rhs)
    {
        if (has_value())
        {
            if (rhs.has_value())
            {
                this->m_value = move(*rhs);
            }
            else
            {
                this->hard_reset();
            }
        }

        if (rhs.has_value())
        {
            this->construct(move(*rhs));
        }

        return *this;
    }

    /// Constructs the value in-place, destroying the current one if there is
    /// one.
    template <typename... ArgsT>
    PHI_EXTENDED_CONSTEXPR TypeT& emplace(ArgsT&&... args)
    {
        static_assert(is_constructible<TypeT, ArgsT&&...>::value,
                      "TypeT must be constructible with ArgsT");

        *this = nullopt;
        this->construct(phi::forward<ArgsT>(args)...);
        return value();
    }

    template <typename OtherT, typename... ArgsT>
    enable_if_t<is_constructible<TypeT, std::initializer_list<OtherT>&, ArgsT&&...>::value, TypeT&>
            PHI_EXTENDED_CONSTEXPR emplace(std::initializer_list<OtherT> init_list, ArgsT&&... args)
    {
        *this = nullopt;
        this->construct(init_list, phi::forward<ArgsT>(args)...);
        return value();
    }

    /// Swaps this optional with the other.
    ///
    /// If neither optionals have a value, nothing happens.
    /// If both have a value, the values are swapped.
    /// If one has a value, it is moved to the other and the movee is left
    /// valueless.
    PHI_EXTENDED_CONSTEXPR void swap(optional& rhs) PHI_NOEXCEPT_EXPR(
            is_nothrow_move_constructible<TypeT>::value&& is_nothrow_swappable<TypeT>::value)
    {
        using phi::swap;
        if (has_value())
        {
            if (rhs.has_value())
            {
                swap(**this, *rhs);
            }
            else
            {
                new (address_of(rhs.m_value)) TypeT(move(this->m_value));
                this->m_value.TypeT::~TypeT();
            }
        }
        else if (rhs.has_value())
        {
            new (address_of(this->m_value)) TypeT(move(rhs.m_value));
            rhs.m_value.TypeT::~TypeT();
        }

        swap(this->m_has_value, rhs.m_has_value);
    }

    /// Returns a pointer to the stored value
    PHI_EXTENDED_CONSTEXPR TypeT* operator->()
    {
        return address_of(this->m_value);
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const
    {
        return address_of(this->m_value);
    }

    /// Returns the stored value
    PHI_EXTENDED_CONSTEXPR TypeT& operator*() &
    {
        return this->m_value;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const&
    {
        return this->m_value;
    }

    PHI_EXTENDED_CONSTEXPR TypeT&& operator*() &&
    {
        return phi::move(this->m_value);
    }

    PHI_EXTENDED_CONSTEXPR const TypeT&& operator*() const&&
    {
        return phi::move(this->m_value);
    }

    /// Returns whether or not the optional has a value
    PHI_NODISCARD PHI_CONSTEXPR bool has_value() const PHI_NOEXCEPT
    {
        return this->m_has_value;
    }

    PHI_CONSTEXPR explicit operator bool() const PHI_NOEXCEPT
    {
        return this->m_has_value;
    }

    PHI_GCC_SUPPRESS_WARNING_PUSH()
    PHI_GCC_SUPPRESS_WARNING("-Wreturn-type")
    PHI_MSVC_SUPPRESS_WARNING_PUSH()
    PHI_MSVC_SUPPRESS_WARNING(4702) // unreachable code

    /// Returns the contained value if there is one
    PHI_EXTENDED_CONSTEXPR TypeT& value() &
    {
        if (has_value())
        {
            return this->m_value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& value() const&
    {
        if (has_value())
        {
            return this->m_value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT&& value() &&
    {
        if (has_value())
        {
            return move(this->m_value);
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT&& value() const&&
    {
        if (has_value())
        {
            return move(this->m_value);
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_MSVC_SUPPRESS_WARNING_POP()
    PHI_GCC_SUPPRESS_WARNING_POP()

    /// Returns the stored value if there is one, otherwise returns `u`
    template <typename OtherT>
    PHI_CONSTEXPR TypeT value_or(OtherT&& other) const&
    {
        static_assert(is_copy_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be copy constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(forward<OtherT>(other));
    }

    template <typename OtherT>
    PHI_CONSTEXPR TypeT value_or(OtherT&& other) &&
    {
        static_assert(is_move_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be move constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(forward<OtherT>(other));
    }

    /// Destroys the stored value if one exists, making the optional empty
    PHI_EXTENDED_CONSTEXPR void reset() PHI_NOEXCEPT
    {
        if (has_value())
        {
            this->m_value.~TypeT();
            this->m_has_value = false;
        }
    }

/// Carries out some operation which returns an optional on the stored
/// object if there is one.
#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& function) &
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& function) &&
    {
        using result = invoke_result_t<FuncT, TypeT&&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), move(**this)) : result(nullopt);
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& function) const&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& function) const&&
    {
        using result = invoke_result_t<FuncT, const TypeT&&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), move(**this)) : result(nullopt);
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& function) &
    {
        return optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& function) &&
    {
        return optional_map_impl(move(*this), forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& function) const&
    {
        return optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& function) const&&
    {
        return optional_map_impl(move(*this), forward<FuncT>(function));
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& function) &
    {
        return optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& function) &&
    {
        return optional_map_impl(move(*this), forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& function) const&
    {
        return optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& function) const&&
    {
        return optional_map_impl(move(*this), forward<FuncT>(function));
    }
#    endif

    /// Calls `f` if the optional is empty
    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &
    {
        if (has_value())
        {
            return *this;
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &
    {
        return has_value() ? *this : forward<FuncT>(function)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &&
    {
        if (has_value())
        {
            return move(*this);
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &&
    {
        return has_value() ? move(*this) : forward<FuncT>(function)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&
    {
        if (has_value())
        {
            return *this;
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&
    {
        return has_value() ? *this : forward<FuncT>(function)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&&
    {
        if (has_value())
        {
            return move(*this);
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&&
    {
        return has_value() ? move(*this) : forward<FuncT>(function)();
    }

    /// Maps the stored value with `f` if there is one, otherwise returns `other`.
    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& other) &
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) : forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& other) &&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& other) const&
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) : forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& other) const&&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(other);
    }

    /// Maps the stored value with `f` if there is one, otherwise calls
    /// `other` and returns the result.
    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& function, OtherT&& other) &
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) : forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& function, OtherT&& other) &&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&&  function,
                                                               OtherT&& other) const&
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) : forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&&  function,
                                                               OtherT&& other) const&&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(other)();
    }

    /// Returns `other` if `*this` has a value, otherwise an empty optional.
    template <typename OtherT>
    PHI_EXTENDED_CONSTEXPR optional<typename decay<OtherT>::type> conjunction(OtherT&& other) const
    {
        using result = optional<decay_t<OtherT>>;
        return has_value() ? result{other} : result{nullopt};
    }

    /// Returns `rhs` if `*this` is empty, otherwise the current value.
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(const optional& rhs) const
    {
        return has_value() ? move(*this) : rhs;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(optional&& rhs) const
    {
        return has_value() ? move(*this) : move(rhs);
    }

    /// Takes the value out of the optional, leaving it empty
    optional take()
    {
        optional ret = move(*this);
        reset();
        return ret;
    }
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

/// Compares two optional objects
template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator==(const optional<TypeT>& lhs, const optional<OtherT>& rhs)
{
    return lhs.has_value() == rhs.has_value() && (!lhs.has_value() || *lhs == *rhs);
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator!=(const optional<TypeT>& lhs, const optional<OtherT>& rhs)
{
    return lhs.has_value() != rhs.has_value() || (lhs.has_value() && *lhs != *rhs);
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator<(const optional<TypeT>& lhs, const optional<OtherT>& rhs)
{
    return rhs.has_value() && (!lhs.has_value() || *lhs < *rhs);
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator>(const optional<TypeT>& lhs, const optional<OtherT>& rhs)
{
    return lhs.has_value() && (!rhs.has_value() || *lhs > *rhs);
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator<=(const optional<TypeT>& lhs, const optional<OtherT>& rhs)
{
    return !lhs.has_value() || (rhs.has_value() && *lhs <= *rhs);
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator>=(const optional<TypeT>& lhs, const optional<OtherT>& rhs)
{
    return !rhs.has_value() || (lhs.has_value() && *lhs >= *rhs);
}

/// Compares an optional to a `nullopt`
template <typename TypeT>
PHI_CONSTEXPR boolean operator==(const optional<TypeT>& lhs, nullopt_t /*unused*/) PHI_NOEXCEPT
{
    return !lhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator==(nullopt_t /*unused*/, const optional<TypeT>& rhs) PHI_NOEXCEPT
{
    return !rhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator!=(const optional<TypeT>& lhs, nullopt_t /*unused*/) PHI_NOEXCEPT
{
    return lhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator!=(nullopt_t /*unused*/, const optional<TypeT>& rhs) PHI_NOEXCEPT
{
    return rhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator<(const optional<TypeT>& /*unused*/,
                                nullopt_t /*unused*/) PHI_NOEXCEPT
{
    return false;
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator<(nullopt_t /*unused*/, const optional<TypeT>& rhs) PHI_NOEXCEPT
{
    return rhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator<=(const optional<TypeT>& lhs, nullopt_t /*unused*/) PHI_NOEXCEPT
{
    return !lhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator<=(nullopt_t /*unused*/,
                                 const optional<TypeT>& /*unused*/) PHI_NOEXCEPT
{
    return true;
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator>(const optional<TypeT>& lhs, nullopt_t /*unused*/) PHI_NOEXCEPT
{
    return lhs.has_value();
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator>(nullopt_t /*unused*/,
                                const optional<TypeT>& /*unused*/) PHI_NOEXCEPT
{
    return false;
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator>=(const optional<TypeT>& /*unused*/,
                                 nullopt_t /*unused*/) PHI_NOEXCEPT
{
    return true;
}

template <typename TypeT>
PHI_CONSTEXPR boolean operator>=(nullopt_t /*unused*/, const optional<TypeT>& rhs) PHI_NOEXCEPT
{
    return !rhs.has_value();
}

/// Compares the optional with a value.
template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator==(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs == rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator==(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs == *rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator!=(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs != rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator!=(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs != *rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator<(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs < rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator<(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs < *rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator<=(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs <= rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator<=(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs <= *rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator>(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs > rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator>(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs > *rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator>=(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs >= rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_CONSTEXPR boolean operator>=(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs >= *rhs : true;
}

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT, enable_if_t<is_move_constructible<TypeT>::value>* = nullptr,
          enable_if_t<is_swappable<TypeT>::value>* = nullptr>
void swap(optional<TypeT>& lhs, optional<TypeT>& rhs) PHI_NOEXCEPT_EXPR(noexcept(lhs.swap(rhs)))
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
inline PHI_CONSTEXPR optional<RetT> make_optional(OtherT&& value)
{
    return optional<RetT>(forward<OtherT>(value));
}

template <typename TypeT, typename... ArgsT>
inline PHI_CONSTEXPR optional<TypeT> make_optional(ArgsT&&... args)
{
    return optional<TypeT>(in_place, forward<ArgsT>(args)...);
}

template <typename TypeT, typename OtherT, typename... ArgsT>
inline PHI_CONSTEXPR optional<TypeT> make_optional(std::initializer_list<OtherT> init_list,
                                                   ArgsT&&... args)
{
    return optional<TypeT>(in_place, init_list, forward<ArgsT>(args)...);
}

#    if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
optional(TypeT) -> optional<TypeT>;
#    endif

/// \exclude
namespace detail
{
#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    template <typename OptT, typename FuncT,
              typename RetT = decltype(invoke(declval<FuncT>(), *declval<OptT>())),
              enable_if_t<!is_void<RetT>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR auto optional_map_impl(OptT&& opt, FuncT&& func)
    {
        return opt.has_value() ? invoke(forward<FuncT>(func), *forward<OptT>(opt)) :
                                 optional<RetT>(nullopt);
    }

    template <typename OptT, typename FuncT,
              typename RetT = decltype(invoke(declval<FuncT>(), *declval<OptT>())),
              enable_if_t<is_void<RetT>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR auto optional_map_impl(OptT&& opt, FuncT&& func)
    {
        if (opt.has_value())
        {
            invoke(forward<FuncT>(func), *forward<OptT>(opt));
            return make_optional(monostate{});
        }

        return optional<monostate>(nullopt);
    }
#    endif
} // namespace detail

/// Specialization for when `T` is a reference. `optional<T&>` acts similarly
/// to a `T*`, but provides more operations and shows intent more clearly.
template <typename TypeT>
class optional<TypeT&>
{
public:
    using this_type  = optional<TypeT&>;
    using value_type = TypeT&;

    /// Constructs an optional that does not contain a value.
    PHI_CONSTEXPR optional() PHI_NOEXCEPT : m_value(nullptr)
    {}

    PHI_CONSTEXPR optional(nullopt_t /*unused*/) PHI_NOEXCEPT : m_value(nullptr)
    {}

    /// Copy constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    optional(const optional& rhs) = default;

    /// Move constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    PHI_CONSTEXPR optional(optional&& rhs) = default;

    /// Constructs the stored value with `other`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    PHI_CONSTEXPR optional(OtherT&& other) PHI_NOEXCEPT : m_value(address_of(other))
    {
        static_assert(is_lvalue_reference<OtherT>::value, "OtherT must be an lvalue");
    }

    template <typename OtherT>
    PHI_CONSTEXPR explicit optional(const optional<OtherT>& rhs) PHI_NOEXCEPT : optional(*rhs)
    {}

    /// No-op
    ~optional() = default;

    /// Assignment to empty.
    ///
    /// Destroys the current value if there is one.
    PHI_EXTENDED_CONSTEXPR optional& operator=(nullopt_t /*unused*/) PHI_NOEXCEPT
    {
        m_value = nullptr;
        return *this;
    }

    /// Copy assignment.
    ///
    /// Rebinds this optional to the referee of `rhs` if there is one. Otherwise
    /// resets the stored value in `*this`.
    optional& operator=(const optional& rhs) = default;

    /// Rebinds this optional to `other`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& operator=(OtherT&& other)
    {
        static_assert(is_lvalue_reference<OtherT>::value, "OtherT must be an lvalue");
        m_value = address_of(other);
        return *this;
    }

    /// Converting copy assignment operator.
    ///
    /// Rebinds this optional to the referee of `rhs` if there is one. Otherwise
    /// resets the stored value in `*this`.
    template <typename OtherT>
    PHI_EXTENDED_CONSTEXPR optional& operator=(const optional<OtherT>& rhs) PHI_NOEXCEPT
    {
        m_value = address_of(rhs.value());
        return *this;
    }

    /// Rebinds this optional to `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& emplace(OtherT&& u) PHI_NOEXCEPT
    {
        return *this = forward<OtherT>(u);
    }

    PHI_EXTENDED_CONSTEXPR void swap(optional& rhs) PHI_NOEXCEPT
    {
        swap(m_value, rhs.m_value);
    }

    /// Returns a pointer to the stored value
    PHI_EXTENDED_CONSTEXPR TypeT* operator->() PHI_NOEXCEPT
    {
        return m_value;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const PHI_NOEXCEPT
    {
        return m_value;
    }

    /// Returns the stored value
    PHI_EXTENDED_CONSTEXPR TypeT& operator*() PHI_NOEXCEPT
    {
        return *m_value;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const PHI_NOEXCEPT
    {
        return *m_value;
    }

    PHI_NODISCARD PHI_CONSTEXPR bool has_value() const PHI_NOEXCEPT
    {
        return m_value != nullptr;
    }

    PHI_CONSTEXPR explicit operator bool() const PHI_NOEXCEPT
    {
        return m_value != nullptr;
    }

    PHI_MSVC_SUPPRESS_WARNING_PUSH()
    PHI_MSVC_SUPPRESS_WARNING(4702) // unreachable code

    /// Returns the contained value if there is one, otherwise throws bad_optional_access
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& value()
    {
        if (has_value())
        {
            return *m_value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& value() const
    {
        if (has_value())
        {
            return *m_value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_MSVC_SUPPRESS_WARNING_POP()

    /// Returns the stored value if there is one, otherwise returns `alternative`
    template <typename OtherT>
    PHI_NODISCARD PHI_CONSTEXPR TypeT value_or(OtherT&& alternative) const& PHI_NOEXCEPT
    {
        static_assert(is_copy_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be copy constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(forward<OtherT>(alternative));
    }

    /// \group value_or
    template <typename OtherT>
            PHI_NODISCARD PHI_CONSTEXPR TypeT value_or(OtherT&& alternative) && PHI_NOEXCEPT
    {
        static_assert(is_move_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be move constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(forward<OtherT>(alternative));
    }

    /// Destroys the stored value if one exists, making the optional empty
    PHI_EXTENDED_CONSTEXPR void reset() PHI_NOEXCEPT
    {
        m_value = nullptr;
    }

#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    /// Carries out some operation which returns an optional on the stored
    /// object if there is one.
    template <typename FuncT>
    PHI_CONSTEXPR auto and_then(FuncT&& function) &
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto and_then(FuncT&& function) &&
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto and_then(FuncT&& function) const&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto and_then(FuncT&& function) const&&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? invoke(forward<FuncT>(function), **this) : result(nullopt);
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    PHI_CONSTEXPR auto map(FuncT&& function) &
    {
        return detail::optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto map(FuncT&& function) &&
    {
        return detail::optional_map_impl(move(*this), forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto map(FuncT&& function) const&
    {
        return detail::optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto map(FuncT&& function) const&&
    {
        return detail::optional_map_impl(move(*this), forward<FuncT>(function));
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    PHI_CONSTEXPR auto transform(FuncT&& function) &
    {
        return detail::optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto transform(FuncT&& function) &&
    {
        return detail::optional_map_impl(move(*this), forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto transform(FuncT&& function) const&
    {
        return detail::optional_map_impl(*this, forward<FuncT>(function));
    }

    template <typename FuncT>
    PHI_CONSTEXPR auto transform(FuncT&& function) const&&
    {
        return detail::optional_map_impl(move(*this), forward<FuncT>(function));
    }
#    endif

    /// Calls `function` if the optional is empty
    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &
    {
        if (has_value())
        {
            return *this;
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &
    {
        return has_value() ? *this : forward<FuncT>(function)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &&
    {
        if (has_value())
        {
            return move(*this);
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_CONSTEXPR optional<TypeT> or_else(FuncT&& function) &&
    {
        return has_value() ? move(*this) : forward<FuncT>(function)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&
    {
        if (has_value())
        {
            return *this;
        }

        forward<FuncT>(function)();
        return nullopt;
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&
    {
        return has_value() ? *this : forward<FuncT>(function)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&&
    {
        if (has_value())
        {
            return move(*this);
        }

        forward<FuncT>(function)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_CONSTEXPR optional<TypeT> or_else(FuncT&& function) const&&
    {
        return has_value() ? move(*this) : forward<FuncT>(function)();
    }
#    endif

    /// Maps the stored value with `function` if there is one, otherwise returns `alternative`
    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& alternative) &
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) :
                             forward<OtherT>(alternative);
    }

    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& alternative) &&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(alternative);
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& alternative) const&
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) :
                             forward<OtherT>(alternative);
    }

    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR OtherT map_or(FuncT&& function, OtherT&& alternative) const&&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(alternative);
    }
#    endif

    /// Maps the stored value with `function` if there is one, otherwise calls
    /// `other` and returns the result.
    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& function, OtherT&& other) &
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) : forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& function, OtherT&& other) &&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(other)();
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& function, OtherT&& other) const&
    {
        return has_value() ? invoke(forward<FuncT>(function), **this) : forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& function, OtherT&& other) const&&
    {
        return has_value() ? invoke(forward<FuncT>(function), move(**this)) :
                             forward<OtherT>(other)();
    }
#    endif

    /// Returns `other` if `*this` has a value, otherwise an empty optional.
    template <typename OtherT>
    PHI_CONSTEXPR optional<typename decay<OtherT>::type> conjunction(OtherT&& other) const
    {
        using result = optional<decay_t<OtherT>>;
        return has_value() ? result{other} : result{nullopt};
    }

    /// Returns `rhs` if `*this` is empty, otherwise the current value.
    PHI_NODISCARD PHI_CONSTEXPR optional disjunction(const optional& rhs) const
    {
        return has_value() ? move(*this) : rhs;
    }

    PHI_NODISCARD PHI_CONSTEXPR optional disjunction(optional&& rhs) const
    {
        return has_value() ? move(*this) : move(rhs);
    }

    /// Takes the value out of the optional, leaving it empty
    PHI_EXTENDED_CONSTEXPR optional take()
    {
        optional ret = move(*this);
        reset();
        return ret;
    }

private:
    TypeT* m_value;
};

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_OPTIONAL() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class optional
{
    static_assert(false_t<TypeT>::value, "phi::optional: Requires compiler support");
};

#endif

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

// TODO SFINAE
template <typename TypeT>
struct hash<phi::optional<TypeT>>
{
    size_t operator()(const phi::optional<TypeT>& optional) const
    {
        if (!optional.has_value())
        {
            return 0;
        }

        return std::hash<phi::remove_const_t<TypeT>>()(optional.value());
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_OPTIONAL_HPP
