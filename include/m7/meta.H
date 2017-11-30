#pragma once
#include <iterator>
#include <type_traits>

namespace m7::meta {

///true if type From can be converted to type To only by adding CV qualifiers.
template <typename To, typename From>
constexpr auto isCvConvertible =
        std::is_same_v<std::remove_cv_t<To>,std::remove_cv_t<From>>
        && !(!std::is_const_v<To> && std::is_const_v<From>)
        && !(!std::is_volatile_v<To> && std::is_volatile_v<From>);

namespace impl {

template <typename T, typename Tag>
struct isIteratorTag {
       private:
	static std::false_type _test(...);
	template <
	    typename U,
	    typename UTag = typename std::iterator_traits<U>::iterator_category,
	    typename = std::enable_if_t<std::is_base_of<Tag, UTag>::value>>
	static std::true_type _test(U&&);

       public:
	/// true if T models the iterator category Tag.
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};

} //namespace impl

/// true if T models the iterator category Tag.
template <typename T, typename Tag>
constexpr auto isIteratorTag = impl::isIteratorTag<T, Tag>::value;

/// true if T models the input iterator concept.
template <typename T>
constexpr auto isInputIterator = isIteratorTag<T, std::input_iterator_tag>;

/// true if T models the output iterator concept.
template <typename T>
constexpr auto isOutputIterator = isIteratorTag<T, std::output_iterator_tag>;

/// true if T models the forward iterator concept.
template <typename T>
constexpr auto isForwardIterator = isIteratorTag<T, std::forward_iterator_tag>;

/// true if T models the bidirectional iterator concept.
template <typename T>
constexpr auto isBidirectionalIterator = isIteratorTag<T, std::bidirectional_iterator_tag>;

/// true if T models the random access iterator concept.
template <typename T>
constexpr auto isRandomAccessIterator = isIteratorTag<T, std::random_access_iterator_tag>;

namespace impl {
using std::begin;
using std::end;
using std::rbegin;
using std::rend;
using std::size;
using std::data;

template <typename T>
using beginType = decltype(begin(std::declval<T&>()));
template <typename T>
using endType = decltype(end(std::declval<T&>()));
template <typename T>
using rbeginType = decltype(rbegin(std::declval<T&>()));
template <typename T>
using rendType = decltype(rend(std::declval<T&>()));
template <typename T>
using sizeType = decltype(size(std::declval<T&>()));
template <typename T>
using dataType = decltype(data(std::declval<T&>()));

} //namespace impl

/// The type returned by begin().
template <typename T>
using beginType = impl::beginType<T>;

/// The type returned by end().
template <typename T>
using endType = impl::endType<T>;

/// The type returned by rbegin().
template <typename T>
using rbeginType = impl::rbeginType<T>;

/// The type returned by rend().
template <typename T>
using rendType = impl::rendType<T>;

/// The type returned by size().
template <typename T>
using sizeType = impl::sizeType<T>;

/// The type returned by data().
template <typename T>
using dataType = impl::dataType<T>;

namespace impl {

template <typename T, typename Tag>
struct isRange {
       private:
	static std::false_type _test(...);
	template <typename U, typename BIter = beginType<U>,
		  typename EIter = endType<U>,
		  typename = std::enable_if_t<isIteratorTag<BIter, Tag>::value>,
		  typename = std::enable_if_t<isIteratorTag<EIter, Tag>::value>>
	static std::true_type _test(U&&);

       public:
	/// true if T models the range concept with iterators in Tag category.
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};

} //namespace impl

/// true if T models the range concept with iterators in Tag category.
template <typename T, typename Tag>
constexpr auto isRange = impl::isRange<T, Tag>::value;

/// true if T models the input range concept.
template <typename T>
constexpr auto isInputRange = isRange<T, std::input_iterator_tag>;

/// true if T models the output range concept.
template <typename T>
constexpr auto isOutputRange = isRange<T, std::output_iterator_tag>;

/// true if T models the forward range concept.
template <typename T>
constexpr auto isForwardRange = isRange<T, std::forward_iterator_tag>;

/// true if T models the bidirectional range concept.
template <typename T>
constexpr auto isBidirectionalRange = isRange<T, std::bidirectional_iterator_tag>;

/// true if T models the random access range concept.
template <typename T>
constexpr auto isRandomAccessRange = isRange<T, std::random_access_iterator_tag>;

namespace impl {

template <typename T>
struct isContiguousRange {
       private:
	static std::false_type _test(...);
	template <
	    typename U, typename SizeType = sizeType<U>,
	    typename DataType = dataType<U>,
	    typename = std::enable_if_t<std::is_integral<SizeType>::value>,
	    typename = std::enable_if_t<std::is_pointer<DataType>::value>>
	static std::true_type _test(U&&);

       public:
	/// true if T models the contiguous range concept.
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};
} //namespace impl

/// true if T models the contiguous range concept.
template <typename T>
constexpr auto isContiguousRange = impl::isContiguousRange<T>::value;

/// The value type stored in the range.
/// FIXME: This is broken for proxy iterators...
template <typename T>
using rangeValueType = std::remove_reference_t<decltype(*std::declval<beginType<T>>())>;

namespace impl {

template <typename F, typename Ret, typename... Args>
struct isCallable {
       private:
	static std::false_type _test(...);
	template <typename U, typename R = decltype(
				  std::declval<U>()(std::declval<Args>()...)),
		  typename = std::enable_if_t<std::is_same<R, Ret>::value>>
	static std::true_type _test(U&&);

       public:
	/// true if F is callable with Args... and returns Ret.
	static constexpr bool value = decltype(_test(std::declval<F>()))::value;
};
} //namespace impl

/// true if F is callable with Args... and returns Ret.
template <typename F, typename Ret, typename... Args>
constexpr auto isCallable = impl::isCallable<F, Ret, Args...>::value;

namespace impl {

template <template <typename...> class Test, typename T, typename... Types>
struct isAnyOf {
	static constexpr bool value =
	    Test<T>::value || isAnyOf<Test, Types...>::value;
};

template <template <typename...> class Test, typename T>
struct isAnyOf<Test, T> {
	static constexpr bool value = Test<T>::value;
};
} //namespace impl

/// true if Test<T>::value is true for at least one of the given types.
template <template <typename...> class Test, typename T, typename... Types>
constexpr auto isAnyOf = impl::isAnyOf<Test, T, Types...>::value;

namespace impl {

template <template <typename...> class Test, typename T, typename... Types>
struct isAllOf {
	static constexpr bool value =
	    Test<T>::value && isAnyOf<Test, Types...>::value;
};

template <template <typename...> class Test, typename T>
struct isAllOf<Test, T> {
	static constexpr bool value = Test<T>::value;
};
} //namespace impl

/// true if Test<T>::value is true for all of the given types.
template <template <typename...> class Test, typename T, typename... Types>
constexpr auto isAllOf = impl::isAllOf<Test, T, Types...>::value;

}  // namespace m7
