#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_stationary.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/tree/make_leaf.hpp>

sanguis::server::ai::create_function
sanguis::server::ai::create_stationary(sanguis::server::ai::sight_range const _sight_range)
{
  return sanguis::server::ai::create_function{
      [_sight_range](sanguis::server::ai::context_ref const _context)
      {
        return sanguis::server::ai::tree::make_leaf<sanguis::server::ai::behavior::attack>(
            _context, _sight_range);
      }};
}
