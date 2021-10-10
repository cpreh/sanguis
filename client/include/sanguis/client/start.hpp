#ifndef SANGUIS_CLIENT_START_HPP_INCLUDED
#define SANGUIS_CLIENT_START_HPP_INCLUDED

#include <sanguis/client/symbol.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <awl/main/exit_code.hpp>

namespace sanguis::client
{

SANGUIS_CLIENT_SYMBOL
awl::main::exit_code start(sanguis::client::args::result const &);

}

#endif
