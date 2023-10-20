#include <sanguis/player_name.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <sanguis/messages/server/add_console_command.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/server/console_command_vector.hpp>
#include <sanguis/server/create_player.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/player_unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <alda/message/init_record.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::player_unique_ptr sanguis::server::create_player(
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::weapons::common_parameters const &_weapon_parameters,
    sanguis::server::environment::load_context &_load_context,
    sanguis::player_name &&_name,
    sanguis::server::unicast_callback const &_send_to_player,
    sanguis::server::player_id const _player_id,
    sanguis::server::console_command_vector const &_known_commands)
{
  for (auto const &command : _known_commands)
  {
    _send_to_player(
        _player_id,
        sanguis::messages::server::create(
            alda::message::init_record<sanguis::messages::server::add_console_command>(
                sanguis::messages::roles::command_name{} =
                    sge::charconv::fcppt_string_to_utf8(fcppt::tuple::get<0U>(command)),
                sanguis::messages::roles::command_description{} =
                    sge::charconv::fcppt_string_to_utf8(fcppt::tuple::get<1U>(command)))));
  }

  return fcppt::make_unique_ptr<sanguis::server::entities::player>(
      _random_generator,
      _weapon_parameters,
      _load_context,
      sanguis::server::health(
          100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      sanguis::server::damage::no_armor(),
      sanguis::server::entities::movement_speed(
          240.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      std::move(_name),
      _player_id);
}
