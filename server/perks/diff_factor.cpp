#include "diff_factor.hpp"

sanguis::server::entities::property::value
sanguis::server::perks::diff_factor(
	entities::property::value (*const factor_)(level_type),
	level_type const level_,
	level_diff const diff_
)
{
	return
		factor_(
			level_ + diff_
		)
		-
		factor_(
			level_
		);
}