#include "create.hpp"
#include "status.hpp"
#include <fcppt/container/tree/object_impl.hpp>

sanguis::server::perks::tree::object const
sanguis::server::perks::tree::create()
{
	tree::object ret;

	// TODO: do this with assign::
	ret.push_back(
		tree::status(
			perk_type::choleric,
			tree::required_player_level(
				2
			),
			tree::required_parent_level(
				0
			)
		)
	);
	ret.push_back(
		tree::status(
			perk_type::ias,
			tree::required_player_level(
				0
			),
			tree::required_parent_level(
				0
			)
		)
	);
	ret.push_back(
		tree::status(
			perk_type::ims,
			tree::required_player_level(
				0
			),
			tree::required_parent_level(
				0
			)
		)
	);
	ret.push_back(
		tree::status(
			perk_type::irs,
			tree::required_player_level(
				0
			),
			tree::required_parent_level(
				0
			)
		)
	);
	ret.push_back(
		tree::status(
			perk_type::health,
			tree::required_player_level(
				0
			),
			tree::required_parent_level(
				0
			)
		)
	);

	tree::object &health(
		ret.back()
	);

	health.push_back(
		tree::status(
			perk_type::regeneration,
			tree::required_player_level(
				0
			),
			tree::required_parent_level(
				2
			)
		)
	);

	return ret;
}
