#ifndef SANGUIS_SERVER_BUFFS_SLOW_FACTOR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_SLOW_FACTOR_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::property::value,
	slow_factor
);

}
}
}

#endif
