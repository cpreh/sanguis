#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_DUMMY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_DUMMY_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::scene::state
{

class dummy : public sanguis::client::draw2d::scene::state::base
{
  FCPPT_NONMOVABLE(dummy);

public:
  dummy();

  ~dummy() override;

  [[nodiscard]] sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
      create_scoped(sge::renderer::context::ffp_ref) const override;
};

}

#endif
