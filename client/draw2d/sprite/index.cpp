#include "index.hpp"

sanguis::client::draw2d::sprite::index::index(
	value_type const value
)
:
	value(value)
{}

sanguis::client::draw2d::sprite::index::value_type
sanguis::client::draw2d::sprite::index::get() const
{
	return value;
}
