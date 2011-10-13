#ifndef SANGUIS_APPLY_LOG_LEVEL_HPP_INCLUDED
#define SANGUIS_APPLY_LOG_LEVEL_HPP_INCLUDED

#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>

namespace sanguis
{

void
apply_log_level(
	fcppt::log::location const &,
	fcppt::log::context &,
	fcppt::log::level::type
);

}

#endif
