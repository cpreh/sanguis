#ifndef SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/world/context_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::world
{

class context
{
  FCPPT_NONMOVABLE(context);

protected:
  context();

public:
  [[nodiscard]] virtual bool request_transfer(sanguis::server::global::source_world_pair) const = 0;

  virtual void transfer_entity(
      sanguis::server::global::source_world_pair,
      sanguis::server::entities::with_id_unique_ptr &&) = 0;

  virtual void
  send_to_player(sanguis::server::player_id, sanguis::messages::server::base const &) = 0;

  virtual void remove_player(sanguis::server::player_id) = 0;

  virtual ~context();
};

}

#endif
