#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_NAME_AND_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_NAME_AND_HEALTH_HPP_INCLUDED

#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_name.hpp>

namespace sanguis::client::draw2d::entities::hover
{

class name_and_health
{
public:
  name_and_health(
      sanguis::client::draw2d::entities::hover::optional_name &&,
      sanguis::client::optional_health_pair);

  [[nodiscard]] sanguis::client::draw2d::entities::hover::optional_name const &name() const;

  [[nodiscard]] sanguis::client::optional_health_pair health() const;

private:
  sanguis::client::draw2d::entities::hover::optional_name name_;

  sanguis::client::optional_health_pair health_;
};

}

#endif
