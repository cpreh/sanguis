#include "unlimited_magazine_count.hpp"
#include <limits>

sanguis::server::weapons::magazine_count const
sanguis::server::weapons::unlimited_magazine_count(
	std::numeric_limits<magazine_type>::max()
);
