#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <sanguis/load/model/aoe_projectile_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::load::model::path
sanguis::load::model::aoe_projectile_path(sanguis::aoe_projectile_type const _type)
{
  return sanguis::load::model::path{
      std::filesystem::path{FCPPT_TEXT("aoe_projectiles")} /
      sanguis::load::aoe_projectile_name(_type)};
}
