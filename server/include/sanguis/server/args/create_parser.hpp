#ifndef SANGUIS_SERVER_ARGS_CREATE_PARSER_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_CREATE_PARSER_HPP_INCLUDED

#include <sanguis/server/symbol.hpp>
#include <sanguis/server/args/parser_unique_ptr.hpp>


namespace sanguis::server::args
{

SANGUIS_SERVER_SYMBOL
sanguis::server::args::parser_unique_ptr
create_parser();

}

#endif
