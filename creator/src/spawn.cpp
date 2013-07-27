#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>


sanguis::creator::spawn::spawn(
	sanguis::creator::spawn_pos const _pos,
	sanguis::creator::spawn_type const _type
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

sanguis::creator::spawn_pos const
sanguis::creator::spawn::pos() const
{
	return pos_;
}

sanguis::creator::spawn_type
sanguis::creator::spawn::type() const
{
	return type_;
}
