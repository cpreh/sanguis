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


#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_TEXTURE_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_TEXTURE_DECL_HPP_INCLUDED

#include "texture_fwd.hpp"
#include "loop_method.hpp"
#include "../../../../load/resource/animation/series.hpp"
#include <sge/sprite/object_fwd.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/callback.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace animation
{

template<
	typename Choices
>
class texture
{
	FCPPT_NONCOPYABLE(
		texture
	);
public:
	typedef sge::sprite::object<
		Choices
	> object;

	texture(
		load::resource::animation::series const &,
		sprite::animation::loop_method::type,
		object &init_sprite,
		sge::time::callback const &time_fun
	);

	bool
	process();

	void
	reset();

	load::resource::animation::series const &
	series() const;
private:
	void
	handle_end();

	load::resource::animation::series series_;

	sprite::animation::loop_method::type action_;

	sge::time::timer cur_timer_;

	object &spr_;

	load::resource::animation::series::const_iterator pos_;
};

}
}
}
}
}

#endif
