#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>


sanguis::creator::destructible::destructible(
	sanguis::creator::destructible_pos const _pos,
	sanguis::creator::destructible_type const _type
)
:
	pos_(
		_pos
	),
	type_(
		_type
	)
{
}

sanguis::creator::destructible_pos const
sanguis::creator::destructible::pos() const
{
	return
		pos_;
}

sanguis::creator::destructible_type
sanguis::creator::destructible::type() const
{
	return
		type_;
}
