#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/make_texture.hpp>
#include <sanguis/client/load/tiles/context.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/load/tiles/context_ref.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/error.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/random/wrapper/make_uniform_container.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::texture::const_optional_part_ref sanguis::client::draw2d::scene::world::make_texture(
    sanguis::random_generator &_random_generator,
    sanguis::client::draw::debug const _debug,
    sanguis::client::load::tiles::context_ref const _context,
    std::filesystem::path const &_path,
    sanguis::tiles::content const &_content)
{
  return fcppt::variant::match(
      _content,
      [&_random_generator, &_path, &_context](sanguis::tiles::area_container_ref const &_areas)
      {
        sanguis::client::load::tiles::texture_container const &textures{
            _context->set(_path, _areas)};

        auto random_part{fcppt::optional::to_exception(
            fcppt::random::wrapper::make_uniform_container(fcppt::make_cref(textures)),
            [] { return sanguis::exception{FCPPT_TEXT("Empty texture container!")}; })};

        return sge::texture::const_optional_part_ref(
            fcppt::make_cref(*random_part(_random_generator)));
      },
      [&_context, _debug](sanguis::tiles::error const _error)
      {
        return _debug.get() ? sge::texture::const_optional_part_ref(
                                  fcppt::make_cref(_context->missing_texture(_error)))
                            : sge::texture::const_optional_part_ref();
      });
}
