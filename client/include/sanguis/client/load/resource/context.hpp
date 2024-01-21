#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/player_ref.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>

namespace sanguis::client::load::resource
{

class context
{
  FCPPT_NONMOVABLE(context);

public:
  [[nodiscard]] sanguis::client::load::resource::textures const &textures() const;

  [[nodiscard]] sanguis::client::load::resource::sounds const &sounds() const;

private:
  friend class sanguis::client::load::context;

  context(
      fcppt::log::context_reference,
      sge::renderer::device::core_ref,
      sge::image2d::system_ref,
      sge::audio::loader_ref,
      sge::audio::player_ref);

  ~context();

  fcppt::unique_ptr<sanguis::client::load::resource::textures> const textures_;

  fcppt::unique_ptr<sanguis::client::load::resource::sounds> const sounds_;
};

}

#endif
