#ifndef SANGUIS_SERVER_AI_SPEED_FACTOR_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SPEED_FACTOR_FWD_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::property::value,
	speed_factor
);

}
}
}

#endif
