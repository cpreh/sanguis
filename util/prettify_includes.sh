#!/usr/bin/env bash

ARGS=(--library sanguis --library alda --library sge --library awl --library mizuiro --library fcppt)

find client collision common core creator main media model server tools \( \( -name '*.hpp' -o -name '*.cpp' \) \) -exec update_headers.sh '{}' "${ARGS[@]}" \;
