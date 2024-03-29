#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_LEVEL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_LEVEL_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/level_fwd.hpp> // IWYU pragma: keep
#include <sge/texture/const_part_ref.hpp>

namespace sanguis::client::draw2d::entities
{

class level
{
public:
  level(sanguis::client::draw2d::z_ordering, sge::texture::const_part_ref);

  [[nodiscard]] sanguis::client::draw2d::z_ordering z_ordering() const;

  [[nodiscard]] sge::texture::const_part_ref texture() const;

private:
  sanguis::client::draw2d::z_ordering z_ordering_;

  sge::texture::const_part_ref texture_;
};

}

#endif
