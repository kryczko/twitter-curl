# Top-level cmake file. All settings are inherited by children cmake files.

# Recursively includes all children cmake files using add_subdirectory(...)

cmake_minimum_required( VERSION 2.6 )

include_directories( src/dependencies/curl )
include_directories( src/dependencies/yaml-cpp )

project(twitter-curl)

aux_source_directory(
	"src" 
	twitter-curl-src
)

add_definitions( -std=c++11 )

add_executable (
	twitter-curl 
	${twitter-curl-src}
)

target_link_libraries (
	twitter-curl
	curl
	yaml-cpp
)

