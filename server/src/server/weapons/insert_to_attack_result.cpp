#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>

sanguis::server::weapons::attack_result sanguis::server::weapons::insert_to_attack_result(
    sanguis::server::entities::optional_base_ref const &_ref)
{
  return _ref.has_value() ? sanguis::server::weapons::attack_result::success
                          : sanguis::server::weapons::attack_result::failure;
}
