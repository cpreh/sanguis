#include "gmtime.hpp"
#include <ctime>

std::tm const
sanguis::client::gmtime(
	std::time_t const _time
)
{
	return
		*std::gmtime(
			&_time
		);
}
