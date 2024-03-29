#ifndef SANGUIS_CLIENT_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/client/world_parameters_fwd.hpp> // IWYU pragma: keep
#include <sanguis/creator/top_parameters.hpp>

namespace sanguis::client
{

class world_parameters
{
public:
  world_parameters(sanguis::world_id, sanguis::creator::top_parameters &&);

  [[nodiscard]] sanguis::world_id world_id() const;

  [[nodiscard]] sanguis::creator::top_parameters const &top_parameters() const;

private:
  sanguis::world_id world_id_;

  sanguis::creator::top_parameters top_parameters_;
};

}

#endif
