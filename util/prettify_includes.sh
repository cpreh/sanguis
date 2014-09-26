#!/bin/bash

if [[ $1 == 'run' ]]; then
	shift
	prettify_includes.py --reserved-prefix sanguis --reserved-prefix alda --reserved-prefix sge --reserved-prefix majutsu --reserved-prefix awl --reserved-prefix mizuiro --reserved-prefix fcppt  "$@" 2>>/tmp/prettify_errors
else
	find client collision common core creator gui main media model server tools \( \( -name '*.hpp' -o -name '*.cpp' \) \) | xargs $0 run
fi
