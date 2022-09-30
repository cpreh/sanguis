#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/creator/generators.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/server/world/random_generator_name.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/random/wrapper/make_uniform_container.hpp>

sanguis::creator::name
sanguis::server::world::random_generator_name(sanguis::random_generator &_generator)
{
  return fcppt::optional::to_exception(
      fcppt::random::wrapper::make_uniform_container(
          fcppt::make_cref(sanguis::creator::generators())),
      [] { return sanguis::exception{FCPPT_TEXT("Generator container is empty!")}; })(_generator);
}
