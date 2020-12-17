#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::creator::destructible::destructible(
	sanguis::creator::destructible_pos _pos,
	sanguis::creator::destructible_type const _type
)
:
	pos_(
		std::move(
			_pos
		)
	),
	type_(
		_type
	)
{
}

sanguis::creator::destructible_pos
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
