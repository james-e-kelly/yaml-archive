/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_list.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// should pass compilation and execution

#include <cstddef> // NULL
#include <cstdio>  // remove
#include <fstream>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
using ::remove;
}
#endif

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_HDR_FORWARD_LIST
#error this test presumes support for forward_list.hpp
#endif
#include <boost/serialization/forward_list.hpp>

#include "test_tools.hpp"
#include <boost/archive/archive_exception.hpp>

#include "A.hpp"
#include "A.hpp"

int test_main(int /* argc */, char* /* argv */ [])
{
    const char* testfile = "forward_list.yml";
    std::forward_list<A> aslist;
    aslist.push_front(A());
    aslist.push_front(A());
    {
        test_ostream os(testfile, TEST_STREAM_FLAGS);
        test_oarchive oa(os, TEST_ARCHIVE_FLAGS);
        oa << boost::serialization::make_nvp("aslist", aslist);
    }
    std::forward_list<A> aslist1;
    {
        test_istream is(testfile, TEST_STREAM_FLAGS);
        test_iarchive ia(is, TEST_ARCHIVE_FLAGS);
        ia >> boost::serialization::make_nvp("aslist", aslist1);
    }
    BOOST_CHECK(aslist == aslist1);
    return EXIT_SUCCESS;
}

// EOF
