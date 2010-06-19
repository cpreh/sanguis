#include "gmtime.hpp"
#include <ctime>

std::tm const
sanguis::client::gmtime(
	std::time_t const time_
)
{
	return
		*std::gmtime(
			&time_
		);
}
