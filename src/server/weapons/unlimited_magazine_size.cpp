#include "unlimited_magazine_size.hpp"
#include <limits>

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::unlimited_magazine_size(
	std::numeric_limits<magazine_type>::max()
);
