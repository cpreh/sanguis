#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/enemies/skills/skill_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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

typedef
std::unique_ptr<
	sanguis::server::entities::enemies::skills::skill
>
unique_ptr;

}
}
}
}
}

#endif
