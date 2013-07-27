#ifndef SANGUIS_CREATOR_SPAWN_HPP_INCLUDED
#define SANGUIS_CREATOR_SPAWN_HPP_INCLUDED

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
		sanguis::creator::spawn_type
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::spawn_pos const
	pos() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::spawn_type
	type() const;
private:
	sanguis::creator::spawn_pos pos_;

	sanguis::creator::spawn_type type_;
};

}
}

#endif
