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


#ifndef SANGUIS_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED

#include "series_fwd.hpp"
#include "entity.hpp"
#include "entity_vector.hpp"
#include <sge/renderer/dim2.hpp>
#include <vector>

namespace sanguis
{
namespace load
{
namespace resource
{
namespace animation
{

class series
{
public:
	typedef animation::entity_vector::const_iterator const_iterator;

	series();

	explicit series(
		entity_vector const &
	);

	void
	push_back(
		entity const &
	);

	entity_vector &
	entities();

	entity_vector const &
	entities() const;

	const_iterator
	begin() const;

	const_iterator
	end() const;

	bool
	empty() const;
private:
	animation::entity_vector entities_;
};

}
}
}
}

#endif
