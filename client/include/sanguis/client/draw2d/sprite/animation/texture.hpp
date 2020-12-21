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


#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_TEXTURE_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture_fwd.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sanguis/client/load/resource/animation/series_cref.hpp>
#include <sge/texture/const_part_ref_fwd.hpp>
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

class texture
{
	FCPPT_NONCOPYABLE(
		texture
	);
public:
	texture(
		sanguis::client::load::resource::animation::series_cref,
		sanguis::client::draw2d::sprite::animation::loop_method,
		sanguis::diff_clock_cref
	);

	texture(
		texture &&
	)
	noexcept;

	texture &
	operator=(
		texture &&
	)
	noexcept;

	~texture();

	[[nodiscard]]
	sge::texture::const_part_ref
	current_texture();

	[[nodiscard]]
	bool
	ended() const;
private:
	sanguis::client::load::resource::animation::series_cref series_;

	sanguis::client::draw2d::sprite::animation::loop_method loop_method_;

	sanguis::client::load::resource::animation::series::const_iterator pos_;

	sanguis::diff_timer cur_timer_;
};

}
}
}
}
}

#endif
