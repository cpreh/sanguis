#include "with_ai.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"

sanguis::server::entities::with_ai::with_ai(
	ai::create_function const &_create_ai,
	weapons::unique_ptr _start_weapon
)
:
	base(),
	with_auras(),
	with_weapon(
		move(
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
sanguis::server::entities::with_ai::on_update(
	time_type const _time
)
{
	with_auras::on_update(
		_time
	);

	with_weapon::on_update(
		_time
	);

	ai_->update(
		_time
	);
}

#if 0
void
sanguis::server::entities::with_ai::on_transfer(
	collision::transfer_parameters const &_param
)
{
	ai_.reset(
		create_ai_(
			*this
		)
	);

	with_ghosts::on_transfer(
		_param
	);
}
#endif
