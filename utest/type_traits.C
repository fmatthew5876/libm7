#include <gtest/gtest.h>
#include <forward_list>
#include <list>
#include <m7/type_traits.H>
#include <vector>

using namespace m7;

TEST(TypeTraits, StaticTests) {
	static_assert(isInputRangeV<std::forward_list<int>>, "RangeCheck");
	// static_assert(isOutputRangeV<std::forward_list<int>>, "RangeCheck");
	static_assert(isForwardRangeV<std::forward_list<int>>, "RangeCheck");
	static_assert(!isBidirectionalRangeV<std::forward_list<int>>,
		      "RangeCheck");
	static_assert(!isRandomAccessRangeV<std::forward_list<int>>,
		      "RangeCheck");
	static_assert(!isContiguousRangeV<std::forward_list<int>>,
		      "RangeCheck");

	static_assert(isInputRangeV<std::list<int>>, "RangeCheck");
	// static_assert(isOutputRangeV<std::list<int>>, "RangeCheck");
	static_assert(isForwardRangeV<std::list<int>>, "RangeCheck");
	static_assert(isBidirectionalRangeV<std::list<int>>, "RangeCheck");
	static_assert(!isRandomAccessRangeV<std::list<int>>, "RangeCheck");
	static_assert(!isContiguousRangeV<std::list<int>>, "RangeCheck");

	static_assert(isInputRangeV<std::vector<int>>, "RangeCheck");
	// static_assert(isOutputRangeV<std::vector<int>>, "RangeCheck");
	static_assert(isForwardRangeV<std::vector<int>>, "RangeCheck");
	static_assert(isBidirectionalRangeV<std::vector<int>>, "RangeCheck");
	static_assert(isRandomAccessRangeV<std::vector<int>>, "RangeCheck");
	static_assert(isContiguousRangeV<std::vector<int>>, "RangeCheck");

	static_assert(
	    isInputIteratorV<typename std::forward_list<int>::iterator>,
	    "IteratorCheck");
	/*
	static_assert(
	    isOutputIteratorV<typename std::forward_list<int>::iterator>,
	    "IteratorCheck");
	    */
	static_assert(
	    isForwardIteratorV<typename std::forward_list<int>::iterator>,
	    "IteratorCheck");
	static_assert(!isBidirectionalIteratorV<
			  typename std::forward_list<int>::iterator>,
		      "IteratorCheck");
	static_assert(
	    !isRandomAccessIteratorV<typename std::forward_list<int>::iterator>,
	    "IteratorCheck");

	static_assert(isInputIteratorV<typename std::list<int>::iterator>,
		      "IteratorCheck");
	/*
	static_assert(isOutputIteratorV<typename std::list<int>::iterator>,
		      "IteratorCheck");
		      */
	static_assert(isForwardIteratorV<typename std::list<int>::iterator>,
		      "IteratorCheck");
	static_assert(
	    isBidirectionalIteratorV<typename std::list<int>::iterator>,
	    "IteratorCheck");
	static_assert(
	    !isRandomAccessIteratorV<typename std::list<int>::iterator>,

	    "IteratorCheck");

	static_assert(isInputIteratorV<typename std::vector<int>::iterator>,
		      "IteratorCheck");
	/*
	static_assert(isOutputIteratorV<typename std::vector<int>::iterator>,
		      "IteratorCheck");
		      */
	static_assert(isForwardIteratorV<typename std::vector<int>::iterator>,
		      "IteratorCheck");
	static_assert(
	    isBidirectionalIteratorV<typename std::vector<int>::iterator>,
	    "IteratorCheck");
	static_assert(
	    isRandomAccessIteratorV<typename std::vector<int>::iterator>,
	    "IteratorCheck");
}
