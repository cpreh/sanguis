#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_COOLDOWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_COOLDOWN_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace skills
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	cooldown
);

}
}
}
}
}

#endif
