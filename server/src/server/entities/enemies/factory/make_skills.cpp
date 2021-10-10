#include <sanguis/random_generator.hpp>
#include <sanguis/server/entities/enemies/factory/make_skills.hpp>
#include <sanguis/server/entities/enemies/skills/factory/callback.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/create_callbacks.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/create_function.hpp>
#include <sanguis/server/random/draw.hpp>
#include <sanguis/server/random/equal_function.hpp>
#include <sanguis/server/random/less_function.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::enemies::skills::factory::container
sanguis::server::entities::enemies::factory::make_skills(
    sanguis::random_generator &_random_generator, sanguis::server::random::amount const _amount)
{
  return sanguis::server::random::draw<
      sanguis::server::entities::enemies::skills::factory::container>(
      _random_generator,
      sanguis::server::entities::enemies::skills::factory::create_callbacks(),
      _amount,
      sanguis::server::random::create_function<
          sanguis::server::entities::enemies::skills::factory::callback,
          sanguis::server::entities::enemies::skills::factory::callback>(
          fcppt::function<sanguis::server::entities::enemies::skills::factory::callback(
              sanguis::server::entities::enemies::skills::factory::callback const &)>{
              [](sanguis::server::entities::enemies::skills::factory::callback const &_callback)
              { return _callback; }}),
      sanguis::server::random::less_function<
          sanguis::server::entities::enemies::skills::factory::callback>(
          fcppt::function<bool(
              sanguis::server::entities::enemies::skills::factory::callback const &,
              sanguis::server::entities::enemies::skills::factory::callback const &)>{
              [](sanguis::server::entities::enemies::skills::factory::callback const &_skill1,
                 sanguis::server::entities::enemies::skills::factory::callback const &_skill2)
              { return std::less<>()(_skill1, _skill2); }}),
      sanguis::server::random::equal_function<
          sanguis::server::entities::enemies::skills::factory::callback>(

          fcppt::function<bool(
              sanguis::server::entities::enemies::skills::factory::callback const &,
              sanguis::server::entities::enemies::skills::factory::callback const &)>{
              [](sanguis::server::entities::enemies::skills::factory::callback const &_skill1,
                 sanguis::server::entities::enemies::skills::factory::callback const &_skill2)
              { return typeid(*_skill1) == typeid(*_skill2); }}));
}
