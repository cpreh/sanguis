#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_TELEPORT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_TELEPORT_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/noncopyable.hpp>


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

class teleport
:
	public sanguis::server::entities::enemies::skills::skill
{
	FCPPT_NONCOPYABLE(
		teleport
	);
public:
	teleport(
		sanguis::diff_clock const &,
		sanguis::server::entities::enemies::skills::cooldown
	);

	~teleport()
	override;

	void
	update(
		sanguis::server::entities::enemies::enemy &
	)
	override;
private:
	sanguis::diff_timer cooldown_timer_;
};

}
}
}
}
}

#endif
