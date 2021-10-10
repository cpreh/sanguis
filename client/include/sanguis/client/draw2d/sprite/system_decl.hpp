#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_DECL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/buffers_decl.hpp>
#include <sanguis/client/draw2d/sprite/state.hpp>
#include <sanguis/client/draw2d/sprite/system_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/sprite/intrusive/ordered/collection_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::client::draw2d::sprite
{

template <typename Choices, typename Category>
class system
{
  FCPPT_NONMOVABLE(system);

  using collection = sge::sprite::intrusive::ordered::collection<Choices, Category>;

  using connection_ref = typename collection::connection_ref;

public:
  using state_ref = fcppt::reference<sanguis::client::draw2d::sprite::state>;

  system(
      sge::renderer::device::core_ref,
      // TODO(philipp): Make it possible to omit the states if they do nothing
      state_ref);

  ~system();

  [[nodiscard]] connection_ref connection(Category);

  void render(
      sge::renderer::context::core &, // NOLINT(google-runtime-references)
      Category);

  [[nodiscard]] sge::renderer::device::core &renderer() const;

private:
  using sge_buffers = sanguis::client::draw2d::sprite::buffers<Choices>;

  sge::renderer::device::core_ref const renderer_;

  state_ref const state_;

  sge_buffers buffers_;

  collection collection_;
};

}

#endif
