#include "with_ai.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"
#include <fcppt/assert/pre.hpp>
#include <fcppt/move.hpp>

sanguis::server::entities::with_ai::with_ai(
	sanguis::diff_clock const &_diff_clock,
	ai::create_function const &_create_ai,
	weapons::unique_ptr _start_weapon
)
:
	base(),
	with_auras(),
	with_weapon(
		_diff_clock,
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
