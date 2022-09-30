#include <sanguis/exception.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>

void sanguis::server::entities::spawns::spawn::unregister(sanguis::server::entities::base &) {}

sanguis::server::entities::spawns::spawn::~spawn() = default;

sanguis::server::entities::spawns::spawn::spawn(
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::weapons::common_parameters const &_weapons_parameters,
    sanguis::creator::enemy_type const _enemy_type,
    sanguis::creator::enemy_kind const _enemy_kind,
    sanguis::server::world::difficulty const _difficulty)
    : sanguis::server::entities::simple(),
      sanguis::server::entities::with_links(),
      random_generator_(_random_generator),
      weapons_parameters_{_weapons_parameters},
      enemy_type_{_enemy_type},
      enemy_kind_{_enemy_kind},
      difficulty_{_difficulty},
      center_(),
      angle_()
{
}

sanguis::server::center sanguis::server::entities::spawns::spawn::center() const
{
  return fcppt::optional::to_exception(
      this->center_, [] { return sanguis::exception{FCPPT_TEXT("Spawn center not set!")}; });
}

sanguis::server::angle sanguis::server::entities::spawns::spawn::angle() const
{
  return fcppt::optional::to_exception(
      this->angle_, [] { return sanguis::exception{FCPPT_TEXT("Spawn angle not set!")}; });
}

void sanguis::server::entities::spawns::spawn::angle(sanguis::server::angle const _angle)
{
  angle_ = optional_angle(_angle);
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::spawns::spawn::on_transfer(
    sanguis::server::entities::transfer_parameters const &_parameters)
{
  center_ = optional_center(_parameters.center());

  angle_ = optional_angle(_parameters.angle());

  return sanguis::server::entities::optional_transfer_result(
      sanguis::server::entities::transfer_result());
}

void sanguis::server::entities::spawns::spawn::update()
{
  fcppt::optional::maybe_void(
      this->environment(),
      [this](fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        sanguis::server::entities::spawns::size_type const cur_count{this->may_spawn()};
        fcppt::algorithm::repeat(
            cur_count,
            [this, _environment]()
            {
              sanguis::server::environment::insert_no_result(
                  _environment.get(),
                  sanguis::server::entities::enemies::create(
                      this->random_generator_,
                      this->weapons_parameters_,
                      this->enemy_type_,
                      this->enemy_kind_,
                      this->difficulty_,
                      _environment->load_context(),
                      sanguis::server::entities::spawn_owner(this->link()),
                      sanguis::server::entities::enemies::special_chance(
                          0.05F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                          )),
                  sanguis::server::entities::insert_parameters(this->center(), this->angle()));
            });

        if (cur_count != 0U)
        {
          this->add_count(cur_count);
        }
      });
}
