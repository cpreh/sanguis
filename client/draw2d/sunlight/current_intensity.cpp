#include "current_intensity.hpp"
#include "intensity.hpp"
#include <ctime>

sanguis::client::draw2d::sunlight::real
sanguis::client::draw2d::sunlight::current_intensity()
{
	return
		sunlight::intensity(
			std::time(
				0
			)
		);
}
