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

update_sublibrary main

update_sublibrary client

update_impl collision \
	include \
	-n \
	src \
	src/include/sanguis/collision/impl \
	src/impl \
	src/include/sanguis/collision/impl/world \
	src/impl/world \
	-r \
	src/world

pushd collision >> /dev/null

update_cmake \
	CMakeLists.txt \
	SANGUIS_COLLISION_SIMPLE_FILES \
	src/include/sanguis/collision/impl/world/simple \
	src/impl/world/simple


popd >> /dev/null

update_sublibrary common

update_sublibrary core

update_sublibrary creator

update_sublibrary gui

update_sublibrary model

update_sublibrary server

update_impl tools/animations \
	src \
	include \
	-e '.*.ui' \
	ui

update_impl tools/check_json \
	src

update_sublibrary tools/libmergeimage

update_impl tools/mergeimage \
	src
