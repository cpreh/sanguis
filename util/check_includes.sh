#!/bin/sh

find client collision common core creator main model server tiles tools -name include -exec check_includes '{}' \;
