#ifndef SANGUIS_SERVER_ARGS_PARSER_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_PARSER_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/args/result_fwd.hpp>
#include <fcppt/options/base_unique_ptr.hpp>

namespace sanguis::server::args
{

using parser_unique_ptr = fcppt::options::base_unique_ptr<sanguis::server::args::result>;

}

#endif
