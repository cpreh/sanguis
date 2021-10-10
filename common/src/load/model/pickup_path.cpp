#include <sanguis/pickup_type.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/pickup_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::load::model::path sanguis::load::model::pickup_path(sanguis::pickup_type const _type)
{
  return sanguis::load::model::path{
      std::filesystem::path{FCPPT_TEXT("pickups")} / sanguis::load::pickup_name(_type)};
}
