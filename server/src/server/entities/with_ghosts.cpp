#include <sanguis/exception.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_container.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::with_ghosts::with_ghosts() : ghosts_() {}

sanguis::server::entities::with_ghosts::with_ghosts(
    sanguis::server::collision::ghost_container &&_ghosts)
    : ghosts_(std::move(_ghosts))
{
}

sanguis::server::entities::with_ghosts::~with_ghosts() = default;

sanguis::collision::world::body_enter_container
sanguis::server::entities::with_ghosts::add_ghost(sanguis::server::collision::ghost &&_ghost)
{
  ghosts_.push_back(std::move(_ghost));

  return ghosts_.back().transfer(
      fcppt::optional::to_exception(
          this->environment(),
          [] {
            return sanguis::exception{FCPPT_TEXT("Environment not set in entities::with_ghosts!")};
          })
          .get()
          .collision_world(),
      this->center());
}

void sanguis::server::entities::with_ghosts::init_ghosts(
    sanguis::server::collision::ghost_container &&_ghosts)
{
  ghosts_ = std::move(_ghosts);
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::with_ghosts::on_transfer(
    sanguis::server::entities::transfer_parameters const &_parameters)
{
  return sanguis::server::entities::optional_transfer_result{
      sanguis::server::entities::transfer_result{
          fcppt::algorithm::map_concat<sanguis::collision::world::body_enter_container>(
              ghosts_,
              [&_parameters](sanguis::server::collision::ghost &_ghost)
              { return _ghost.transfer(_parameters.world(), _parameters.center()); })}};
}

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::with_ghosts::remove_from_world()
{
  sanguis::server::environment::object &cur_environment{
      fcppt::optional::to_exception(
          this->environment(),
          [] {
            return sanguis::exception{FCPPT_TEXT("Environment not set in entities::with_ghosts!")};
          })
          .get()};

  return sanguis::server::entities::remove_from_world_result(
      fcppt::algorithm::map_concat<sanguis::collision::world::body_exit_container>(
          ghosts_,
          [&cur_environment](sanguis::server::collision::ghost &_ghost)
          { return _ghost.destroy(cur_environment.collision_world()); }));
}

void sanguis::server::entities::with_ghosts::update_ghost_center(
    sanguis::server::center const &_center)
{
  for (auto &ghost : ghosts_)
  {
    ghost.center(_center);
  }
}
