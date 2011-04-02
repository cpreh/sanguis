#ifndef SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED

#include "../level.hpp"
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
		server::level required_player_level,
		server::level required_parent_level
	);
	
	void
	choose();

	server::level const
	required_player_level() const;

	server::level const
	required_parent_level() const;

	server::level const
	level() const;

	perk_type::type
	type() const;
private:
	perk_type::type type_;

	server::level
		required_player_level_,
		required_parent_level_,
		level_;
};

}
}
}

#endif
