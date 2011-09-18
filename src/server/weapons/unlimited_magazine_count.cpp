#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>

sanguis::server::weapons::magazine_count const
sanguis::server::weapons::unlimited_magazine_count(
	std::numeric_limits<magazine_type>::max()
);
