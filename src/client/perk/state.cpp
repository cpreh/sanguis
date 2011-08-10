#include "state.hpp"
#include "choosable.hpp"
#include "info.hpp"
#include "../log.hpp"
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>

sanguis::client::perk::state::state(
	perk::send_callback const &_send_callback
)
:
	send_callback_(_send_callback),
	perks_(),
	current_level_(0),
	consumed_levels_(0),
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
	perk::tree_unique_ptr _perks
)
{
	perks_.take(
		move(
			_perks
		)
	);

	change_signal_(
		*perks_
	);
}

void
sanguis::client::perk::state::player_level(
	client::player_level const _level
)
{
	current_level_ = _level;

	level_signal_(
		_level
	);
}

bool
sanguis::client::perk::state::choose_perk(
	sanguis::perk_type::type const _type
)
{
	if(
		this->choosable(
			_type
		)
		!= perk::choosable_state::ok
	)
		return false;

	++consumed_levels_;

	++perk_levels_[
		_type
	];

	send_callback_(
		_type
	);

	return true;
}

sanguis::client::perk::tree const &
sanguis::client::perk::state::perks() const
{
	FCPPT_ASSERT(
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
	sanguis::perk_type::type const _perk_type
) const
{
	return
		perk_levels_[
			_perk_type
		];
}

sanguis::client::perk::level_map const &
sanguis::client::perk::state::perk_levels() const
{
	return perk_levels_;
}

sanguis::client::perk::choosable_state::type
sanguis::client::perk::state::choosable(
	sanguis::perk_type::type const _type
) const
{
	return
		client::perk::choosable(
			_type,
			this->perks(),
			perk_levels_,
			current_level_,
			consumed_levels_
		);
}

fcppt::signal::auto_connection
sanguis::client::perk::state::register_level_change(
	perk::level_callback const &_callback
)
{
	return
		level_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::client::perk::state::register_perks_change(
	perk::change_callback const &_callback
)
{
	return
		change_signal_.connect(
			_callback
		);
}
