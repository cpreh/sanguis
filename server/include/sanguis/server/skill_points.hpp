#ifndef SANGUIS_SERVER_SKILL_POINTS_HPP_INCLUDED
#define SANGUIS_SERVER_SKILL_POINTS_HPP_INCLUDED

#include <sanguis/messages/types/level.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sanguis::server
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::messages::types::level, skill_points);

}

#endif
