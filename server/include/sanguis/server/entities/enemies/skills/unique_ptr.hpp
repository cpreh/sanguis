#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/enemies/skills/skill_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::entities::enemies::skills
{

using
unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::entities::enemies::skills::skill
>;

}

#endif
