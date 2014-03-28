#!/bin/bash

set -e -u

function toupper()
{
	echo $(tr 'a-z' 'A-Z' <<< "$1")
}

function update_impl()
{
	local sublibrary="$1"

	local upperpath=$(toupper "${sublibrary}")

	pushd "${sublibrary}" >> /dev/null

	update_cmake \
		CMakeLists.txt \
		SANGUIS_"${upperpath/\//_}"_FILES \
		"${@:2}"

	popd >> /dev/null
}

function update_sublibrary()
{
	update_impl \
		"$@" \
		include \
		src
}

update_cmake \
	src/CMakeLists.txt \
	SANGUIS_FILES \
	src \
	include

update_sublibrary creator

update_sublibrary gui

update_impl collision \
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

pushd collision >> /dev/null

update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_PROJECTILE_FILES \
	src/include/sanguis/collision/aux_/world/projectile \
	src/aux_/world/projectile

popd >> /dev/null

update_sublibrary core

update_sublibrary model

update_impl tools/animations \
	src \
	include \
	-e '.*.ui' \
	ui

update_impl tools/check_json \
	src
