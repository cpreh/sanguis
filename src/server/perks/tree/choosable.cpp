#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/equal.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <sanguis/server/log.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

bool
sanguis::server::perks::tree::choosable(
	tree::object const &_tree,
	sanguis::perk_type::type const _perk,
	server::level const _player_level
)
{
	if(
		_perk == perk_type::size
	)
		return false;

	typedef
	fcppt::container::tree::pre_order<
		tree::object const
	> traversal;

	traversal trav(
		_tree
	);

	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			tree::equal(
				_perk
			)
		)
	);

	if(
		it == trav.end()
	)
	{
		FCPPT_LOG_WARNING(
			server::log(),
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
		tree::object const *pos(&*it);
		pos->has_parent();
		pos = &pos->parent()
	)
	{
		tree::status const &cur_status(
			pos->value()
		);

		if(
			cur_status.required_parent_level().get()
			> pos->parent().value().level().get()
		)
			return false;
	}

	return true;
}
