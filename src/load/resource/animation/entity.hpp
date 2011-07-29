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


#ifndef SANGUIS_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED

#include "entity_fwd.hpp"
#include <sge/time/unit.hpp>
#include <sge/time/duration.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/renderer/dim2.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
namespace animation
{

class entity
{
public:
	entity(
		sge::time::duration const &delay,
		sge::texture::const_part_ptr
	);

	sge::time::unit
	delay() const;

	sge::texture::const_part_ptr const
	tex() const;

	void
	tex(
		sge::texture::const_part_ptr
	);

	sge::renderer::dim2 const
	dim() const;
private:
	sge::time::unit delay_;

	sge::texture::const_part_ptr tex_;
};

}
}
}
}

#endif
