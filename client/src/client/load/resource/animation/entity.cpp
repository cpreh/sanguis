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


#include <sanguis/duration.hpp>
#include <sanguis/client/load/resource/animation/entity.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part.hpp>


sanguis::client::load::resource::animation::entity::entity(
	sanguis::duration const &_res,
	sge::texture::const_part_shared_ptr const _tex_part
)
:
	delay_(
		_res.count()
	),
	tex_part_(
		_tex_part
	)
{
}

sanguis::duration const
sanguis::client::load::resource::animation::entity::delay() const
{
	return delay_;
}

sge::texture::const_part_shared_ptr
sanguis::client::load::resource::animation::entity::tex() const
{
	return tex_part_;
}

void
sanguis::client::load::resource::animation::entity::tex(
	sge::texture::const_part_shared_ptr const _tex_part
)
{
	tex_part_ = _tex_part;
}

sge::renderer::dim2 const
sanguis::client::load::resource::animation::entity::dim() const
{
	return tex_part_->area().size();
}
