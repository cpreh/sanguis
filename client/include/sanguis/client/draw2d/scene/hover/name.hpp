#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_HPP_INCLUDED

#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/name_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis::client::draw2d::scene::hover
{

class name
{
  FCPPT_NONCOPYABLE(name);

public:
  name(
      sge::renderer::device::ffp_ref,
      sge::font::object_ref,
      sanguis::client::draw2d::sprite::center const &,
      sanguis::client::draw2d::radius,
      sanguis::client::draw2d::entities::hover::name const &);

  name(name &&) noexcept;

  name &operator=(name &&) noexcept;

  ~name();

  void draw(sge::renderer::context::ffp & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)
private:
  sge::font::draw::static_text text_;
};

}

#endif
