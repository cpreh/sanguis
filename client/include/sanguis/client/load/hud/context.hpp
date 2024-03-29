#ifndef SANGUIS_CLIENT_LOAD_HUD_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_CONTEXT_HPP_INCLUDED

#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>

namespace sanguis::client::load::hud
{

class context
{
  FCPPT_NONMOVABLE(context);

public:
  context(fcppt::log::context_reference, sanguis::client::load::resource::textures_cref);

  ~context();

  [[nodiscard]] sge::texture::part const &weapon_icon(sanguis::weapon_type);

private:
  fcppt::log::object log_;

  sanguis::client::load::hud::weapon_icon_map const weapon_icons_;

  sge::texture::part const &missing_texture_;
};

}

#endif
