#include <sanguis/client/load/resource/texture_from_view.hpp>
#include <sanguis/client/load/resource/textures.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/error_image.hpp>
#include <sge/image2d/store/object.hpp>
#include <sge/image2d/store/view.hpp>
#include <sge/image2d/view/const_object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/texture/part.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/enum/array_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/enum/array_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::client::load::tiles::context::context(
    sanguis::client::load::resource::textures_cref const _textures)
    : collection_(fcppt::make_ref(_textures->image_system())),
      textures_(_textures),
      sets_(),
      missing_textures_(fcppt::enum_::array_init<missing_texture_array>(
          [&_textures](sanguis::tiles::error const _error)
          {
            sge::image2d::store::object const error_image{sanguis::tiles::error_image(_error)};

            return sanguis::client::load::resource::texture_from_view(
                fcppt::make_ref(_textures->renderer()),
                sge::image2d::store::view(fcppt::make_cref(error_image)));
          }))
{
}

sanguis::client::load::tiles::context::~context() = default;

sanguis::client::load::tiles::texture_container const &sanguis::client::load::tiles::context::set(
    std::filesystem::path const &_image_path, sanguis::tiles::area_container_ref const &_areas)
{
  return fcppt::container::get_or_insert(
             sets_,
             _image_path,
             [this](std::filesystem::path const &_path)
             { return sanguis::client::load::tiles::set(textures_, _path); })
      .areas(_areas);
}

sanguis::tiles::collection &sanguis::client::load::tiles::context::collection()
{
  return collection_;
}

sge::texture::part const &
sanguis::client::load::tiles::context::missing_texture(sanguis::tiles::error const _error) const
{
  return *missing_textures_[_error];
}
