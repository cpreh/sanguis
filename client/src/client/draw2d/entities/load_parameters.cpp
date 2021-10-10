#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/sound_manager_ref.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>

sanguis::client::draw2d::entities::load_parameters::load_parameters(
    sanguis::diff_clock_cref const _diff_clock,
    sanguis::random_generator_ref const _random_generator,
    sanguis::client::sound_manager_ref const _sound_manager,
    sanguis::client::draw2d::sprite::normal::system_ref const _normal_system,
    sanguis::client::load::model::collection_cref const _collection)
    : diff_clock_(_diff_clock),
      random_generator_(_random_generator),
      sound_manager_(_sound_manager),
      normal_system_(_normal_system),
      collection_(_collection)
{
}

sanguis::diff_clock const &sanguis::client::draw2d::entities::load_parameters::diff_clock() const
{
  return diff_clock_.get();
}

sanguis::client::sound_manager &
sanguis::client::draw2d::entities::load_parameters::sound_manager() const
{
  return sound_manager_.get();
}

sanguis::random_generator &
sanguis::client::draw2d::entities::load_parameters::random_generator() const
{
  return random_generator_.get();
}

sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::entities::load_parameters::normal_system() const
{
  return normal_system_.get();
}

sanguis::client::load::model::collection const &
sanguis::client::draw2d::entities::load_parameters::collection() const
{
  return collection_.get();
}
