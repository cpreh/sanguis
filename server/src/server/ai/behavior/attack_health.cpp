#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/behavior/attack_health.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/strong_typedef_arithmetic.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/div.hpp>
#include <fcppt/optional/maybe.hpp>

sanguis::server::ai::behavior::attack_health::attack_health(
    sanguis::server::ai::context_ref const _context,
    sanguis::server::ai::sight_range const _sight_range,
    sanguis::server::ai::speed_factor const _speed_factor)
    : sanguis::server::ai::behavior::attack{_context, _sight_range}, speed_factor_{_speed_factor}
{
}

sanguis::server::ai::behavior::attack_health::~attack_health() = default;

sanguis::server::ai::speed_factor sanguis::server::ai::behavior::attack_health::speed_factor() const
{
  return speed_factor_ +
         fcppt::strong_typedef_construct_cast<
             sanguis::server::ai::speed_factor,
             fcppt::cast::size_fun>(fcppt::optional::maybe(
             fcppt::math::div(this->me().current_health().get(), this->me().max_health().get()),
             fcppt::const_(fcppt::literal<sanguis::server::space_unit>(1.0F)),
             [](sanguis::server::space_unit const _ratio)
             { return fcppt::literal<sanguis::server::space_unit>(1.0F) - _ratio; }));
}
