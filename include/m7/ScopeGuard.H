#pragma once
#include <utility>

namespace m7 {

/// a move-only object which calls the given functor automatically on
/// destruction.
template <typename F>
class ScopeGuard {
       public:
	/// Default construct with no functor and disabled state.
	ScopeGuard() = default;

	/// Construct with given functor f and enabled state.
	ScopeGuard(F f) : _f(std::move(f)), _active(true) {}

	/// Non-copyable.
	ScopeGuard(const ScopeGuard&) = delete;
	/// Non-copyable.
	ScopeGuard& operator=(const ScopeGuard&) = delete;

	/// Move operation: o is disabled.
	ScopeGuard(ScopeGuard&& o) noexcept : _f(std::move(o._f)),
					      _active(o._active) {
		o._active = false;
	}

	/// Move operation: o is disabled.
	ScopeGuard& operator=(ScopeGuard&& o) noexcept {
		if (this != &o) {
			ScopeGuard tmp;
			this->swap(o);
			o->swap(tmp);
		}
		return *this;
	}

	/// calls fire().
	~ScopeGuard() { fire(); }

	/// Swap operator.
	void swap(ScopeGuard& o) noexcept {
		using std::swap;
		swap(_f, o._f);
		swap(_active, o._active);
	}

	/// True if will call fire() on destruction.
	bool active() const { return _active; }

	/// Disable the scope guard.
	void dismiss() { _active = false; }

	/// If active() == true, call the functor now and set to disabled.
	void fire() {
		if (active()) {
			_f();
			dismiss();
		}
	}

       private:
	F _f;
	bool _active = false;
};

/// Construct a scope guard using f.
template <typename F>
constexpr auto makeScopeGuard(F&& f) {
	return ScopeGuard<std::remove_reference_t<F>>(std::forward<F>(f));
}

}  // namespace m7
