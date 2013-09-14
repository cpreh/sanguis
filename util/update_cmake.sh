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
	SANGUIS_CREATOR_FILES \
	include \
	src

popd > /dev/null

pushd collision > /dev/null

update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_FILES \
	include \
	-n \
	src \
	src/include/sanguis/collision/aux \
	src/aux \
	src/include/sanguis/collision/aux/world \
	src/aux/world \
	-r \
	src/world \
	src/include/sanguis/collision/aux/world/simple \
	src/aux/world/simple


update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_PROJECTILE_FILES \
	src/include/sanguis/collision/aux/world/projectile \
	src/aux/world/projectile

popd > /dev/null
