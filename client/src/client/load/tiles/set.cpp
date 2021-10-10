#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sanguis/client/load/tiles/make_textures.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::client::load::tiles::set::set(
    sanguis::client::load::resource::textures_cref const _textures,
    std::filesystem::path const &_path)
    : texture_{_textures->load(_path)}, elements_()
{
}

sanguis::client::load::tiles::set::set(set &&) noexcept = default;

sanguis::client::load::tiles::set &
sanguis::client::load::tiles::set::operator=(set &&) noexcept = default;

sanguis::client::load::tiles::set::~set() = default;

sanguis::client::load::tiles::texture_container const &
sanguis::client::load::tiles::set::areas(sanguis::tiles::area_container_ref const _areas_arg)
{
  return fcppt::container::get_or_insert(
      elements_,
      _areas_arg,
      [this](sanguis::tiles::area_container_ref const &_areas)
      { return sanguis::client::load::tiles::make_textures(texture_.get(), _areas.get()); });
}
