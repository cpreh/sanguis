#ifndef SANGUIS_CREATOR_SPAWN_HPP_INCLUDED
#define SANGUIS_CREATOR_SPAWN_HPP_INCLUDED

#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/spawn_fwd.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/symbol.hpp>


namespace sanguis
{
namespace creator
{

class spawn
{
public:
	spawn(
		sanguis::creator::spawn_pos,
		sanguis::creator::enemy_type,
		sanguis::creator::spawn_type,
		sanguis::creator::enemy_kind
	);

	[[nodiscard]]
	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::spawn_pos
	pos() const;

	[[nodiscard]]
	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::enemy_type
	enemy_type() const;

	[[nodiscard]]
	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::spawn_type
	spawn_type() const;

	[[nodiscard]]
	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::enemy_kind
	enemy_kind() const;
private:
	sanguis::creator::spawn_pos pos_;

	sanguis::creator::enemy_type enemy_type_;

	sanguis::creator::spawn_type spawn_type_;

	sanguis::creator::enemy_kind enemy_kind_;
};

}
}

#endif
