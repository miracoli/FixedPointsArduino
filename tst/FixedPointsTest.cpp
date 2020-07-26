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

BOOST_AUTO_TEST_SUITE(testsuite)

BOOST_AUTO_TEST_CASE(test_getters) {
  UQ8x8 a = 1.5;
  BOOST_CHECK( sizeof(uint16_t) == sizeof(a.getInternal()));
  BOOST_CHECK( 0x0180 == a.getInternal());

  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getInteger()));
  BOOST_CHECK( 0x01 == a.getInteger());

  BOOST_CHECK( sizeof(uint8_t) == sizeof(a.getFraction()));
  BOOST_CHECK( 0x80 == a.getFraction());
}

BOOST_AUTO_TEST_CASE(test_cast_operators) {
  UQ8x8 a = 1.5;
  UQ16x16 b = 1.5;
  BOOST_CHECK( 1.5 == static_cast<float>(a) );
  BOOST_CHECK( 1.5 == static_cast<double>(a) );
  BOOST_CHECK( 1.5 == static_cast<long double>(a) );
  //BOOST_CHECK( 1 == static_cast<unsigned int>(a) );
  BOOST_CHECK( b == static_cast<UQ16x16>(a) );
}

BOOST_AUTO_TEST_SUITE_END()
