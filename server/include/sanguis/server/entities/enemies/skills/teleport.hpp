#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_TELEPORT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_TELEPORT_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::enemies::skills
{

class teleport
:
	public sanguis::server::entities::enemies::skills::skill
{
	FCPPT_NONMOVABLE(
		teleport
	);
public:
	teleport(
		sanguis::diff_clock_cref,
		sanguis::server::entities::enemies::skills::cooldown
	);

	~teleport()
	override;
private:
	void
	update(
		sanguis::server::entities::enemies::enemy & // NOLINT(google-runtime-references)
	) // NOLINT(google-runtime-references)
	override;

	[[nodiscard]]
	sanguis::server::entities::enemies::attribute
	attribute() const
	override;

	sanguis::diff_timer cooldown_timer_;
};

}

#endif
