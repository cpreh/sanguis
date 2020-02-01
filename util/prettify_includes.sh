#!/usr/bin/env bash

LIBS=(--library sanguis --library alda --library sge --library awl --library mizuiro --library fcppt)
DIRS=(client collision common core creator main media model server tools)

prettify_includes "${LIBS[@]}" "${DIRS[@]}"
