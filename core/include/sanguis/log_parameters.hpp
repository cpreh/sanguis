#ifndef SANGUIS_LOG_PARAMETERS_HPP_INCLUDED
#define SANGUIS_LOG_PARAMETERS_HPP_INCLUDED

#include <sanguis/core/symbol.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters.hpp>


namespace sanguis
{

SANGUIS_CORE_SYMBOL
fcppt::log::parameters
log_parameters(
	fcppt::log::location const &
);

}

#endif
