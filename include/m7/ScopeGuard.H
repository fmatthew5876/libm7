#pragma once
#include <m7/ScopeGuardDef.H>
#include <utility>

namespace m7 {

template <typename F>
    constexpr ScopeGuard<F>::ScopeGuard(F f) noexcept(std::is_nothrow_move_constructible_v<F>)
    : _f(std::move(f))
      , _active(true)
{}

template <typename F>
constexpr ScopeGuard<F>::ScopeGuard(ScopeGuard<F>&& o) noexcept(std::is_nothrow_move_constructible_v<F>)
    : _f(std::move(o._f))
, _active(o._active)
{
    o._active = false;
}

template <typename F>
constexpr ScopeGuard<F>& ScopeGuard<F>::operator=(ScopeGuard<F>&& o)
    noexcept(kFireIsNoExcept && noexcept(std::is_nothrow_move_constructible_v<F>))
{
    if (this != &o) {
        fire();
        _f = std::move(o._f);
        using std::swap;
        swap(_active, o._active);
    }
    return *this;
}

template <typename F>
ScopeGuard<F>::~ScopeGuard() noexcept(kFireIsNoExcept) {
    fire();
}

template <typename F>
constexpr void ScopeGuard<F>::swap(ScopeGuard& o) noexcept(std::is_nothrow_swappable_v<F>) {
    using std::swap;
    swap(_f, o._f);
    swap(_active, o._active);
}

template <typename F>
constexpr bool ScopeGuard<F>::active() const noexcept {
    return _active;
}

template <typename F>
constexpr void ScopeGuard<F>::dismiss() noexcept {
    _active = false;
}

template <typename F>
constexpr void ScopeGuard<F>::fire() noexcept(kFireIsNoExcept) {
    if (!active()) {
        return;
    }
    _f();
    dismiss();
}

/// Construct a scope guard using f.
template <typename F>
constexpr ScopeGuard<F> make_scope_guard(F&& f) noexcept(std::is_nothrow_move_constructible_v<F>) {
	return ScopeGuard<std::remove_reference_t<F>>(std::forward<F>(f));
}

}  // namespace m7
