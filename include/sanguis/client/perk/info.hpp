#ifndef SANGUIS_CLIENT_PERK_INFO_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_INFO_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/info_fwd.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/max_level.hpp>
#include <sanguis/client/perk/required_parent_level.hpp>
#include <sanguis/client/perk/required_player_level.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

class info
{
public:
	explicit
	info(
		sanguis::perk_type
	);

	info(
		sanguis::perk_type,
		sanguis::client::perk::level,
		sanguis::client::perk::required_parent_level,
		sanguis::client::perk::required_player_level,
		sanguis::client::perk::max_level
	);

	void
	increment_level();

	sanguis::perk_type
	perk_type() const;

	sanguis::client::perk::level const
	level() const;

	sanguis::client::perk::required_parent_level const
	required_parent_level() const;

	sanguis::client::perk::required_player_level const
	required_player_level() const;

	sanguis::client::perk::max_level const
	max_level() const;
private:
	sanguis::perk_type type_;

	sanguis::client::perk::level level_;

	sanguis::client::perk::required_parent_level required_parent_level_;

	sanguis::client::perk::required_player_level required_player_level_;

	sanguis::client::perk::max_level max_level_;
};

}
}
}

#endif
