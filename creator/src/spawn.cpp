#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>


sanguis::creator::spawn::spawn(
	sanguis::creator::spawn_pos const _pos,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::creator::spawn_type const _spawn_type
)
:
	pos_(
		_pos
	),
	enemy_type_(
		_enemy_type
	),
	spawn_type_(
		_spawn_type
	)
{
}

sanguis::creator::spawn_pos const
sanguis::creator::spawn::pos() const
{
	return pos_;
}

sanguis::creator::enemy_type
sanguis::creator::spawn::enemy_type() const
{
	return enemy_type_;
}

sanguis::creator::spawn_type
sanguis::creator::spawn::spawn_type() const
{
	return spawn_type_;
}
