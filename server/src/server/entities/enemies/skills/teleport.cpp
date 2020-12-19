#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/teleport.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>


sanguis::server::entities::enemies::skills::teleport::teleport(
	sanguis::diff_clock_cref const _diff_clock,
	sanguis::server::entities::enemies::skills::cooldown const _cooldown
)
:
	sanguis::server::entities::enemies::skills::skill(),
	cooldown_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_cooldown.get()
		)
	)
{
}

sanguis::server::entities::enemies::skills::teleport::~teleport()
= default;

void
sanguis::server::entities::enemies::skills::teleport::update(
	sanguis::server::entities::enemies::enemy &_entity
)
{
	if(
		!sge::timer::reset_when_expired(
			fcppt::make_ref(
				cooldown_timer_
			)
		)
	)
	{
		return;
	}

	fcppt::optional::maybe_void(
		_entity.target(),
		[
			&_entity
		](
			sanguis::server::weapons::target const &_target
		)
		{
			_entity.center(
				sanguis::server::center(
					_target.get()
				)
			);
		}
	);
}

sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::skills::teleport::attribute() const
{
	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("teleporting")
		);
}
