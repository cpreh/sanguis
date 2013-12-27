#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/sunlight/real.hpp>
#include <sanguis/client/draw2d/sunlight/sun_angle.hpp>
#include <sanguis/client/draw2d/sunlight/time_to_gregorian.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/rad_to_deg.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <cmath>
#include <ctime>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::sunlight::real
sanguis::client::draw2d::sunlight::sun_angle(
	std::tm const &_current_tm
)
{
	boost::gregorian::date const current(
		sanguis::client::draw2d::sunlight::time_to_gregorian(
			_current_tm
		)
	);

	boost::gregorian::date const equinox(
		2000,
		boost::gregorian::Jan,
		1
	);

	boost::gregorian::date_period const d(
		equinox,
		current
	);

	sanguis::client::draw2d::sunlight::real const
		hours =
			fcppt::cast::int_to_float<
				sanguis::client::draw2d::sunlight::real
			>(
				_current_tm.tm_hour
			),
		minutes =
			fcppt::cast::int_to_float<
				sanguis::client::draw2d::sunlight::real
			>(
				_current_tm.tm_min
			),
		lambda =
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				7.990
			),
		phi =
			fcppt::math::deg_to_rad(
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					52.2493
				)
			),
		fracminutes =
			minutes
			/
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				60
			),
		fracday =
			(
				(
					hours
					<
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						12
					)
					?
						(
							fcppt::literal<
								sanguis::client::draw2d::sunlight::real
							>(
								12
							)
							+
							hours
						)
					:
						(
							hours
							-
							fcppt::literal<
								sanguis::client::draw2d::sunlight::real
							>(
								12
							)
						)
						+
						fracminutes
				)
				/
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					24
				)
			),
		n =
			fcppt::cast::int_to_float<
				sanguis::client::draw2d::sunlight::real
			>(
				d.length().days()
			)
			-
			(
				hours
				<
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					12
				)
				?
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						1
					)
				:
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						0
					)
				+
				fracday
			),
		L =
			std::fmod(
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					280.460
				)
				+
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					0.9856474
				)
				*
				n,
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					360
				)
			),
		g =
			fcppt::math::deg_to_rad(
				std::fmod(
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						357.528
					)
					+
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						0.9856003
					)
					*
					n,
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						360
					)
				)
			),
		ekliptik =
			fcppt::math::deg_to_rad(
				L
				+
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					1.915
				)
				*
				std::sin(
					g
				)
				+
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					0.020
				)
				*
				std::sin(
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						2.0
					)
					*
					g
				)
			),
		e =
			fcppt::math::deg_to_rad(
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					23.439
				)
				-
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					0.0000004
				)
				*
				n
			),
		alpha_arg =
			std::cos(
				e
			)
			*
			std::sin(
				ekliptik
			)
			/
			std::cos(
				ekliptik
			),
		alpha_raw =
			fcppt::math::rad_to_deg(
				std::atan(
					alpha_arg
				)
			),
		alpha =
			alpha_raw
			+
			(
				std::cos(
					ekliptik
				)
				<
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					0
				)
				?
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						180.0
					)
				:
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						0.0
					)
			),
		delta =
			std::asin(
				std::sin(
					e
				)
				*
				std::sin(
					ekliptik
				)
			),
		t0 =
				//(current.julian_day()-2451545.0)/36525.0,
			(
				current.julian_day()
				-
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					1
				)
				+
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					0.5
				)
				-
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					2451545
				)
			)
			/
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				36525.0
			),
		sternzeit =
			std::fmod(
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					6.697376
				)
				+
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					2400.05134
				)
				*
				t0
				+
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					1.002738
				)
				*
				(
					hours
					+
					fracminutes
				),
				fcppt::literal<
					sanguis::client::draw2d::sunlight::real
				>(
					24
				)
			),
		sternzeit_k =
			sternzeit
			*
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				15
			),
		stw =
			sternzeit_k
			+
			lambda,
		tau =
			fcppt::math::deg_to_rad(
				stw
				-
				alpha
			),
		h =
			fcppt::math::rad_to_deg(
				std::asin(
					std::cos(
						delta
					)
					*
					std::cos(
						tau
					)
					*
					std::cos(
						phi
					)
					+
					std::sin(
						delta
					)
					*
					std::sin(
						phi
					)
				)
			),
		R =
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				1.02
			)
			/
			std::tan(
				fcppt::math::deg_to_rad(
					h
					+
					fcppt::literal<
						sanguis::client::draw2d::sunlight::real
					>(
						10.3
					)
					/
					(
						h
						+
						fcppt::literal<
							sanguis::client::draw2d::sunlight::real
						>(
							5.11
						)
					)
				)
			),
		hr =
			h
			+
			R
			/
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				60
			),
		hr_rad =
			fcppt::math::deg_to_rad(
				hr
			),
		half_pi(
			fcppt::math::pi<
				real
			>()
			/
			fcppt::literal<
				sanguis::client::draw2d::sunlight::real
			>(
				2
			)
		);

	if(
		hr_rad
		<
		-half_pi
		||
		hr_rad
		>
		half_pi
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::client::draw2d::log(),
			fcppt::log::_
				<< FCPPT_TEXT("sun angle out of range: ")
				<< hr_rad
		)
	}

	return
		hr_rad;
}
