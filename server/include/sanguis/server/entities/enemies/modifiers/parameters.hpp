#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::enemies::modifiers
{

class parameters
{
public:
  explicit parameters(sanguis::random_generator_ref);

  [[nodiscard]] sanguis::random_generator &random_generator() const;

private:
  sanguis::random_generator_ref random_generator_;
};

}

#endif
