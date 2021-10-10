#ifndef SANGUIS_CLIENT_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/model/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/player_ref.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>

namespace sanguis::client::load
{

class context
{
  FCPPT_NONMOVABLE(context);

public:
  context(
      fcppt::log::context_reference,
      sge::image2d::system_ref,
      sge::renderer::device::core_ref,
      sge::audio::loader_ref,
      sge::audio::player_ref);

  ~context();

  [[nodiscard]] sanguis::client::load::resource::context const &resources() const;

  [[nodiscard]] sanguis::client::load::model::context const &models() const;

private:
  sanguis::client::load::resource::context const resource_ctx_;

  sanguis::client::load::model::context const model_ctx_;
};

}

#endif
