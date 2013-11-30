#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/change_callback.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/level_callback.hpp>
#include <sanguis/client/perk/remaining_levels.hpp>
#include <sanguis/client/perk/send_callback.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/client/perk/tree_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::perk::state::state(
	sanguis::client::perk::send_callback const &_send_callback
)
:
	send_callback_(
		_send_callback
	),
	perks_(),
	current_level_(
		sanguis::client::level(
			0u
		)
	),
	remaining_levels_(
		sanguis::client::level(
			0u
		)
	),
	level_signal_(),
	change_signal_()
{
}

sanguis::client::perk::state::~state()
{
}

void
sanguis::client::perk::state::perks(
	sanguis::client::perk::tree_unique_ptr &&_perks,
	sanguis::client::perk::remaining_levels const _remaining_levels
)
{
	perks_.take(
		std::move(
			_perks
		)
	);

	remaining_levels_ =
		_remaining_levels;

	change_signal_(
		*perks_
	);
}

void
sanguis::client::perk::state::player_level(
	sanguis::client::player_level const _level
)
{
	FCPPT_ASSERT_PRE(
		_level
		>=
		current_level_
	);

	remaining_levels_
		+=
		sanguis::client::perk::remaining_levels(
			_level.get()
			-
			current_level_.get()
		);

	current_level_ = _level;

	level_signal_(
		_level
	);
}

bool
sanguis::client::perk::state::choose_perk(
	sanguis::perk_type const _type
)
{
	if(
		this->choosable(
			_type
		)
		!=
		sanguis::client::perk::choosable_state::ok
	)
		return false;

	FCPPT_ASSERT_PRE(
		remaining_levels_.get()
		>
		sanguis::client::level(
			0u
		)
	);

	--remaining_levels_;

	sanguis::client::perk::find_info(
		_type,
		*perks_
	).value()->increment_level();

	send_callback_(
		_type
	);

	return true;
}

sanguis::client::perk::tree const &
sanguis::client::perk::state::perks() const
{
	FCPPT_ASSERT_PRE(
		perks_
	);

	return
		*perks_;
}

sanguis::client::player_level const
sanguis::client::perk::state::player_level() const
{
	return
		current_level_;
}

sanguis::client::perk::remaining_levels const
sanguis::client::perk::state::remaining_levels() const
{
	return
		remaining_levels_;
}

sanguis::client::perk::level const
sanguis::client::perk::state::perk_level(
	sanguis::perk_type const _perk_type
) const
{
	return
		sanguis::client::perk::find_info_const(
			_perk_type,
			*perks_
		).value()->level();
}

sanguis::client::perk::choosable_state
sanguis::client::perk::state::choosable(
	sanguis::perk_type const _perk_type
) const
{
	return
		sanguis::client::perk::choosable(
			_perk_type,
			this->perks(),
			current_level_,
			remaining_levels_
		);
}

fcppt::signal::auto_connection
sanguis::client::perk::state::register_level_change(
	sanguis::client::perk::level_callback const &_callback
)
{
	return
		level_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::client::perk::state::register_perks_change(
	sanguis::client::perk::change_callback const &_callback
)
{
	return
		change_signal_.connect(
			_callback
		);
}
