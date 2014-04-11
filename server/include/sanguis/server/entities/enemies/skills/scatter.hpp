#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_SCATTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_SCATTER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
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

class scatter
:
	public sanguis::server::entities::enemies::skills::skill
{
	FCPPT_NONCOPYABLE(
		scatter
	);
public:
	scatter(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::entities::enemies::skills::cooldown
	);

	~scatter()
	override;
private:
	void
	update(
		sanguis::server::entities::enemies::enemy &
	)
	override;

	sanguis::server::entities::enemies::attribute
	attribute() const
	override;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::diff_timer cooldown_timer_;
};

}
}
}
}
}

#endif