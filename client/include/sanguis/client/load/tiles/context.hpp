#ifndef SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/error.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load::tiles
{

class context
{
  FCPPT_NONMOVABLE(context);

public:
  explicit context(sanguis::client::load::resource::textures_cref);

  ~context();

  [[nodiscard]] sanguis::client::load::tiles::texture_container const &
  set(std::filesystem::path const &, sanguis::tiles::area_container_ref const &);

  [[nodiscard]] sanguis::tiles::collection &collection();

  [[nodiscard]] sge::texture::part const &missing_texture(sanguis::tiles::error) const;

private:
  using map_type = std::map<std::filesystem::path, sanguis::client::load::tiles::set>;

  sanguis::tiles::collection collection_;

  sanguis::client::load::resource::textures_cref const textures_;

  map_type sets_;

  using missing_texture_array =
      fcppt::enum_::array<sanguis::tiles::error, sge::texture::const_part_unique_ptr>;

  missing_texture_array const missing_textures_;
};

}

#endif
