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
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::resource::animation::entity::entity(
	sanguis::duration const _delay,
	sge::texture::const_part_unique_ptr &&_texture
)
:
	delay_(
		_delay
	),
	texture_(
		std::move(
			_texture
		)
	)
{
}

sanguis::client::load::resource::animation::entity::entity(
	entity &&
)
noexcept
= default;

sanguis::client::load::resource::animation::entity &
sanguis::client::load::resource::animation::entity::operator=(
	entity &&
)
noexcept
= default;

sanguis::client::load::resource::animation::entity::~entity()
= default;

sanguis::duration
sanguis::client::load::resource::animation::entity::delay() const
{
	return
		delay_;
}

sge::texture::part const &
sanguis::client::load::resource::animation::entity::texture() const
{
	return
		*texture_;
}

sge::renderer::dim2
sanguis::client::load::resource::animation::entity::dim() const
{
	return
		this->texture().area().size();
}
