#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::creator::spawn::spawn(
	sanguis::creator::spawn_pos _pos,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::creator::spawn_type const _spawn_type,
	sanguis::creator::enemy_kind const _enemy_kind
)
:
	pos_{
		std::move(
			_pos
		)
	},
	enemy_type_{
		_enemy_type
	},
	spawn_type_{
		_spawn_type
	},
	enemy_kind_{
		_enemy_kind
	}
{
}

sanguis::creator::spawn_pos
sanguis::creator::spawn::pos() const
{
	return
		pos_;
}

sanguis::creator::enemy_type
sanguis::creator::spawn::enemy_type() const
{
	return
		enemy_type_;
}

sanguis::creator::spawn_type
sanguis::creator::spawn::spawn_type() const
{
	return
		spawn_type_;
}

sanguis::creator::enemy_kind
sanguis::creator::spawn::enemy_kind() const
{
	return
		enemy_kind_;
}
