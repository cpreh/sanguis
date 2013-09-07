#!/bin/sh

set -e -u

update_cmake \
	src/CMakeLists.txt \
	SANGUIS_FILES \
	src \
	include

pushd creator > /dev/null

update_cmake \
	CMakeLists.txt \
	SANGUIS_CREATOR_INCLUDE_FILES \
	include

update_cmake \
	CMakeLists.txt \
	SANGUIS_CREATOR_SRC_FILES \
	src

popd > /dev/null

pushd collision > /dev/null

update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_INCLUDE_FILES \
	include

update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_SRC_FILES \
	src

popd > /dev/null
