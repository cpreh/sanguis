#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_SCATTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_SCATTER_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/nonmovable.hpp>


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

class scatter
:
	public sanguis::server::entities::enemies::skills::skill
{
	FCPPT_NONMOVABLE(
		scatter
	);
public:
	scatter(
		sanguis::diff_clock_cref,
		sanguis::random_generator_ref,
		sanguis::server::entities::enemies::skills::cooldown
	);

	~scatter()
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

	sanguis::random_generator_ref const random_generator_;

	sanguis::diff_timer cooldown_timer_;
};

}
}
}
}
}

#endif
