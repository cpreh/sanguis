#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/find_node.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>


bool
sanguis::server::perks::tree::choosable(
	sanguis::server::perks::tree::container const &_tree,
	sanguis::perk_type const _perk,
	sanguis::server::level const _player_level
)
{
	sanguis::server::perks::tree::object::const_optional_ref const node(
		sanguis::server::perks::tree::find_node(
			_tree,
			_perk
		)
	);

	if(
		!node
	)
	{
		FCPPT_LOG_WARNING(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Perk not found in tree")
		);

		return
			false;
	}

	{
		sanguis::server::perks::tree::status const &current(
			node->value()
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

	for(
		sanguis::server::perks::tree::object::const_optional_ref pos(
			node
		);
		pos->has_parent();
		pos = pos->parent()
	)
	{
		sanguis::server::perks::tree::status const &cur_status(
			pos->value()
		);

		sanguis::server::perks::tree::object::const_optional_ref const parent(
			pos->parent()
		);

		if(
			parent.has_value()
			&&
			cur_status.required_parent_level().get()
			>
			parent->value().level().get()
		)
			return
				false;
	}

	return
		true;
}
