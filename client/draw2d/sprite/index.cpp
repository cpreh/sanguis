#include "sprite_part_index.hpp"

sanguis::draw::sprite_part_index::sprite_part_index(
	value_type const value)
:
	value(value)
{}

sanguis::draw::sprite_part_index::value_type
sanguis::draw::sprite_part_index::get() const
{
	return value;
}
