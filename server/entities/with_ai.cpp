#include "with_ai.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"

sanguis::server::entities::with_ai::with_ai(
	ai::auto_ptr ai_,
	weapons::auto_ptr start_weapon
)
:
	base(),
	with_auras(),
	with_weapon(
		start_weapon
	),
	ai_(ai_)
{
	this->ai_->bind(
		*this
	);
}

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
