#ifndef SANGUIS_SERVER_ENTITIES_CENTER_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_CENTER_GHOST_HPP_INCLUDED

#include <sanguis/server/entities/center_simple.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities
{

class center_ghost : public sanguis::server::entities::center_simple,
                     public virtual sanguis::server::entities::with_ghosts
{
  FCPPT_NONMOVABLE(center_ghost);

protected:
  center_ghost();

public:
  ~center_ghost() override = 0;

protected:
  [[nodiscard]] sanguis::server::entities::optional_transfer_result
  on_transfer(sanguis::server::entities::transfer_parameters const &) override;
};

}

#endif
