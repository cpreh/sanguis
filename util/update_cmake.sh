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

pushd gui > /dev/null

update_cmake \
	CMakeLists.txt \
	SANGUIS_GUI_FILES \
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
	src/include/sanguis/collision/aux_ \
	src/aux_ \
	src/include/sanguis/collision/aux_/world \
	src/aux_/world \
	-r \
	src/world \
	src/include/sanguis/collision/aux_/world/simple \
	src/aux_/world/simple


update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_PROJECTILE_FILES \
	src/include/sanguis/collision/aux_/world/projectile \
	src/aux_/world/projectile

popd > /dev/null
