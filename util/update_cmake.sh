#!/bin/bash

set -e -u

function update_sublibrary()
{
	update_cmake.sh \
		"$1"/files.txt \
		"$1"/include \
		"$1"/src \
		"$1/${@:2}"
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

update_sublibrary \
	tools/libmergeimage \
	impl
