#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/change_callback.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/level_callback.hpp>
#include <sanguis/client/perk/level_map.hpp>
#include <sanguis/client/perk/send_callback.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/client/perk/tree_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/tree/object_impl.hpp>
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
	consumed_levels_(
		0u
	),
	perk_levels_(),
	level_signal_(),
	change_signal_()
{
}

sanguis::client::perk::state::~state()
{
}

void
sanguis::client::perk::state::perks(
	sanguis::client::perk::tree_unique_ptr &&_perks
)
{
	perks_.take(
		std::move(
			_perks
		)
	);

	change_signal_(
		*perks_
	);
}

void
sanguis::client::perk::state::player_level(
	sanguis::client::player_level const _level
)
{
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

	++consumed_levels_;

	++perk_levels_.insert(
		std::make_pair(
			_type,
			sanguis::client::perk::level(
				sanguis::client::level(
					0u
				)
			)
		)
	).first->second;

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

	return *perks_;
}

sanguis::client::player_level const
sanguis::client::perk::state::player_level() const
{
	return current_level_;
}

sanguis::client::level const
sanguis::client::perk::state::levels_left() const
{
	return
		current_level_.get()
		- consumed_levels_;
}

sanguis::client::perk::level const
sanguis::client::perk::state::perk_level(
	sanguis::perk_type const _perk_type
) const
{
	return
		perk_levels_.insert(
			std::make_pair(
				_perk_type,
				sanguis::client::perk::level(
					sanguis::client::level(
						0u
					)
				)
			)
		).first->second;
}

sanguis::client::perk::level_map const &
sanguis::client::perk::state::perk_levels() const
{
	return perk_levels_;
}

sanguis::client::perk::choosable_state
sanguis::client::perk::state::choosable(
	sanguis::perk_type const _type
) const
{
	return
		sanguis::client::perk::choosable(
			_type,
			this->perks(),
			perk_levels_,
			current_level_,
			consumed_levels_
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
