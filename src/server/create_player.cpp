#include <sanguis/server/create_player.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/messages/add_console_command.hpp>
#include <sanguis/messages/create.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/utf8/from_fcppt_string.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/homogenous_pair_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::entities::player_unique_ptr
sanguis::server::create_player(
	sanguis::diff_clock const &_diff_clock,
	environment::load_context &_load_context,
	server::string const &_name,
	server::unicast_callback const &_send_to_player,
	server::player_id const _player_id,
	server::console_command_vector const &_known_commands
)
{
	FCPPT_LOG_DEBUG(
		server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Creating player ")
			<< _player_id
	);

	for(
		console_command_vector::const_iterator elem_it(
			_known_commands.begin()
		);
		elem_it != _known_commands.end();
		++elem_it
	)
		_send_to_player(
			_player_id,
			messages::create(
				messages::add_console_command(
					fcppt::utf8::from_fcppt_string(
						elem_it->first
					),
					fcppt::utf8::from_fcppt_string(
						elem_it->second
					)
				)
			)
		);

	return
		fcppt::make_unique_ptr<
			entities::player
		>(
			fcppt::cref(
				_diff_clock
			),
			fcppt::ref(
				_load_context
			),
			server::health(100),
			damage::no_armor(),
			entities::movement_speed(2),
			_name,
			_player_id
		);
}
