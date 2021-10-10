#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/log_cref.hpp>
#include <sanguis/server/weapons/log_fwd.hpp>

sanguis::server::weapons::common_parameters::common_parameters(
    sanguis::server::weapons::log_cref const _log,
    sanguis::random_generator_ref const _random_generator)
    : log_{_log}, random_generator_{_random_generator}
{
}

sanguis::server::weapons::log const &sanguis::server::weapons::common_parameters::log() const
{
  return log_.get();
}

sanguis::random_generator &sanguis::server::weapons::common_parameters::random_generator() const
{
  return random_generator_.get();
}
