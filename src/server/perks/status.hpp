#ifndef SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED

#include "required_player_level.hpp"
#include "required_parent_level.hpp"
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
		perks::required_player_level,
		perks::required_parent_level
	);
	
	void
	choose();

	perks::required_player_level const
	required_player_level() const;

	perks::required_parent_level const
	required_parent_level() const;

	server::level const
	level() const;

	perk_type::type
	type() const;
private:
	perk_type::type type_;

	perks::required_player_level required_player_level_;

	perks::required_parent_level required_parent_level_;

	server::level level_;
};

}
}
}

#endif
