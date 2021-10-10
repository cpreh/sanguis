#ifndef SANGUIS_SERVER_BUFFS_BURN_INTERVAL_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_INTERVAL_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sanguis::server::buffs
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::duration, burn_interval);

}

#endif
