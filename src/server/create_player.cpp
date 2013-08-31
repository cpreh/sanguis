#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/console_command_vector.hpp>
#include <sanguis/server/create_player.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/player_unique_ptr.hpp>
#include <sanguis/messages/add_console_command.hpp>
#include <sanguis/messages/create.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>


sanguis::server::entities::player_unique_ptr
sanguis::server::create_player(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::string const &_name,
	sanguis::server::unicast_callback const &_send_to_player,
	sanguis::server::player_id const _player_id,
	sanguis::server::console_command_vector const &_known_commands
)
{
	FCPPT_LOG_DEBUG(
		sanguis::server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Creating player ")
			<< _player_id
	);

	for(
		auto const &command : _known_commands
	)
		_send_to_player(
			_player_id,
			*sanguis::messages::create(
				sanguis::messages::add_console_command(
					sge::charconv::fcppt_string_to_utf8(
						command.first
					),
					sge::charconv::fcppt_string_to_utf8(
						command.second
					)
				)
			)
		);

	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::player
		>(
			_diff_clock,
			_load_context,
			sanguis::server::health(
				100.f
			),
			sanguis::server::damage::no_armor(),
			sanguis::server::entities::movement_speed(
				10.f
			),
			_name,
			_player_id
		);
}
