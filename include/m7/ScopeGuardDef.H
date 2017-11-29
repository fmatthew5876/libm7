#pragma once
#include <m7/ScopeGuardFwd.H>
#include <utility>
#include <type_traits>

namespace m7 {

/// a move-only object which calls the given functor automatically on
/// destruction.
template <typename F>
    class ScopeGuard {
        public:
            //Constant is true if the fire() method is noexcept.
            static constexpr bool kFireIsNoExcept = noexcept(std::declval<F>()());

            /// Default construct with no functor and disabled state.
            constexpr ScopeGuard() = default;

            /// Construct with given functor f and enabled state.
            constexpr explicit ScopeGuard(F f) noexcept(std::is_nothrow_move_constructible_v<F>);

            /// Non-copyable.
            ScopeGuard(const ScopeGuard&) = delete;
            /// Non-copyable.
            ScopeGuard& operator=(const ScopeGuard&) = delete;

            /// This takes the functor and o is disabled.
            constexpr ScopeGuard(ScopeGuard<F>&& o) noexcept(std::is_nothrow_move_constructible_v<F>);

            /// fire(), and then this takes the functor and o is disabled.
            constexpr ScopeGuard<F>& operator=(ScopeGuard<F>&& o)
                noexcept(kFireIsNoExcept && noexcept(std::is_nothrow_move_constructible_v<F>));

            /// Swap operator.
            constexpr void swap(ScopeGuard<F>& o) noexcept(std::is_nothrow_swappable_v<F>);

            /// calls fire().
            ~ScopeGuard() noexcept(kFireIsNoExcept);

            /// True if will call fire() on destruction.
            constexpr bool active() const noexcept;

            /// Disable the scope guard.
            constexpr void dismiss() noexcept;

            /// If active() == true, call the functor now and set to disabled.
            constexpr void fire() noexcept(kFireIsNoExcept);
        private:
            F _f;
            bool _active = false;
    };

/// Construct a scope guard using f.
template <typename F>
    constexpr ScopeGuard<F> make_scope_guard(F&& f) noexcept(std::is_nothrow_move_constructible_v<F>);


} //namespace m7
