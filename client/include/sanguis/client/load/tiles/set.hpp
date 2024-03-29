#ifndef SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_comparison.hpp> // IWYU pragma: keep
#include <fcppt/reference_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load::tiles
{

class set
{
  FCPPT_NONCOPYABLE(set);

public:
  set(sanguis::client::load::resource::textures_cref, std::filesystem::path const &);

  set(set &&) noexcept;

  set &operator=(set &&) noexcept;

  ~set();

  [[nodiscard]] sanguis::client::load::tiles::texture_container const &
      areas(sanguis::tiles::area_container_ref);

private:
  fcppt::reference<sge::texture::part const> texture_;

  using element_map =
      std::map<sanguis::tiles::area_container_ref, sanguis::client::load::tiles::texture_container>;

  element_map elements_;
};

}

#endif
