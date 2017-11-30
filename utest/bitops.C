#include <gtest/gtest.h>
#include <m7/bitops.H>

using namespace m7;

#include <cstdint>

typedef ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t> IntTypes;
#if 0
typedef ::testing::Types<
  std::pair<int8_t, int8_t>,
  std::pair<int8_t, uint8_t>,
  std::pair<int8_t, int16_t>,
  std::pair<int8_t, uint16_t>,
  std::pair<int8_t, int32_t>,
  std::pair<int8_t, uint32_t>,
  std::pair<int8_t, int32_t>,
  std::pair<int8_t, uint32_t>,

  std::pair<uint8_t, int8_t>,
  std::pair<uint8_t, uint8_t>,
  std::pair<uint8_t, int16_t>,
  std::pair<uint8_t, uint16_t>,
  std::pair<uint8_t, int32_t>,
  std::pair<uint8_t, uint32_t>,
  std::pair<uint8_t, int32_t>,
  std::pair<uint8_t, uint32_t>,

  std::pair<int16_t, int8_t>,
  std::pair<int16_t, uint8_t>,
  std::pair<int16_t, int16_t>,
  std::pair<int16_t, uint16_t>,
  std::pair<int16_t, int32_t>,
  std::pair<int16_t, uint32_t>,
  std::pair<int16_t, int32_t>,
  std::pair<int16_t, uint32_t>,

  std::pair<uint16_t, int8_t>,
  std::pair<uint16_t, uint8_t>,
  std::pair<uint16_t, int16_t>,
  std::pair<uint16_t, uint16_t>,
  std::pair<uint16_t, int32_t>,
  std::pair<uint16_t, uint32_t>,
  std::pair<uint16_t, int32_t>,
  std::pair<uint16_t, uint32_t>,

  std::pair<int32_t, int8_t>,
  std::pair<int32_t, uint8_t>,
  std::pair<int32_t, int16_t>,
  std::pair<int32_t, uint16_t>,
  std::pair<int32_t, int32_t>,
  std::pair<int32_t, uint32_t>,
  std::pair<int32_t, int32_t>,
  std::pair<int32_t, uint32_t>,

  std::pair<uint32_t, int8_t>,
  std::pair<uint32_t, uint8_t>,
  std::pair<uint32_t, int16_t>,
  std::pair<uint32_t, uint16_t>,
  std::pair<uint32_t, int32_t>,
  std::pair<uint32_t, uint32_t>,
  std::pair<uint32_t, int32_t>,
  std::pair<uint32_t, uint32_t>,

  std::pair<int64_t, int8_t>,
  std::pair<int64_t, uint8_t>,
  std::pair<int64_t, int16_t>,
  std::pair<int64_t, uint16_t>,
  std::pair<int64_t, int32_t>,
  std::pair<int64_t, uint32_t>,
  std::pair<int64_t, int32_t>,
  std::pair<int64_t, uint32_t>,

  std::pair<uint64_t, int8_t>,
  std::pair<uint64_t, uint8_t>,
  std::pair<uint64_t, int16_t>,
  std::pair<uint64_t, uint16_t>,
  std::pair<uint64_t, int32_t>,
  std::pair<uint64_t, uint32_t>,
  std::pair<uint64_t, int32_t>,
  std::pair<uint64_t, uint32_t>
  > IntPairTypes;
#endif

template <typename T>
class ShiftTest : public ::testing::Test {
};

TYPED_TEST_CASE(ShiftTest, IntTypes);

TYPED_TEST(ShiftTest, Shll) {
    using T = TypeParam;
    ASSERT_EQ(T(0), shll(T(0), 1));

    for(int i = 1; i < 128; ++i) {
        ASSERT_EQ(T(i * 2), shll(T(i), 1));
    }
};

TYPED_TEST(ShiftTest, Shlr) {
    using T = TypeParam;
    ASSERT_EQ(T(0), shlr(T(0), 1));

    for(int i = 2; i < 128; ++i) {
        ASSERT_EQ(T(i / 2), shlr(T(i), 1));
    }
};

TEST(RevBytesTest, Rev8) {
  ASSERT_EQ(uint8_t(0xAA), reverse_bytes(uint8_t(0xAA)));
  ASSERT_EQ(uint8_t(0xAA), reverse_bytes(uint8_t(0xAA), 1, 1));
}

TEST(RevBytesTest, Rev16) {
  ASSERT_EQ(uint16_t(0xAABB), reverse_bytes(uint16_t(0xBBAA)));
  ASSERT_EQ(uint16_t(0xBBAA), reverse_bytes(uint16_t(0xBBAA), 1, 1));
  ASSERT_EQ(uint16_t(0xAABB), reverse_bytes(uint16_t(0xBBAA), 1, 2));
  ASSERT_EQ(uint16_t(0xBBAA), reverse_bytes(uint16_t(0xBBAA), 2));
  ASSERT_EQ(uint16_t(0xBBAA), reverse_bytes(uint16_t(0xBBAA), 2, 1));
}

TEST(RevBytesTest, Rev32) {
  ASSERT_EQ(uint32_t(0xAABBCCDDUL), reverse_bytes(uint32_t(0xDDCCBBAAUL)));
  ASSERT_EQ(uint32_t(0xDDCCBBAAUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 1, 1));
  ASSERT_EQ(uint32_t(0xCCDDAABBUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 1, 2));
  ASSERT_EQ(uint32_t(0xAABBCCDDUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 1, 4));
  ASSERT_EQ(uint32_t(0xBBAADDCCUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 2));
  ASSERT_EQ(uint32_t(0xDDCCBBAAUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 2, 1));
  ASSERT_EQ(uint32_t(0xBBAADDCCUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 2, 2));
  ASSERT_EQ(uint32_t(0xDDCCBBAAUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 4));
  ASSERT_EQ(uint32_t(0xDDCCBBAAUL), reverse_bytes(uint32_t(0xDDCCBBAAUL), 4, 1));
}

TEST(RevBytesTest, Rev64) {
  ASSERT_EQ(uint64_t(0xAABBCCDD11223344UL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL)));
  ASSERT_EQ(uint64_t(0x44332211DDCCBBAAUL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 1, 1));
  ASSERT_EQ(uint64_t(0x33441122CCDDAABBUL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 1, 2));
  ASSERT_EQ(uint64_t(0x11223344AABBCCDDUL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 1, 4));
  ASSERT_EQ(uint64_t(0xAABBCCDD11223344UL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 1, 8));
  ASSERT_EQ(uint64_t(0xBBAADDCC22114433UL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 2));
  ASSERT_EQ(uint64_t(0x44332211DDCCBBAAUL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 2, 1));
  ASSERT_EQ(uint64_t(0x22114433BBAADDCCUL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 2, 2));
  ASSERT_EQ(uint64_t(0xBBAADDCC22114433UL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 2, 4));
  ASSERT_EQ(uint64_t(0xDDCCBBAA44332211UL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 4));
  ASSERT_EQ(uint64_t(0x44332211DDCCBBAAUL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 4, 1));
  ASSERT_EQ(uint64_t(0xDDCCBBAA44332211UL), reverse_bytes(uint64_t(0x44332211DDCCBBAAUL), 4, 2));
}


TEST(RevBytesTest, RevI8) {
  ASSERT_EQ(int8_t(0xAA), reverse_bytes(int8_t(0xAA)));
  ASSERT_EQ(int8_t(0xAA), reverse_bytes(int8_t(0xAA), 1, 1));
}

TEST(RevBytesTest, RevI16) {
  ASSERT_EQ(int16_t(0xAABB), reverse_bytes(int16_t(0xBBAA)));
  ASSERT_EQ(int16_t(0xBBAA), reverse_bytes(int16_t(0xBBAA), 1, 1));
  ASSERT_EQ(int16_t(0xAABB), reverse_bytes(int16_t(0xBBAA), 1, 2));
  ASSERT_EQ(int16_t(0xBBAA), reverse_bytes(int16_t(0xBBAA), 2));
  ASSERT_EQ(int16_t(0xBBAA), reverse_bytes(int16_t(0xBBAA), 2, 1));
}

TEST(RevBytesTest, RevI32) {
  ASSERT_EQ(int32_t(0xAABBCCDDUL), reverse_bytes(int32_t(0xDDCCBBAAUL)));
  ASSERT_EQ(int32_t(0xDDCCBBAAUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 1, 1));
  ASSERT_EQ(int32_t(0xCCDDAABBUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 1, 2));
  ASSERT_EQ(int32_t(0xAABBCCDDUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 1, 4));
  ASSERT_EQ(int32_t(0xBBAADDCCUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 2));
  ASSERT_EQ(int32_t(0xDDCCBBAAUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 2, 1));
  ASSERT_EQ(int32_t(0xBBAADDCCUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 2, 2));
  ASSERT_EQ(int32_t(0xDDCCBBAAUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 4));
  ASSERT_EQ(int32_t(0xDDCCBBAAUL), reverse_bytes(int32_t(0xDDCCBBAAUL), 4, 1));
}

TEST(RevBytesTest, RevI64) {
  ASSERT_EQ(int64_t(0xAABBCCDD11223344UL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL)));
  ASSERT_EQ(int64_t(0x44332211DDCCBBAAUL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 1, 1));
  ASSERT_EQ(int64_t(0x33441122CCDDAABBUL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 1, 2));
  ASSERT_EQ(int64_t(0x11223344AABBCCDDUL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 1, 4));
  ASSERT_EQ(int64_t(0xAABBCCDD11223344UL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 1, 8));
  ASSERT_EQ(int64_t(0xBBAADDCC22114433UL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 2));
  ASSERT_EQ(int64_t(0x44332211DDCCBBAAUL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 2, 1));
  ASSERT_EQ(int64_t(0x22114433BBAADDCCUL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 2, 2));
  ASSERT_EQ(int64_t(0xBBAADDCC22114433UL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 2, 4));
  ASSERT_EQ(int64_t(0xDDCCBBAA44332211UL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 4));
  ASSERT_EQ(int64_t(0x44332211DDCCBBAAUL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 4, 1));
  ASSERT_EQ(int64_t(0xDDCCBBAA44332211UL), reverse_bytes(int64_t(0x44332211DDCCBBAAUL), 4, 2));
}

