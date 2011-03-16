#ifndef SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED

#include "level_type.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class status
{
public:
	status();

	status(
		perk_type::type,
		level_type required_player_level,
		level_type required_parent_level
	);
	
	void
	choose();

	level_type
	required_player_level() const;

	level_type
	required_parent_level() const;

	level_type
	level() const;

	perk_type::type
	type() const;
private:
	perk_type::type type_;

	level_type
		required_player_level_,
		required_parent_level_,
		level_;
};

}
}
}

#endif
