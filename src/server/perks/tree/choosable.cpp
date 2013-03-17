#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/equal.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


bool
sanguis::server::perks::tree::choosable(
	sanguis::server::perks::tree::object const &_tree,
	sanguis::perk_type const _perk,
	sanguis::server::level const _player_level
)
{
	typedef
	fcppt::container::tree::pre_order<
		sanguis::server::perks::tree::object const
	> traversal;

	traversal trav(
		_tree
	);

	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			sanguis::server::perks::tree::equal(
				_perk
			)
		)
	);

	if(
		it == trav.end()
	)
	{
		FCPPT_LOG_WARNING(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Perk not found in tree")
		);

		return false;
	}

	if(
		it->value().required_player_level().get()
		>
		_player_level.get()
	)
		return false;

	for(
		sanguis::server::perks::tree::object::const_optional_ref pos(
			*it
		);
		pos->has_parent();
		pos = pos->parent()
	)
	{
		sanguis::server::perks::tree::status const &cur_status(
			pos->value()
		);

		if(
			cur_status.required_parent_level().get()
			> pos->parent()->value().level().get()
		)
			return false;
	}

	return true;
}
