add_library(libkdb
    process.cpp
)

add_library(kdb::libkdb ALIAS libkdb)

set_target_properties(libkdb PROPERTIES OUTPUT_NAME kdb)

target_compile_features(libkdb PUBLIC cxx_std_20)

target_include_directories(libkdb
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
)

target_link_libraries(libkdb
    PkgConfig::libedit
)

include(GNUInstallDirs)

install(TARGETS libkdb
    EXPORT kdb-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT kdb-targets
    FILE kdb-config.cmake
    NAMESPACE kdb::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kdb
)