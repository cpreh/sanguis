#include <sanguis/client/draw2d/sunlight/time_to_gregorian.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/date_time/date_defs.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>

boost::gregorian::date const
sanguis::client::draw2d::sunlight::time_to_gregorian(
	std::tm const &_tm
)
{
	return
		boost::gregorian::date(
			static_cast<
				unsigned short
			>(
				_tm.tm_year + 1900 // year starts at 1900
			),
			static_cast<
				unsigned short
			>(
				_tm.tm_mon + 1 // boost::date_time::Jan is 1
			),
			static_cast<
				unsigned short
			>(
				_tm.tm_mday
			)
		);
}
