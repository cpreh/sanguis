#include <sanguis/server/perks/tree/create.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <sanguis/server/perks/tree/object_unique_ptr.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::perks::tree::object_unique_ptr
sanguis::server::perks::tree::create()
{
	// dummy head
	tree::object_unique_ptr ret(
		fcppt::make_unique_ptr<
			tree::object
		>(
			tree::status(
				perk_type::size,
				tree::required_player_level(
					0u
				),
				tree::required_parent_level(
					0u
				),
				tree::max_level(
					0u
				)
			)
		)
	);

	ret->push_back(
		tree::status(
			perk_type::choleric,
			tree::required_player_level(
				2u
			),
			tree::required_parent_level(
				0u
			),
			tree::max_level(
				10u
			)
		)
	);

	ret->push_back(
		tree::status(
			perk_type::ias,
			tree::required_player_level(
				0u
			),
			tree::required_parent_level(
				0u
			),
			tree::max_level(
				8U
			)
		)
	);

	ret->push_back(
		tree::status(
			perk_type::ims,
			tree::required_player_level(
				0u
			),
			tree::required_parent_level(
				0u
			),
			tree::max_level(
				7u
			)
		)
	);

	ret->push_back(
		tree::status(
			perk_type::irs,
			tree::required_player_level(
				0u
			),
			tree::required_parent_level(
				0u
			),
			tree::max_level(
				4u
			)
		)
	);

	ret->push_back(
		tree::status(
			perk_type::health,
			tree::required_player_level(
				0u
			),
			tree::required_parent_level(
				0u
			),
			tree::max_level(
				10u
			)
		)
	);

	tree::object &health(
		ret->back()
	);

	health.push_back(
		tree::status(
			perk_type::regeneration,
			tree::required_player_level(
				0u
			),
			tree::required_parent_level(
				2u
			),
			tree::max_level(
				3u
			)
		)
	);

	return
		move(
			ret
		);
}
