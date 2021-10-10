#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/property/changeable.hpp>

void sanguis::server::ai::stop(sanguis::server::entities::with_ai &_me)
{
  _me.movement_speed().current(0);
}
