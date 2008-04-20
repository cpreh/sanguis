#include "time_util.hpp"

sge::time_type
sanguis::to_sge_time(
	const time_type tm)
{
	return static_cast<sge::time_type>(
		tm * static_cast<time_type>(
			sge::second()));
}
