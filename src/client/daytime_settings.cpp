#include <sanguis/client/daytime_settings.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/to_fcppt_string.hpp>
#include <fcppt/chrono/system_clock.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>
#include <fcppt/chrono/time_point_impl.hpp>
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/time/gmtime.hpp>
#include <fcppt/time/parse_date.hpp>
#include <fcppt/time/parse_time.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>

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
		T const &_t
	) const
	{

		int &dest(
			boost::fusion::at_c<0>(
				_t
			)
		);

		int const &src(
			boost::fusion::at_c<1>(
				_t
			)
		);

		if(
			dest  == invalid_value
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
	sge::console::object &_console
)
:
	time_begin_(
		daytime_settings::now()
	),
	speedup_(1),
	day_con_(
		_console.insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&daytime_settings::change_day,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("day")
				)
			)
			.short_description(
				SGE_FONT_TEXT_LIT("Sets the current day to a fixed value.")
			)
		)
	),
	time_con_(
		_console.insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&daytime_settings::change_time,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("time")
				)
			)
			.short_description(
				SGE_FONT_TEXT_LIT("Sets the current time to a fixed value.")
			)
		)
	),
	time_speed_con_(
		_console.insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&daytime_settings::change_time_speed,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("time_speed")
				)
			)
			.short_description(
				SGE_FONT_TEXT_LIT("Sets the current time speedup. Use a value of 1 to reset this.")
			)
		)
	),
	reset_day_con_(
		_console.insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&daytime_settings::reset_day,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("reset_day")
				)
			)
			.short_description(
				SGE_FONT_TEXT_LIT("Resets to the current day.")
			)
		)
	),
	reset_time_con_(
		_console.insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&daytime_settings::reset_time,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("reset_time")
				)
			)
			.short_description(
				SGE_FONT_TEXT_LIT("Resets to the current time.")
			)
		)
	)
{
	boost::fusion::for_each(
		current_time_,
		boost::phoenix::arg_names::arg1 = invalid_value
	);
}

sanguis::client::daytime_settings::~daytime_settings()
{
}

std::tm const
sanguis::client::daytime_settings::current_time()
{
	time_point const time_now(
		daytime_settings::now()
	);

	std::tm const local_time(
		fcppt::time::gmtime(
			clock::to_time_t(
				time_begin_
				+ (
					time_now
					- time_begin_
				)
				* speedup_
			)
		)
	);

	std::tm result_time(
		current_time_
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
				result_time,
				local_time
			)
		),
		overwrite_members()
	);

	return result_time;
}

void
sanguis::client::daytime_settings::change_day(
	sge::console::arg_list const &_args,
	sge::console::object &_object
)
{
	if(
		_args.size() != 2
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("The date command needs one argument!")
		);

		return;
	}

	fcppt::io::istringstream iss(
		sge::font::text::to_fcppt_string(
			_args[1]
		)
	);

	if(
		!fcppt::time::parse_date(
			iss,
			current_time_
		)
	)
		_object.emit_error(
			SGE_FONT_TEXT_LIT("Day parsing failed.")
		);
}

void
sanguis::client::daytime_settings::change_time(
	sge::console::arg_list const &_args,
	sge::console::object &_object
)
{
	if(
		_args.size() != 2
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("The time command needs one argument!")
		);

		return;
	}

	fcppt::io::istringstream iss(
		sge::font::text::to_fcppt_string(
			_args[1]
		)
	);

	if(
		!fcppt::time::parse_time(
			iss,
			current_time_
		)
	)
		_object.emit_error(
			SGE_FONT_TEXT_LIT("Time parsing failed.")
		);
}

void
sanguis::client::daytime_settings::change_time_speed(
	sge::console::arg_list const &_args,
	sge::console::object &_object
)
{
	if(
		_args.size() != 2
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("The time_speed command needs one argument!")
		);

		return;
	}

	typedef fcppt::optional<
		time_rep
	> optional_time_rep;


	optional_time_rep const opt_speedup(
		fcppt::extract_from_string<
			time_rep
		>(
			_args[1]
		)
	);

	if(
		!opt_speedup
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("You need to pass an int argument to the time_speed command: ")
		);

		return;
	}

	time_rep const speedup(
		*opt_speedup
	);

	if(
		speedup < 1
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("speedup needs to be > 0")
		);

		return;
	}

	speedup_ = speedup;

	time_begin_ = daytime_settings::now();
}

void
sanguis::client::daytime_settings::reset_day(
	sge::console::arg_list const &_args,
	sge::console::object &_object
)
{
	if(
		_args.size() == 2
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("Dangling arguments for reset_day!")
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
	sge::console::arg_list const &_args,
	sge::console::object &_object
)
{
	if(
		_args.size() == 2
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("Dangling arguments for reset_time!")
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
