#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/client/load/log_location.hpp>
#include <sanguis/client/load/resource/make_missing_texture.hpp>
#include <sanguis/client/load/resource/search_texture_names.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::texture::part const &sanguis::client::load::resource::textures::load(
    sanguis::client::load::resource::texture_identifier const &_id) const
{
  return *fcppt::container::get_or_insert(
      textures_,
      _id,
      [this](sanguis::client::load::resource::texture_identifier const &_inner_id)
      { return this->do_load(_inner_id); });
}

sge::texture::part const &
sanguis::client::load::resource::textures::load(std::filesystem::path const &_path) const
{
  return *fcppt::container::get_or_insert(
      unnamed_textures_,
      _path,
      [this](std::filesystem::path const &_inner_path)
      { return this->do_load_inner(_inner_path); });
}

sge::texture::const_optional_part_ref
sanguis::client::load::resource::textures::load_opt(std::filesystem::path const &_path) const
try
{
  // TODO(philipp): This should be the other way around (exception from optional)
  return sge::texture::const_optional_part_ref{fcppt::make_cref(this->load(_path))};
}
catch (fcppt::exception const &_error)
{
  FCPPT_LOG_ERROR(
      log_,
      fcppt::log::out << FCPPT_TEXT("Failed to load ") << fcppt::filesystem::path_to_string(_path)
                      << FCPPT_TEXT(": ") << _error.string())

  return sge::texture::const_optional_part_ref();
}

sge::texture::part const &sanguis::client::load::resource::textures::missing_texture() const
{
  return *missing_texture_;
}

sge::image2d::system &sanguis::client::load::resource::textures::image_system() const
{
  return image_loader_.get();
}

sge::renderer::device::core &sanguis::client::load::resource::textures::renderer() const
{
  return renderer_.get();
}

sanguis::client::load::resource::textures::textures(
    fcppt::log::context_reference const _log_context,
    sge::renderer::device::core_ref const _renderer,
    sge::image2d::system_ref const _image_loader)
    : log_{_log_context, sanguis::client::load::log_location(), fcppt::log::name{FCPPT_TEXT("textures")}},
      renderer_(_renderer),
      image_loader_(_image_loader),
      texture_names_(sanguis::client::load::resource::search_texture_names(log_)),
      textures_(),
      unnamed_textures_(),
      missing_texture_(sanguis::client::load::resource::make_missing_texture(
          renderer_,
          fcppt::literal<sge::image::size_type>(
              64 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          sge::image::color::any::object{sge::image::color::predef::magenta()},
          sge::image::color::any::object{sge::image::color::predef::black()}))
{
}

sanguis::client::load::resource::textures::~textures() = default;

sge::texture::const_part_unique_ptr sanguis::client::load::resource::textures::do_load(
    sanguis::client::load::resource::texture_identifier const &_id) const
{
  return this->do_load_inner(
      sanguis::media_path() / fcppt::optional::to_exception(
                                  fcppt::container::find_opt_mapped(texture_names_, _id),
                                  [_id]
                                  {
                                    return sanguis::exception{
                                        FCPPT_TEXT("no texture for id \"") + _id.get() +
                                        FCPPT_TEXT("\" found")};
                                  })
                                  .get());
}

sge::texture::const_part_unique_ptr
sanguis::client::load::resource::textures::do_load_inner(std::filesystem::path const &_path) const
{
  return fcppt::unique_ptr_to_const(fcppt::unique_ptr_to_base<sge::texture::part>(
      fcppt::make_unique_ptr<sge::texture::part_raw_ptr>(
          sge::renderer::texture::create_planar_from_path(
              _path,
              renderer_,
              image_loader_.get(),
              sge::renderer::texture::mipmap::off(),
              sge::renderer::resource_flags_field::null(),
              sge::renderer::texture::emulate_srgb::yes))));
}
