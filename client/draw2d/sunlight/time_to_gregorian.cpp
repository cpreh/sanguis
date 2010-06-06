#include "time_to_gregorian.hpp"
#include <boost/date_time/date_defs.hpp>
#include <ctime>

boost::gregorian::date const
sanguis::client::draw2d::sunlight::time_to_gregorian(
	std::tm const &tm_
)
{
	return
		boost::gregorian::date(
			static_cast<
				boost::gregorian::date::year_type
			>(
				tm_.tm_year
			),
			static_cast<
				boost::date_time::months_of_year
			>(
				tm_.tm_mon
			),
			static_cast<
				boost::gregorian::date::day_type
			>(
				tm_.tm_mday
			)
		);
}
