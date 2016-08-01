#pragma once
#include <iterator>
#include <type_traits>

namespace m7 {

/// isIteratorTagV type trait type.
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

/// true if T models the iterator category Tag.
template <typename T, typename Tag>
constexpr auto isIteratorTagV = isIteratorTag<T, Tag>::value;

/// isInputIteratorV type trait type.
template <typename T>
using isInputIterator = isIteratorTag<T, std::input_iterator_tag>;

/// true if T models the input iterator concept.
template <typename T>
static constexpr auto isInputIteratorV = isInputIterator<T>::value;

/// isOutputIteratorV type trait type.
template <typename T>
using isOutputIterator = isIteratorTag<T, std::output_iterator_tag>;

/// true if T models the output iterator concept.
template <typename T>
static constexpr auto isOutputIteratorV = isOutputIterator<T>::value;

/// isForwardIteratorV type trait type.
template <typename T>
using isForwardIterator = isIteratorTag<T, std::forward_iterator_tag>;

/// true if T models the forward iterator concept.
template <typename T>
static constexpr auto isForwardIteratorV = isForwardIterator<T>::value;

/// isBidirectionalIteratorV type trait type.
template <typename T>
using isBidirectionalIterator =
    isIteratorTag<T, std::bidirectional_iterator_tag>;

/// true if T models the bidirectional iterator concept.
template <typename T>
static constexpr auto isBidirectionalIteratorV =
    isBidirectionalIterator<T>::value;

/// isRandomAccessIteratorV type trait type.
template <typename T>
using isRandomAccessIterator =
    isIteratorTag<T, std::random_access_iterator_tag>;

/// true if T models the random access iterator concept.
template <typename T>
static constexpr auto isRandomAccessIteratorV =
    isRandomAccessIterator<T>::value;

namespace detail {
using std::begin;
using std::end;

template <typename C>
auto size(const C& c) -> decltype(c.size()) {
	return c.size();
}

template <typename T, size_t N>
size_t size(T (&)[N]) {
	return N;
}

template <typename C>
auto data(C& c) -> decltype(c.data()) {
	return c.data();
}

template <typename C>
auto data(const C& c) -> decltype(c.data()) {
	return c.data();
}

template <typename T, size_t N>
T* data(T (&a)[N]) {
	return a;
}
template <typename T>
T* data(std::initializer_list<T> il) {
	return &*il.begin();
}

template <typename T>
using BeginType = decltype(begin(std::declval<T&>()));
template <typename T>
using EndType = decltype(end(std::declval<T&>()));
template <typename T>
using SizeType = decltype(size(std::declval<T&>()));
template <typename T>
using DataType = decltype(data(std::declval<T&>()));
}

/// isRangeV type trait type.
template <typename T, typename Tag>
struct isRange {
       private:
	static std::false_type _test(...);
	template <typename U, typename BIter = typename detail::BeginType<U>,
		  typename EIter = typename detail::EndType<U>,
		  typename = std::enable_if_t<isIteratorTag<BIter, Tag>::value>,
		  typename = std::enable_if_t<isIteratorTag<EIter, Tag>::value>>
	static std::true_type _test(U&&);

       public:
	/// true if T models the range concept with iterators in Tag category.
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};

/// true if T models the range concept with iterators in Tag category.
template <typename T, typename Tag>
constexpr auto isRangeV = isRange<T, Tag>::value;

/// isInputRangeV type trait type.
template <typename T>
using isInputRange = isRange<T, std::input_iterator_tag>;

/// true if T models the input range concept.
template <typename T>
static constexpr auto isInputRangeV = isInputRange<T>::value;

/// isOutputRangeV type trait type.
template <typename T>
using isOutputRange = isRange<T, std::output_iterator_tag>;

/// true if T models the output range concept.
template <typename T>
static constexpr auto isOutputRangeV = isOutputRange<T>::value;

/// isForwardRangeV type trait type.
template <typename T>
using isForwardRange = isRange<T, std::forward_iterator_tag>;

/// true if T models the forward range concept.
template <typename T>
static constexpr auto isForwardRangeV = isForwardRange<T>::value;

/// isBidirectionalRangeV type trait type.
template <typename T>
using isBidirectionalRange = isRange<T, std::bidirectional_iterator_tag>;

/// true if T models the bidirectional range concept.
template <typename T>
static constexpr auto isBidirectionalRangeV = isBidirectionalRange<T>::value;

/// isRandomAccessRangeV type trait type.
template <typename T>
using isRandomAccessRange = isRange<T, std::random_access_iterator_tag>;

/// true if T models the random access range concept.
template <typename T>
static constexpr auto isRandomAccessRangeV = isRandomAccessRange<T>::value;

/// isContiguousRange type trait type.
template <typename T>
struct isContiguousRange {
       private:
	static std::false_type _test(...);
	template <
	    typename U, typename SizeType = typename detail::SizeType<U>,
	    typename DataType = typename detail::DataType<U>,
	    typename = std::enable_if_t<std::is_integral<SizeType>::value>,
	    typename = std::enable_if_t<std::is_pointer<DataType>::value>>
	static std::true_type _test(U&&);

       public:
	/// true if T models the contiguous range concept.
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};

/// true if T models the contiguous range concept.
template <typename T>
constexpr auto isContiguousRangeV = isContiguousRange<T>::value;

}  // namespace m7
