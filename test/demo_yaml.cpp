/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//
// demo_yaml.cpp
//
// (C) Copyright 2002-4 Robert Ramey - http://www.rrsd.com .
//
// Modified for yaml-archive example by Raoul Wols in 2017.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <boost/config.hpp>
#include <cstdio> // remove
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std
{
using ::remove;
}
#endif

#include <YAML/InputArchive.hpp>
#include <YAML/OutputArchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include "demo_gps.hpp"

void save_schedule(const bus_schedule& s, const char* filename)
{
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    YAML::OutputArchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
}

void restore_schedule(bus_schedule& s, const char* filename)
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    YAML::InputArchive ia(ifs);

    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}

int main(int argc, char* argv[])
{
    // make the schedule
    bus_schedule original_schedule;

    // fill in the data
    // make a few stops
    bus_stop* bs0 = new bus_stop_corner(gps_position(34, 135, 52.560f),
                                        gps_position(134, 22, 78.30f),
                                        "24th Street", "10th Avenue");
    bus_stop* bs1 = new bus_stop_corner(gps_position(35, 137, 23.456f),
                                        gps_position(133, 35, 54.12f),
                                        "State street", "Cathedral Vista Lane");
    bus_stop* bs2 =
        new bus_stop_destination(gps_position(35, 136, 15.456f),
                                 gps_position(133, 32, 15.300f), "White House");
    bus_stop* bs3 = new bus_stop_destination(gps_position(35, 134, 48.789f),
                                             gps_position(133, 32, 16.230f),
                                             "Lincoln Memorial");

    // make a  routes
    bus_route route0;
    route0.append(bs0);
    route0.append(bs1);
    route0.append(bs2);

    // add trips to schedule
    original_schedule.append("bob", 6, 24, &route0);
    original_schedule.append("bob", 9, 57, &route0);
    original_schedule.append("alice", 11, 02, &route0);

    // make aother routes
    bus_route route1;
    route1.append(bs3);
    route1.append(bs2);
    route1.append(bs1);

    // add trips to schedule
    original_schedule.append("ted", 7, 17, &route1);
    original_schedule.append("ted", 9, 38, &route1);
    original_schedule.append("alice", 11, 47, &route1);

    // display the complete schedule
    std::cout << "original schedule";
    std::cout << original_schedule;

    std::string filename(boost::archive::tmpdir());
    filename += "/demo.xml";

    // save the schedule
    save_schedule(original_schedule, filename.c_str());

    // ... some time later
    // make  a new schedule
    bus_schedule new_schedule;

    restore_schedule(new_schedule, filename.c_str());

    // and display
    std::cout << "\nrestored schedule";
    std::cout << new_schedule;
    // should be the same as the old one. (except for the pointer values)

    std::remove(filename.c_str());

    delete bs0;
    delete bs1;
    delete bs2;
    delete bs3;
    return 0;
}
