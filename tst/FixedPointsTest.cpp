#define BOOST_TEST_DYN_LINK // optional
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE MyTest // specify the name of your test module
#if defined (__GNUC__) && defined(__unix__)
    #include <boost/test/included/unit_test.hpp> // include this to get main()
#elif defined (WIN32)
    #include <boost/test/unit_test.hpp> // include this to get main()
#endif

#include <iostream>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

using namespace boost::unit_test;
using namespace std;

template class UFixed<8, 8>;
template class SFixed<7, 8>;

BOOST_AUTO_TEST_SUITE(testsuite)

BOOST_AUTO_TEST_CASE(test_getters_ufixed) {
  UQ8x8 a = 1.5;
  BOOST_CHECK( sizeof(uint16_t) == sizeof(a.getInternal()));
  BOOST_CHECK( 0x0180 == a.getInternal());

  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getInteger()));
  BOOST_CHECK( 0x01 == a.getInteger());

  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getFraction()));
  BOOST_CHECK( 0x80 == a.getFraction());
}

BOOST_AUTO_TEST_CASE(test_cast_operators_ufixed) {
  UQ8x8 a = 1.5;
  BOOST_CHECK( 1.5 == static_cast<float>(a) );
  BOOST_CHECK( 1.5 == static_cast<double>(a) );
  BOOST_CHECK( 1.5 == static_cast<long double>(a) );
  BOOST_CHECK( 1 == static_cast<unsigned char>(a) );
  BOOST_CHECK( 1.5 == static_cast<UQ16x16>(a) );
  BOOST_CHECK(1.5 == (static_cast<UFixed<16, 8> >(a)));
  BOOST_CHECK(1.5 == (static_cast<UFixed<20, 4> >(a)));

  BOOST_CHECK(1.5 == static_cast<SQ7x8>(a));
  BOOST_CHECK(1.5 == (static_cast<SFixed<7, 16> >(a)));
  BOOST_CHECK(1.5 == (static_cast<SFixed<11, 4> >(a)));
  a = 0;
  BOOST_CHECK(0 == static_cast<SQ7x8>(a));
}

BOOST_AUTO_TEST_CASE(test_getters_sfixed) {
  SQ7x8 a = 1.5;
  BOOST_CHECK( sizeof(uint16_t) == sizeof(a.getInternal()));
  BOOST_CHECK( 0x0180 == a.getInternal());

  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getInteger()));
  BOOST_CHECK( 0x01 == a.getInteger());

  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getFraction()));
  BOOST_CHECK( 0x80 == a.getFraction());
}

BOOST_AUTO_TEST_CASE(test_cast_operators_sfixed) {
  SQ7x8 a = 1.5;
  SQ15x16 b = 1.5;
  BOOST_CHECK( 1.5 == static_cast<float>(a) );
  BOOST_CHECK( 1.5 == static_cast<double>(a) );
  BOOST_CHECK( 1.5 == static_cast<long double>(a) );
  BOOST_CHECK( 1 == static_cast<signed char>(a) );
  BOOST_CHECK( b == static_cast<SQ15x16>(a) );
  BOOST_CHECK(1.5 == static_cast<UQ8x8>(a));
  a = 0;
  BOOST_CHECK(0 == static_cast<UQ8x8>(a));
  a = -1;
  BOOST_CHECK(255 == static_cast<UQ8x8>(a));
  a = -12.5;
  BOOST_CHECK(243.5 == static_cast<UQ8x8>(a));
}

BOOST_AUTO_TEST_CASE(test_utils) {
  UQ8x8 a = 1.5;
  UQ8x8 b = floorFixed(a);
  BOOST_CHECK( 1.0 == static_cast<float>(b));
}

BOOST_AUTO_TEST_CASE(test_random_ufixed) {
  auto a = randomUFixed<8, 8>();
  BOOST_CHECK( sizeof(uint16_t) == sizeof(a.getInternal()));
  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getInteger()));
  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getFraction()));
}

BOOST_AUTO_TEST_CASE(test_random_sfixed) {
  auto a = randomSFixed<7, 8>();
  BOOST_CHECK( sizeof(uint16_t) == sizeof(a.getInternal()));
  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getInteger()));
  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getFraction()));
}

BOOST_AUTO_TEST_CASE(test_multiply_ufixed) {
  UQ8x8 a = 200.0;
  UQ8x8 b = 1.5;
  BOOST_CHECK( 300.0 == static_cast<float>(multiply(a, b)));
}

BOOST_AUTO_TEST_CASE(test_multiply_sfixed) {
  SQ7x8 a = 100.0;
  SQ7x8 b = 1.5;
  BOOST_CHECK( 150.0 == static_cast<float>(multiply(a, b)));
}

BOOST_AUTO_TEST_CASE(test_basic_arithmetic_operations_same_size_ufixed) {
  UQ8x8 a = 100.0;
  UQ8x8 b = 1.5;
  BOOST_CHECK( 101.5 == a + b);
  BOOST_CHECK( 98.5 == a - b);
  BOOST_CHECK( 150 == a * b);
  BOOST_CHECK( UQ8x8(66.66666666666667) == a / b);
}

BOOST_AUTO_TEST_CASE(test_basic_arithmetic_operations_same_size_sfixed) {
  SQ7x8 a = 100.0;
  SQ7x8 b = 1.5;
  BOOST_CHECK( 101.5 == a + b);
  BOOST_CHECK( 98.5 == a - b);
  BOOST_CHECK( 150 == a * b);
  BOOST_CHECK( SQ7x8(66.66666666666667) == a / b);
}

BOOST_AUTO_TEST_CASE(test_compound_assignemnt_operators_ufixed) {
  UQ8x8 a = 100.0;
  UQ8x8 b = 1.5;
  a += b;
  BOOST_CHECK( 101.5 == a);
  a -= b;
  BOOST_CHECK( 100.0 == a);
  a *= b;
  BOOST_CHECK( 150 == a);
  a /= b;
  BOOST_CHECK( 100.0 == a);
}

BOOST_AUTO_TEST_CASE(test_compound_assignemnt_operators_sfixed) {
  SQ7x8 a = 100.0;
  SQ7x8 b = 1.25;
  a += b;
  BOOST_CHECK( 101.25 == a);
  a -= b;
  BOOST_CHECK( 100.0 == a);
  a *= b;
  BOOST_CHECK( 125 == a);
  a /= b;
  BOOST_CHECK( 100.0 == a);

  a = -100.0;
  a += b;
  BOOST_CHECK( -98.75 == a);
  a -= b;
  BOOST_CHECK( -100.0 == a);
  a *= b;
  BOOST_CHECK( -125 == a);
  a /= b;
  BOOST_CHECK( -100.0 == a);
}

BOOST_AUTO_TEST_CASE(test_increment_and_decrement_ufixed) {
  UQ8x8 a = 100.0;
  ++a;
  BOOST_CHECK( 101.0 == a);
  --a;
  BOOST_CHECK( 100.0 == a);
  UQ8x8 b = a++;
  BOOST_CHECK( 100.0 == b);
  BOOST_CHECK( 101.0 == a);
  b = a--;
  BOOST_CHECK( 100.0 == a);
  BOOST_CHECK( 101.0 == b);
}

BOOST_AUTO_TEST_CASE(test_increment_and_decrement_sfixed) {
  SQ7x8 a = 100.0;
  ++a;
  BOOST_CHECK( 101.0 == a);
  --a;
  BOOST_CHECK( 100.0 == a);
  SQ7x8 b = a++;
  BOOST_CHECK( 100.0 == b);
  BOOST_CHECK( 101.0 == a);
  b = a--;
  BOOST_CHECK( 100.0 == a);
  BOOST_CHECK( 101.0 == b);
}

BOOST_AUTO_TEST_CASE(test_statics_ufixed) {
  UQ8x8 a = 100.0;
  UQ8x8 b = UQ8x8::fromInternal(a.getInternal());
  BOOST_CHECK( 100.0 == b);
}

BOOST_AUTO_TEST_CASE(test_statics_sfixed) {
  SQ7x8 a = 100.0;
  SQ7x8 b = SQ7x8::fromInternal(a.getInternal());
  BOOST_CHECK( 100.0 == b);
  BOOST_CHECK( -100.0 == -b);
}

BOOST_AUTO_TEST_CASE(test_constructors_ufixed) {
  UQ8x8 a;
  BOOST_CHECK(0.0 == a);
  UQ8x8 b(static_cast<const char> (5));
  BOOST_CHECK(5 == b);
  UQ8x8 c(static_cast<const unsigned char> (5));
  BOOST_CHECK(5 == c);
  UQ8x8 d(static_cast<const signed char> (5));
  BOOST_CHECK(5 == d);
  UQ8x8 e(static_cast<const unsigned short> (5));
  BOOST_CHECK(5 == e);
  UQ8x8 f(static_cast<const signed short> (5));
  BOOST_CHECK(5 == f);
  UQ8x8 g(static_cast<const unsigned int> (5));
  BOOST_CHECK(5 == g);
  UQ8x8 h(static_cast<const signed int> (5));
  BOOST_CHECK(5 == h);
  UQ8x8 i(static_cast<const unsigned long> (5));
  BOOST_CHECK(5 == i);
  UQ8x8 j(static_cast<const signed long> (5));
  BOOST_CHECK(5 == j);
  UQ8x8 k(static_cast<const unsigned long long> (5));
  BOOST_CHECK(5 == k);
  UQ8x8 l(static_cast<const signed long long>(5));
  BOOST_CHECK(5 == l);
  UQ8x8 m(static_cast<float>(5));
  BOOST_CHECK(5 == m);
  UQ8x8 n(static_cast<long double>(5));
  BOOST_CHECK(5 == n);
  UQ8x8 o(static_cast<long double>(5));
  BOOST_CHECK(5 == o);
}

BOOST_AUTO_TEST_SUITE_END()
