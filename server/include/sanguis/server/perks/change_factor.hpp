#ifndef SANGUIS_SERVER_PERKS_CHANGE_FACTOR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHANGE_FACTOR_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::property::value,
	change_factor
);

}
}
}

#endif
