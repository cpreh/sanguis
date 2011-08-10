#ifndef SANGUIS_SERVER_PERKS_TREE_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_STATUS_HPP_INCLUDED

#include "status_fwd.hpp"
#include "max_level.hpp"
#include "required_player_level.hpp"
#include "required_parent_level.hpp"
#include "../../level.hpp"
#include "../../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

class status
{
public:
	status(
		perk_type::type,
		tree::required_player_level,
		tree::required_parent_level,
		tree::max_level
	);

	void
	choose();

	tree::required_player_level const
	required_player_level() const;

	tree::required_parent_level const
	required_parent_level() const;

	tree::max_level const
	max_level() const;

	server::level const
	level() const;

	perk_type::type
	type() const;
private:
	perk_type::type type_;

	tree::required_player_level required_player_level_;

	tree::required_parent_level required_parent_level_;

	tree::max_level max_level_;

	server::level level_;
};

}
}
}
}

#endif
