#ifndef SANGUIS_SERVER_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/load_context_ref.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/world/context_ref.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/context_reference.hpp>

namespace sanguis::server::world
{

class parameters
{
public:
  parameters(
      fcppt::log::context_reference,
      sanguis::random_generator_ref,
      sanguis::server::weapons::common_parameters const &,
      sanguis::server::world::context_ref,
      sanguis::server::environment::load_context_ref);

  [[nodiscard]] fcppt::log::context &log_context() const;

  [[nodiscard]] sanguis::random_generator &random_generator() const;

  [[nodiscard]] sanguis::server::weapons::common_parameters const &weapon_parameters() const;

  [[nodiscard]] sanguis::server::world::context &context() const;

  [[nodiscard]] sanguis::server::environment::load_context &load_context() const;

private:
  fcppt::log::context_reference log_context_;

  sanguis::random_generator_ref random_generator_;

  sanguis::server::weapons::common_parameters weapon_parameters_;

  sanguis::server::world::context_ref context_;

  sanguis::server::environment::load_context_ref load_context_;
};

}

#endif
