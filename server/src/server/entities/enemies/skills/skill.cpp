#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>


sanguis::server::entities::enemies::skills::skill::skill()
= default;

sanguis::server::entities::enemies::skills::skill::~skill()
= default;

void
sanguis::server::entities::enemies::skills::skill::update(
	sanguis::server::entities::enemies::enemy &
)
{
}

void
sanguis::server::entities::enemies::skills::skill::on_die(
	sanguis::server::entities::enemies::enemy const &
)
{
}
