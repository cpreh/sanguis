#include "current_sun_angle.hpp"
#include "sun_angle.hpp"
#include <ctime>

sanguis::client::draw2d::sunlight::real
sanguis::client::draw2d::sunlight::current_sun_angle()
{
	return
		sunlight::sun_angle(
			std::time(
				0
			)
		);
}
