# this is only so my IDE likes me, not for actual builds

project(nodearrow)
cmake_minimum_required(VERSION 3.22)

include_directories(/opt/homebrew/Cellar/apache-arrow/9.0.0_1/include /Users/hannes/Library/Caches/node-gyp/18.8.0/include/node /Users/hannes/source/nodearrow/node_modules/node-addon-api)

add_library(nodearrow src/nodearrow.cpp)