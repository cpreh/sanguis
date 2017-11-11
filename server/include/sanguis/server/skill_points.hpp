#ifndef SANGUIS_SERVER_SKILL_POINTS_HPP_INCLUDED
#define SANGUIS_SERVER_SKILL_POINTS_HPP_INCLUDED

#include <sanguis/messages/types/level.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::messages::types::level,
	skill_points
);

}
}

#endif
