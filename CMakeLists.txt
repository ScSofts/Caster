cmake_minimum_required(VERSION 3.10.0)
project(Caster)

add_subdirectory(asmjit)


add_library(caster STATIC caster.cc)
target_include_directories(caster PUBLIC ${ASMJIT_DIR}/src/)


add_executable(caster-test caster-test.c)
target_link_libraries(caster-test PUBLIC asmjit
                                  PUBLIC caster)
target_compile_options(caster-test PUBLIC "-g"  PUBLIC "-Og")