#include <sanguis/random_generator.hpp>
#include <sanguis/creator/generators.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/server/world/random_generator_name.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/random/wrapper/make_uniform_container.hpp>

sanguis::creator::name
sanguis::server::world::random_generator_name(sanguis::random_generator &_generator)
{
  return FCPPT_ASSERT_OPTIONAL_ERROR(fcppt::random::wrapper::make_uniform_container(
      fcppt::make_cref(sanguis::creator::generators())))(_generator);
}
