#ifndef SANGUIS_CREATOR_AUX_BRESENHAM_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_BRESENHAM_HPP_INCLUDED

#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace creator
{
namespace aux
{

template
<
	typename Callback
>
void
bresenham
(
	sanguis::creator::signed_pos const &_start,
	sanguis::creator::signed_pos const &_end,
	Callback const &_callback
)
{
	typedef
	sanguis::creator::signed_pos::value_type
	int_type;

	int_type x0 = static_cast<int_type>(_start.x());
	int_type y0 = static_cast<int_type>(_start.y());
	int_type x1 = static_cast<int_type>(_end.x());
	int_type y1 = static_cast<int_type>(_end.y());

#if 1
	bool const steep =
		std::abs(y1 - y0)
		>
		std::abs(x1 - x0);

	if (steep){
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int_type dx = x1 - x0;
	int_type dy = std::abs(y1 - y0);

	int_type D = 2 * dy - dx;
	_callback(
		sanguis::creator::signed_pos(
			x0,
			y0));

	int_type y = y0;

	for (int_type x = x0 + 1; x <= x1; ++x)
	{
		if (D > 0)
		{
			y++;
			if (steep)
				_callback(
					sanguis::creator::signed_pos(
						y,
						x));
			else
				_callback(
					sanguis::creator::signed_pos(
						x,
						y));
			D = D + (2*dy-2*dx);
		}
		else
		{
			if (steep)
				_callback(
					sanguis::creator::signed_pos(
						y,
						x));
			else
				_callback(
					sanguis::creator::signed_pos(
						x,
						y));
			D = D + (2*dy);
		}
	}
#else
	bool const steep =
		std::abs(y1 - y0)
		>
		std::abs(x1 - x0);

	if (steep){
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int_type const deltax = x1 - x0;
	int_type const deltay = std::abs(y1 - y0);
	int_type error = deltax / 2;
	int_type y = y0;
	int_type const ystep = (y0 < y1) ? 1 : -1;

	double length =
			static_cast<double>(x1 - x0) *
			static_cast<double>(x1 - x0) +
			static_cast<double>(y1 - y0) *
			static_cast<double>(y1 - y0);

	for (int_type x = x0; x <= x1; ++x)
	{
		double pos =
				static_cast<double>(x - x0) *
				static_cast<double>(x - x0) +
				static_cast<double>(y - y0) *
				static_cast<double>(y - y0);
		double t = std::sqrt(pos / length);

		if (steep)
		{
			_callback(
				sanguis::creator::signed_pos(
					y,
					x));
			_callback(
				sanguis::creator::signed_pos(
					y,
					x+1));
		}

		else
		{
			_callback(
				sanguis::creator::signed_pos(
					x,
					y));
			_callback(
				sanguis::creator::signed_pos(
					x+1,
					y));
		}


		error -= deltay;

		if (error < 0)
		{
			y += ystep;
			error += deltax;
		}
	}
#endif
}

}
}
}

#endif
