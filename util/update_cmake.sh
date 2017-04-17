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

update_sublibrary \
	collision \
	impl

update_sublibrary common

update_sublibrary core

update_sublibrary \
	creator \
	impl

update_sublibrary \
	model \
	impl

update_sublibrary server

update_sublibrary \
	tiles \
	impl

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

update_impl tools/drawlevel \
	src
