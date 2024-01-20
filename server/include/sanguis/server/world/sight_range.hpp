#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/world/sight_range_entry_set.hpp>
#include <sanguis/server/world/sight_range_fwd.hpp> // IWYU pragma: keep

namespace sanguis::server::world
{

class sight_range
{
public:
  sight_range();

  void add(sanguis::entity_id);

  void remove(sanguis::entity_id);

  [[nodiscard]] bool contains(sanguis::entity_id) const;

  [[nodiscard]] bool empty() const;

private:
  sanguis::server::world::sight_range_entry_set entries_;
};

}

#endif
