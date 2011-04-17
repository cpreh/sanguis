#ifndef SANGUIS_CLIENT_PERK_INFO_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_INFO_HPP_INCLUDED

#include "max_level.hpp"
#include "required_parent_level.hpp"
#include "required_player_level.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace client
{
namespace perk
{

class info
{
public:
	info();

	explicit info(
		sanguis::perk_type::type
	);

	info(
		sanguis::perk_type::type,
		perk::required_parent_level,
		perk::required_player_level,
		perk::max_level
	);

	perk_type::type
	type() const;

	perk::required_parent_level const
	required_parent_level() const;

	perk::required_player_level const
	required_player_level() const;

	perk::max_level const
	max_level() const;
private:
	sanguis::perk_type::type type_;

	perk::required_parent_level required_parent_level_;

	perk::required_player_level required_player_level_;

	perk::max_level max_level_;
};

}
}
}

#endif
