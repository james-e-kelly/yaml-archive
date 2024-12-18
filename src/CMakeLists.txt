set(YAML_HEADERS
    boost/archive/iterators/yaml_escape.hpp
    boost/archive/iterators/yaml_unescape_exception.hpp
    boost/archive/yaml_iarchive.hpp
    boost/archive/basic_yaml_iarchive.hpp
    boost/archive/polymorphic_yaml_iarchive.hpp
    boost/archive/yaml_oarchive.hpp
    boost/archive/basic_yaml_oarchive.hpp
    boost/archive/polymorphic_yaml_oarchive.hpp
    boost/archive/yaml_wiarchive.hpp
    boost/archive/impl/basic_yaml_grammar.hpp
    boost/archive/polymorphic_yaml_wiarchive.hpp
    boost/archive/yaml_woarchive.hpp
    boost/archive/iterators/yaml_escape.hpp
    boost/archive/polymorphic_yaml_woarchive.hpp
    boost/archive/iterators/yaml_unescape.hpp
    boost/archive/yaml_archive_exception.hpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${YAML_HEADERS})

set(YAML_SOURCES
    boost/archive/yaml_archive_exception.cpp
    boost/archive/yaml_iarchive.cpp
    boost/archive/yaml_oarchive.cpp
    boost/archive/yaml_wiarchive.cpp
    boost/archive/yaml_woarchive.cpp
    boost/archive/impl/basic_yaml_grammar.ipp
    boost/archive/impl/basic_yaml_iarchive.ipp
    boost/archive/impl/basic_yaml_oarchive.ipp
    boost/archive/impl/yaml_iarchive_impl.ipp
    boost/archive/impl/yaml_oarchive_impl.ipp
    boost/archive/impl/yaml_wiarchive_impl.ipp
    boost/archive/impl/yaml_woarchive_impl.ipp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${YAML_SOURCES})

add_library(yaml-archive ${YAML_SOURCES} ${YAML_HEADERS})

set_target_properties(yaml-archive PROPERTIES CXX_STANDARD 11)

target_include_directories(yaml-archive PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include>
)

# Link with boost serialization
if (BUILD_SHARED_LIBS)
    set(Boost_USE_STATIC_LIBS OFF)
    # If we are a shared library, make sure we link with the shared library
    # variant of Boost.Serialization. Users don't have to repeat this because
    # we make this definition public.
    target_compile_definitions(yaml-archive PUBLIC BOOST_SERIALIZATION_DYN_LINK)
else()
    set(Boost_USE_STATIC_LIBS ON)
endif()
target_compile_definitions(yaml-archive PUBLIC BOOST_SERIALIZATION_NO_LIB)

if (yaml-archive_WE_ARE_ROOT)
    include(FetchContent)

    FetchContent_Declare(
    boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.xz
    )

    FetchContent_MakeAvailable(boost)
endif()

# Link with Boost and add its include path to the search paths.
target_link_libraries(yaml-archive PUBLIC Boost::serialization Boost::locale)

if (MSVC)
    target_compile_definitions(yaml-archive PRIVATE _SCL_SECURE_NO_WARNINGS)
    target_compile_definitions(yaml-archive PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(yaml-archive PRIVATE /MP)
endif()

install(TARGETS yaml-archive
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include)
