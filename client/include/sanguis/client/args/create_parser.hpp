#ifndef SANGUIS_CLIENT_ARGS_CREATE_PARSER_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_CREATE_PARSER_HPP_INCLUDED

#include <sanguis/client/symbol.hpp>
#include <sanguis/client/args/parser_unique_ptr.hpp>


namespace sanguis::client::args
{

SANGUIS_CLIENT_SYMBOL
sanguis::client::args::parser_unique_ptr
create_parser();

}

#endif
