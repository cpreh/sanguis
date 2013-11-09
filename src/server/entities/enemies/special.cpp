#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::special::special(
	sanguis::server::entities::enemies::parameters &&_parameters,
	sanguis::server::entities::enemies::skills::container &&_skills
)
:
	sanguis::server::entities::enemies::enemy(
		std::move(
			_parameters
		)
	),
	skills_()
{
	for(
		auto &skill
		:
		_skills
	)
		fcppt::container::ptr::push_back_unique_ptr(
			skills_,
			std::move(
				skill
			)
		);
}

sanguis::server::entities::enemies::special::~special()
{
}

void
sanguis::server::entities::enemies::special::update()
{
	sanguis::server::entities::enemies::enemy::update();

	for(
		auto &skill
		:
		skills_
	)
		skill.update(
			*this
		);
}
