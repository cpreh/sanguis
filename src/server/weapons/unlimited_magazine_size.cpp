#include <sanguis/server/weapons/unlimited_magazine_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::unlimited_magazine_size(
	std::numeric_limits<magazine_type>::max()
);
