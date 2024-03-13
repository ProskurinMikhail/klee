add_klee_unit_test(UniqueStatesTest
  UniqueStatesTest.cpp)
target_link_libraries(UniqueStatesTest PRIVATE kleeCore)
target_include_directories(UniqueStatesTest BEFORE PRIVATE "${CMAKE_SOURCE_DIR}/lib")
target_compile_options(UniqueStatesTest PRIVATE ${KLEE_COMPONENT_CXX_FLAGS})
target_compile_definitions(UniqueStatesTest PRIVATE ${KLEE_COMPONENT_CXX_DEFINES})

target_include_directories(UniqueStatesTest PRIVATE ${KLEE_INCLUDE_DIRS})