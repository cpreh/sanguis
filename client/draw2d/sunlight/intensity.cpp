#include "intensity.hpp"
#include "time_to_gregorian.hpp"
#include "localtime.hpp"
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/rad_to_deg.hpp>
#include <fcppt/assert.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <algorithm>
#include <cmath>
#include <ctime>

sanguis::client::draw2d::sunlight::real
sanguis::client::draw2d::sunlight::intensity(
	std::time_t const current_time
)
{
	std::tm const current_tm(
		sunlight::localtime(
			current_time
		)
	);

	boost::gregorian::date const current(
		sunlight::time_to_gregorian(
			current_tm
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

	real const 
		hours = 
			static_cast<real>(current_tm.tm_hour),
		minutes = 
			static_cast<real>(current_tm.tm_min),
		lambda = 
			13.5,
		phi = 
			fcppt::math::deg_to_rad(52.5),
		fracminutes = 
			minutes/60.0,
		fracday = 
			((hours < 12.0 ? (12.0+hours) : (hours-12))+fracminutes)/24.0,
		n = 
			d.length().days() - (hours < 12.0 ? 1.0 : 0.0) + fracday,
		L = 
			(std::fmod(280.460+0.9856474*n,360.0)),
		g = 
			fcppt::math::deg_to_rad(std::fmod(357.528+0.9856003*n,360.0)),
		ekliptik =
			fcppt::math::deg_to_rad(L + 1.915 * std::sin(g) + 0.020 * std::sin(2.0*g)),
		e = 
			fcppt::math::deg_to_rad(23.439-0.0000004*n),
		alpha_arg = 
			std::cos(e)*std::sin(ekliptik)/std::cos(ekliptik),
		alpha_raw = 
			fcppt::math::rad_to_deg(std::atan(alpha_arg)),
		alpha =
			alpha_raw + (std::cos(ekliptik) < 0.0 ? 180.0 : 0.0),
		delta = 
			std::asin(std::sin(e)*std::sin(ekliptik)),
		t0 = 
				//(current.julian_day()-2451545.0)/36525.0,
			((current.julian_day() - 1 + 0.5)-2451545.0)/36525.0,
		sternzeit = 
			std::fmod(
				6.697376
				+ 2400.05134
				* t0
				+ 1.002738
				* (hours + fracminutes),
				24.0
			),
		sternzeit_k = 
			sternzeit*15.0,
		stw = 
			sternzeit_k + lambda,
		tau = 
			fcppt::math::deg_to_rad(stw - alpha),
		h = 
			fcppt::math::rad_to_deg(
				std::asin(
					std::cos(delta)
					* std::cos(tau)
					* std::cos(phi)
					+ std::sin(delta)
					* std::sin(phi)
				)
			),
		R = 
			1.02/std::tan(fcppt::math::deg_to_rad(h + 10.3/(h+5.11))),
		hr = 
			h + R/60.0,
		result =
			std::max(
				static_cast<real>(0),
				std::sin(
					fcppt::math::deg_to_rad(
						hr
					)
				)
			);
	
	FCPPT_ASSERT(
		0. <= result
		&& result <= 1.0
	);

	return result;
}
