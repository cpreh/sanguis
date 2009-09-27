#include "with_ai.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"

sanguis::server::entities::with_ai::with_ai(
	ai::create_function const &create_ai_,
	weapons::auto_ptr start_weapon
)
:
	base(),
	with_auras(),
	with_weapon(
		start_weapon
	),
	create_ai_(create_ai_),
	ai_()
{}

sanguis::server::entities::with_ai::~with_ai()
{}

void
sanguis::server::entities::with_ai::on_update(
	time_type const time
)
{
	with_auras::on_update(
		time
	);

	with_weapon::on_update(
		time
	);

	ai_->update(
		time
	);
}

void
sanguis::server::entities::with_ai::on_transfer(
	collision::global_groups const &groups_,
	collision::create_parameters const &param_
)
{
	ai_.reset(
		create_ai_(
			*this
		)
	);

	with_auras::on_transfer(
		groups_,
		param_
	);
}
