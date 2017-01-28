#ifndef SANGUIS_SERVER_ARGS_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_RESULT_FWD_HPP_INCLUDED

#include <sanguis/server/args/elements/log_level_fwd.hpp>
#include <sanguis/server/args/elements/port_fwd.hpp>
#include <fcppt/record/variadic_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace args
{

typedef
fcppt::record::variadic<
	sanguis::server::args::elements::port,
	sanguis::server::args::elements::log_level
>
result;

}
}
}

#endif
