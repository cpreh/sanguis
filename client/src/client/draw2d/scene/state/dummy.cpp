#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/dummy.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sge/renderer/context/ffp_ref.hpp>

sanguis::client::draw2d::scene::state::dummy::dummy()
    : sanguis::client::draw2d::scene::state::base()
{
}

sanguis::client::draw2d::scene::state::dummy::~dummy() = default;

sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
sanguis::client::draw2d::scene::state::dummy::create_scoped(sge::renderer::context::ffp_ref) const
{
  return sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr();
}
