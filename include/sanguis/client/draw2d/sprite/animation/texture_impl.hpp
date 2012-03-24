/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_TEXTURE_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_TEXTURE_IMPL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/animation/texture_decl.hpp>
#include <sanguis/exception.hpp>
#include <sge/sprite/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>

template<
	typename Choices
>
sanguis::client::draw2d::sprite::animation::texture<Choices>::texture(
	sanguis::load::resource::animation::series const &_series,
	animation::loop_method::type const _action,
	object &_spr,
	sanguis::diff_clock const &_diff_clock
)
:
	series_(_series),
	action_(_action),
	cur_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
				0
			)
		)
	),
	spr_(_spr),
	pos_(series_.begin())
{
	if(
		series_.empty()
	)
		throw sanguis::exception(
			FCPPT_TEXT("animation::texture series is empty!")
		);

	reset();
}

template<
	typename Choices
>
bool
sanguis::client::draw2d::sprite::animation::texture<Choices>::process()
{
	if(
		!cur_timer_.expired()
	)
		return false;

	if(
		boost::next(pos_) == series_.end()
	)
	{
		handle_end();
		return true;
	}

	++pos_;

	cur_timer_.interval(
		pos_->delay()
	);

	spr_.texture(
		pos_->tex()
	);

	return false;
}

template<
	typename Choices
>
void
sanguis::client::draw2d::sprite::animation::texture<Choices>::reset()
{
	spr_.texture(
		series_.begin()->tex()
	);

	pos_ = series_.begin();

	cur_timer_.interval(
		series_.begin()->delay()
	);
}

template<
	typename Choices
>
sanguis::load::resource::animation::series const &
sanguis::client::draw2d::sprite::animation::texture<Choices>::series() const
{
	return series_;
}

template<
	typename Choices
>
void
sanguis::client::draw2d::sprite::animation::texture<Choices>::handle_end()
{
	switch(
		action_
	)
	{
	case animation::loop_method::repeat:
		reset();
		return;
	case animation::loop_method::stop_at_end:
		return;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid loop_method!")
	);
}

#endif
