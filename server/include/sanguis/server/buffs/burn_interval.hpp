#ifndef SANGUIS_SERVER_BUFFS_BURN_INTERVAL_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_INTERVAL_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	burn_interval
);

}
}
}

#endif
