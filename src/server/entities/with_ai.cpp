#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/ai/base.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/move.hpp>

sanguis::server::entities::with_ai::with_ai(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	ai::create_function const &_create_ai,
	weapons::unique_ptr _start_weapon
)
:
	base(),
	with_auras(),
	with_weapon(
		_diff_clock,
		_random_generator,
		fcppt::move(
			_start_weapon
		)
	),
	create_ai_(_create_ai),
	ai_()
{
}

sanguis::server::entities::with_ai::~with_ai()
{
}

void
sanguis::server::entities::with_ai::on_update()
{
	with_weapon::on_update();

	FCPPT_ASSERT_PRE(
		ai_
	);

	ai_->update();
}

void
sanguis::server::entities::with_ai::on_create()
{
	ai_.take(
		create_ai_(
			*this
		)
	);
}
