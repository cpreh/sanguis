#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>

sanguis::server::entities::insert_parameters
sanguis::server::entities::insert_parameters_center(sanguis::server::center const &_center)
{
  // TODO(philipp): This function makes no sense
  return sanguis::server::entities::insert_parameters(_center, sanguis::server::angle(0.F));
}
