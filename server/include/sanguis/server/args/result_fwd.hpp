#ifndef SANGUIS_SERVER_ARGS_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_RESULT_FWD_HPP_INCLUDED

#include <sanguis/server/args/elements/log_level_fwd.hpp>
#include <sanguis/server/args/elements/port_fwd.hpp>
#include <fcppt/record/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace args
{

using
result
=
fcppt::record::object<
	sanguis::server::args::elements::port,
	sanguis::server::args::elements::log_level
>;

}
}
}

#endif
