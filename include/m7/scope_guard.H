#pragma once
#include <utility>

namespace m7 {

template <typename F>
class ScopeGuard {
       public:
	ScopeGuard() = default;
	ScopeGuard(F f) : _f(std::move(f)), _active(true) {}

	ScopeGuard(const ScopeGuard&) = delete;
	ScopeGuard& operator=(const ScopeGuard&) = delete;

	ScopeGuard(ScopeGuard&& o) noexcept : _f(std::move(o._f)),
					      _active(o._active) {
		o._active = false;
	}
	ScopeGuard& operator=(ScopeGuard&& o) noexcept {
		if (this != &o) {
			ScopeGuard tmp;
			this->swap(o);
			o->swap(tmp);
		}
		return *this;
	}

	~ScopeGuard() { fire(); }

	void swap(ScopeGuard& o) noexcept {
		using std::swap;
		swap(_f, o._f);
		swap(_active, o._active);
	}

	bool active() const { return _active; }
	void dismiss() { _active = false; }
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

template <typename F>
constexpr auto makeScopeGuard(F&& f) {
	return ScopeGuard<std::remove_reference_t<F>>(std::forward<F>(f));
}

}  // namespace m7
