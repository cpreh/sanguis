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


#include "entity.hpp"
#include <sge/texture/part.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/chrono/duration_impl.hpp>

sanguis::load::resource::animation::entity::entity(
	sanguis::duration const &_res,
	sge::texture::const_part_ptr const _tex
)
:
	delay_(_res.count()),
	tex_(_tex)
{
}

sanguis::duration const
sanguis::load::resource::animation::entity::delay() const
{
	return delay_;
}

sge::texture::const_part_ptr const
sanguis::load::resource::animation::entity::tex() const
{
	return tex_;
}

void
sanguis::load::resource::animation::entity::tex(
	sge::texture::const_part_ptr const _tex
)
{
	tex_ = _tex;
}

sge::renderer::dim2 const
sanguis::load::resource::animation::entity::dim() const
{
	return tex_->area().size();
}
