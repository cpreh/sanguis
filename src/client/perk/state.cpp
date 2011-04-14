#include "state.hpp"
#include "../log.hpp"
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/text.hpp>

sanguis::client::perk::state::state(
	perk::send_callback const &_send_callback
)
:
	send_callback_(_send_callback),
	perks_(),
	current_level_(0),
	consumed_levels_(0),
	level_signal_(),
	change_signal_()
{
}

sanguis::client::perk::state::~state()
{
}

void
sanguis::client::perk::state::perks(
	perk::container const &_perks
)
{
	perks_ = _perks;

	change_signal_(
		_perks
	);
}

void
sanguis::client::perk::state::level(
	client::level const _level
)
{
	current_level_ = _level;

	level_signal_(
		_level
	);
}

void
sanguis::client::perk::state::choose_perk(
	sanguis::perk_type::type const _type
)
{
	if(
		consumed_levels_ == current_level_
	)
	{
		FCPPT_LOG_ERROR(
			client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Cannot choose a perk because no level up is left! ")
				<< FCPPT_TEXT("The current level is ")
				<< current_level_
		);

		return;
	}

	++consumed_levels_;
	
	send_callback_(
		_type
	);
}

sanguis::client::perk::container const &
sanguis::client::perk::state::perks()
{
	return perks_;
}

sanguis::client::level const
sanguis::client::perk::state::level() const
{
	return current_level_;
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
