cmake_minimum_required(VERSION 3.5)

project(pc_test LANGUAGES C)

set(table_miner ../../micropm)
include_directories(${table_miner})

add_executable(pc_test main.c ${table_miner}/table_miner.c)
