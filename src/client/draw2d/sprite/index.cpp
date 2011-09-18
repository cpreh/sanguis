#include <sanguis/client/draw2d/sprite/index.hpp>

sanguis::client::draw2d::sprite::index::index(
	value_type const _value
)
:
	value_(_value)
{}

sanguis::client::draw2d::sprite::index::value_type
sanguis::client::draw2d::sprite::index::get() const
{
	return value_;
}
