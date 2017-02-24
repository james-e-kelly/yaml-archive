/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_deque.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// should pass compilation and execution

#include <cstddef>
#include <fstream>

#include <boost/config.hpp>
#include <cstdio> // remove
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
using ::remove;
}
#endif

#include "test_tools.hpp"
#include <boost/archive/archive_exception.hpp>

#include <boost/serialization/deque.hpp>

#include "A.hpp"
#include "A.ipp"

int test_main(int /* argc */, char* /* argv */ [])
{
    const char* testfile = "deque.yml";
    BOOST_REQUIRE(NULL != testfile);

    // test array of objects
    std::deque<A> adeque, adeque1;
    adeque.push_front(A());
    adeque.push_front(A());
    {
        test_ostream os(testfile, TEST_STREAM_FLAGS);
        test_oarchive oa(os, TEST_ARCHIVE_FLAGS);
        oa << boost::serialization::make_nvp("adeque", adeque);
    }
    {
        test_istream is(testfile, TEST_STREAM_FLAGS);
        test_iarchive ia(is, TEST_ARCHIVE_FLAGS);
        ia >> boost::serialization::make_nvp("adeque", adeque1);
    }
    BOOST_CHECK(adeque == adeque1);

    // std::remove(testfile);
    return EXIT_SUCCESS;
}

// EOF