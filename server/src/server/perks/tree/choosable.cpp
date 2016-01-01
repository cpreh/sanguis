#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/find_node.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>


bool
sanguis::server::perks::tree::choosable(
	sanguis::server::perks::tree::container const &_tree,
	sanguis::perk_type const _perk,
	sanguis::server::level const _player_level
)
{
	return
		fcppt::optional::maybe(
			sanguis::server::perks::tree::find_node(
				_tree,
				_perk
			),
			[]{
				FCPPT_LOG_WARNING(
					sanguis::server::log(),
					fcppt::log::_
						<< FCPPT_TEXT("Perk not found in tree")
				);

				return
					false;
			},
			[
				_player_level
			](
				sanguis::server::perks::tree::object const &_node
			)
			{
				{
					sanguis::server::perks::tree::status const &current(
						_node.value()
					);

					if(
						current.required_player_level().get()
						>
						_player_level.get()
						||
						current.level().get()
						==
						current.max_level().get()
					)
						return
							false;
				}

				// TODO: Do this differently
				for(
					sanguis::server::perks::tree::object::const_optional_ref pos(
						_node
					);
					pos.get_unsafe().has_parent();
					pos = pos.get_unsafe().parent()
				)
				{
					sanguis::server::perks::tree::status const &cur_status(
						pos.get_unsafe().value()
					);

					if(
						cur_status.required_parent_level().get()
						>
						pos.get_unsafe().parent().get_unsafe().value().level().get()
					)
						return
							false;
				}

				return
					true;
			}
		);
}
