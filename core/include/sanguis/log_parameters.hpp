#ifndef SANGUIS_LOG_PARAMETERS_HPP_INCLUDED
#define SANGUIS_LOG_PARAMETERS_HPP_INCLUDED

#include <sanguis/symbol.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location_fwd.hpp>


namespace sanguis
{

SANGUIS_SYMBOL
fcppt::log::parameters::object
log_parameters(
	fcppt::log::location const &
);

}

#endif
