#include "localtime.hpp"
#include <ctime>

std::tm const
sanguis::client::draw2d::sunlight::localtime(
	std::time_t const time_
)
{
	return
		*std::localtime(
			&time_
		);
}
