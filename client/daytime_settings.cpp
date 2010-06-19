#include "daytime_settings.hpp"
#include "gmtime.hpp"
#include <sge/console/object.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/time/parse_date.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <ctime>

namespace
{

int const invalid_value = -1;

struct overwrite_members
{
	typedef void result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T const &t
	) const
	{
#if 0
		if(
			src != invalid_value
		)
			dest = src;
#endif
	}
};

}

BOOST_FUSION_ADAPT_STRUCT(
	struct std::tm,
	(int, tm_sec)
	(int, tm_min)
	(int, tm_hour)
	(int, tm_mday)
	(int, tm_mon)
	(int, tm_year)
	(int, tm_mday)
	(int, tm_yday)
	(int, tm_isdst)
)

sanguis::client::daytime_settings::daytime_settings(
	sge::console::object &console_
)
:
	day_con_(
		console_.insert(
			FCPPT_TEXT("day"),
			std::tr1::bind(
				&daytime_settings::change_day,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Sets the current day to a fixed value.")
		)
	),
	time_con_(
		console_.insert(
			FCPPT_TEXT("time"),
			std::tr1::bind(
				&daytime_settings::change_time,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Sets the current time to a fixed value.")
		)
	),
	time_speed_con_(
		console_.insert(
			FCPPT_TEXT("time_speed"),
			std::tr1::bind(
				&daytime_settings::change_time,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Sets the current time speedup. Use a value of 1 to reset this.")
		)
	),
	reset_day_con_(
		console_.insert(
			FCPPT_TEXT("reset_day"),
			std::tr1::bind(
				&daytime_settings::change_time,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Resets to the current day.")
		)
	),
	reset_time_con_(
		console_.insert(
			FCPPT_TEXT("reset_time"),
			std::tr1::bind(
				&daytime_settings::change_time,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Resets to the current time.")
		)
	)
{
	boost::fusion::for_each(
		current_time_,
		boost::phoenix::arg_names::arg1 = invalid_value 
	);
}

#include <boost/fusion/include/vector.hpp>

std::tm const
sanguis::client::daytime_settings::current_time()
{
	std::tm localtime_(
		client::gmtime(
			std::time(0)
		)
	);

	typedef boost::fusion::vector<
		std::tm &,
		std::tm &
	> zipped_vec;

	boost::fusion::for_each(
		boost::fusion::zip_view<
			zipped_vec
		>(
			zipped_vec(
				current_time_,
				localtime_
			)
		),
		overwrite_members()
	);

	return localtime_; // TODO: return current_time_ instead!
}

void
sanguis::client::daytime_settings::change_day(
	sge::console::arg_list const &args_
)
{
	if(
		args_.empty()
	)
		return;

	fcppt::io::istringstream iss(
		args_[0]
	);

	// TODO: check for errors
	fcppt::time::parse_date(
		iss,
		current_time_
	);
}

void
sanguis::client::daytime_settings::change_time(
	sge::console::arg_list const &args_
)
{
}

void
sanguis::client::daytime_settings::change_time_speed(
	sge::console::arg_list const &args_
)
{
}

void
sanguis::client::daytime_settings::reset_day(
	sge::console::arg_list const &args_
)
{
	current_time_.tm_mday = invalid_value;
	current_time_.tm_mon = invalid_value;
	current_time_.tm_year = invalid_value;
	current_time_.tm_wday = invalid_value;
	current_time_.tm_yday = invalid_value;
}

void
sanguis::client::daytime_settings::reset_time(
	sge::console::arg_list const &args_
)
{
	current_time_.tm_sec = invalid_value;
	current_time_.tm_min = invalid_value;
	current_time_.tm_hour = invalid_value;
}
