#!/bin/bash

function die()
{
	exit -1
}

function update_cmake_file()
{
	local cmakefile="$1"	

	update_cmake \
		"${cmakefile}" \
		"${@:2}" \
		|| die
	
	mv "${cmakefile}".new "${cmakefile}" || die
}

update_cmake_file \
	CMakeLists.txt \
	SANGUIS_FILES \
	src \

pushd creator > /dev/null

update_cmake_file \
	CMakeLists.txt \
	SANGUIS_CREATOR_INCLUDE_FILES \
	include \

update_cmake_file \
	CMakeLists.txt \
	SANGUIS_CREATOR_SRC_FILES \
	src \

popd > /dev/null
