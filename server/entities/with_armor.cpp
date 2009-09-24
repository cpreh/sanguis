#include "with_armor.hpp"

void
sanguis::server::entities::with_armor::damage(
	space_unit const d,
	damage::array const &damages
)
{
	for(
		damage::array::size_type i = 0;
		i < damages.size();
		++i
	)
		health(
			health()
			- d * damages[i] * (1 - armor_[i])
		);

	if(dead())
		die();
}
