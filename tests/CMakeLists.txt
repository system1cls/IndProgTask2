set(SOURCE_FILES_WITH_PATH "")
foreach(source_file ${bank})
    list(APPEND SOURCE_FILES_WITH_PATH "../${source_file}")
endforeach()

add_executable (IndProgTask2Test ${SOURCE_FILES_WITH_PATH} "TestApproaches.cpp" "loadConfigs.cpp")

find_package(GTest REQUIRED)

target_include_directories(IndProgTask2Test PUBLIC 
    $<BUILD_INTERFACE:${HEADER}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


target_link_libraries(IndProgTask2Test PUBLIC GTest::GTest)
