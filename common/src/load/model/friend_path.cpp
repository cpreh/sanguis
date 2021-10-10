#include <sanguis/friend_type.hpp>
#include <sanguis/load/friend_name.hpp>
#include <sanguis/load/model/friend_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::load::model::path sanguis::load::model::friend_path(sanguis::friend_type const _type)
{
  return sanguis::load::model::path{
      std::filesystem::path{FCPPT_TEXT("friends")} / sanguis::load::friend_name(_type)};
}
