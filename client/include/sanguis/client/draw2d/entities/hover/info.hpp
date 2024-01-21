#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_INFO_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_INFO_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/info_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/draw2d/entities/hover/variant.hpp>

namespace sanguis::client::draw2d::entities::hover
{

class info
{
public:
  explicit info(sanguis::client::draw2d::entities::hover::variant &&);

  [[nodiscard]] sanguis::client::draw2d::entities::hover::variant const &get() const;

private:
  sanguis::client::draw2d::entities::hover::variant impl_;
};

}

#endif
