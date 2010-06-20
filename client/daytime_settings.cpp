#include "daytime_settings.hpp"
#include "gmtime.hpp"
#include <sge/console/object.hpp>
#include <sge/console/gfx.hpp>
#include <fcppt/chrono/system_clock.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>
#include <fcppt/chrono/time_point_impl.hpp>
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/time/parse_date.hpp>
#include <fcppt/time/parse_time.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/view/zip_view.hpp>
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

		int &dest(
			boost::fusion::at_c<0>(t)
		);

		int const &src(
			boost::fusion::at_c<1>(t)
		);

		if(
			src != invalid_value
		)
			dest = src;
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
	sge::console::gfx &_console
)
:
	console_(_console),
	time_begin_(
		daytime_settings::now()
	),
	speedup_(1),
	day_con_(
		console_.object().insert(
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
		console_.object().insert(
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
		console_.object().insert(
			FCPPT_TEXT("time_speed"),
			std::tr1::bind(
				&daytime_settings::change_time_speed,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Sets the current time speedup. Use a value of 1 to reset this.")
		)
	),
	reset_day_con_(
		console_.object().insert(
			FCPPT_TEXT("reset_day"),
			std::tr1::bind(
				&daytime_settings::reset_day,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("Resets to the current day.")
		)
	),
	reset_time_con_(
		console_.object().insert(
			FCPPT_TEXT("reset_time"),
			std::tr1::bind(
				&daytime_settings::reset_time,
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

sanguis::client::daytime_settings::~daytime_settings()
{}

std::tm const
sanguis::client::daytime_settings::current_time()
{
	time_point const time_(
		daytime_settings::now()
	);

	std::tm const localtime_(
		client::gmtime(
			clock::to_time_t(
				time_begin_
				+ (
					time_
					- time_begin_
				)
				* speedup_
			)
		)
	);

	typedef boost::fusion::vector<
		std::tm &,
		std::tm const &
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

	return current_time_;
}

void
sanguis::client::daytime_settings::change_day(
	sge::console::arg_list const &args_
)
{
	if(
		args_.size() != 2
	)
	{
		console_.print_line(
			FCPPT_TEXT("The date command needs one argument!")
		);

		return;
	}

	fcppt::io::istringstream iss(
		args_[1]
	);

	if(
		!fcppt::time::parse_date(
			iss,
			current_time_
		)
	)
		console_.print_line(
			FCPPT_TEXT("Day parsing failed.")
		);
}

void
sanguis::client::daytime_settings::change_time(
	sge::console::arg_list const &args_
)
{
	if(
		args_.size() != 2
	)
	{
		console_.print_line(
			FCPPT_TEXT("The time command needs one argument!")
		);

		return;
	}

	fcppt::io::istringstream iss(
		args_[1]
	);

	if(
		!fcppt::time::parse_time(
			iss,
			current_time_
		)
	)
		console_.print_line(
			FCPPT_TEXT("Time parsing failed.")
		);
}

void
sanguis::client::daytime_settings::change_time_speed(
	sge::console::arg_list const &args_
)
{
	if(
		args_.size() != 2
	)
	{
		console_.print_line(
			FCPPT_TEXT("The time_speed command needs one argument!")
		);

		return;
	}

	try
	{
		time_rep const speedup(
			fcppt::lexical_cast<
				time_rep
			>(
				args_[1]
			)
		);

		if(
			speedup < 1
		)
		{
			console_.print_line(
				FCPPT_TEXT("speedup needs to be > 0")
			);
		}

		speedup_ = speedup;

		time_begin_ = daytime_settings::now();
	}
	catch(
		fcppt::exception const &
	)
	{
		console_.print_line(
			FCPPT_TEXT("You need to pass an int argument to the time_speed command: ")
		);
	}
}

void
sanguis::client::daytime_settings::reset_day(
	sge::console::arg_list const &args_
)
{
	if(
		args_.size() == 1
	)
	{
		console_.print_line(
			FCPPT_TEXT("Dangling arguments for reset_day!")
		);

		return;
	}

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
	if(
		args_.size() == 1
	)
	{
		console_.print_line(
			FCPPT_TEXT("Dangling arguments for reset_time!")
		);

		return;
	}

	current_time_.tm_sec = invalid_value;
	current_time_.tm_min = invalid_value;
	current_time_.tm_hour = invalid_value;
}

sanguis::client::daytime_settings::time_point const
sanguis::client::daytime_settings::now()
{
	return clock::now();
}
