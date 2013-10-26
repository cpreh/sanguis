#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/create.hpp>
#include <sanguis/server/perks/tree/max_level.hpp>
#include <sanguis/server/perks/tree/object_unique_ptr.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/optional_status.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <sanguis/server/perks/tree/required_parent_level.hpp>
#include <sanguis/server/perks/tree/required_player_level.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::perks::tree::object_unique_ptr
sanguis::server::perks::tree::create()
{
	// dummy head
	sanguis::server::perks::tree::object_unique_ptr ret(
		fcppt::make_unique_ptr<
			sanguis::server::perks::tree::object
		>(
			sanguis::server::perks::tree::optional_status()
		)
	);

	ret->push_back(
		sanguis::server::perks::tree::optional_status(
			sanguis::server::perks::tree::status(
				sanguis::perk_type::choleric,
				sanguis::server::perks::tree::required_player_level(
					2u
				),
				sanguis::server::perks::tree::required_parent_level(
					0u
				),
				sanguis::server::perks::tree::max_level(
					10u
				)
			)
		)
	);

	ret->push_back(
		sanguis::server::perks::tree::optional_status(
			sanguis::server::perks::tree::status(
				sanguis::perk_type::ias,
				sanguis::server::perks::tree::required_player_level(
					0u
				),
				sanguis::server::perks::tree::required_parent_level(
					0u
				),
				sanguis::server::perks::tree::max_level(
					8U
				)
			)
		)
	);

	ret->push_back(
		sanguis::server::perks::tree::optional_status(
			sanguis::server::perks::tree::status(
				sanguis::perk_type::ims,
				sanguis::server::perks::tree::required_player_level(
					0u
				),
				sanguis::server::perks::tree::required_parent_level(
					0u
				),
				sanguis::server::perks::tree::max_level(
					7u
				)
			)
		)
	);

	ret->push_back(
		sanguis::server::perks::tree::optional_status(
			sanguis::server::perks::tree::status(
				sanguis::perk_type::irs,
				sanguis::server::perks::tree::required_player_level(
					0u
				),
				sanguis::server::perks::tree::required_parent_level(
					0u
				),
				sanguis::server::perks::tree::max_level(
					4u
				)
			)
		)
	);

	ret->push_back(
		sanguis::server::perks::tree::optional_status(
			sanguis::server::perks::tree::status(
				sanguis::perk_type::health,
				sanguis::server::perks::tree::required_player_level(
					0u
				),
				sanguis::server::perks::tree::required_parent_level(
					0u
				),
				sanguis::server::perks::tree::max_level(
					10u
				)
			)
		)
	);

	sanguis::server::perks::tree::object &health(
		ret->back()
	);

	health.push_back(
		sanguis::server::perks::tree::optional_status(
			sanguis::server::perks::tree::status(
				sanguis::perk_type::regeneration,
				sanguis::server::perks::tree::required_player_level(
					0u
				),
				sanguis::server::perks::tree::required_parent_level(
					10u
				),
				sanguis::server::perks::tree::max_level(
					3u
				)
			)
		)
	);

	return
		std::move(
			ret
		);
}
