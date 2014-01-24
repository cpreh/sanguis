#include <sanguis/client/health_value.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/max_health_valid.hpp>
#include <fcppt/literal.hpp>


bool
sanguis::client::max_health_valid(
	sanguis::client::max_health const _max_health
)
{
	return
		_max_health.get()
		>
		fcppt::literal<
			sanguis::client::health_value
		>(
			0
		);
}
