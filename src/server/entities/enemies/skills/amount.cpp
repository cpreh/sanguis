#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/entities/enemies/skills/amount.hpp>
#include <sanguis/server/entities/enemies/skills/factory/create_callbacks.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


sanguis::server::random::amount const
sanguis::server::entities::enemies::skills::amount()
{
	return
		fcppt::strong_typedef_construct_cast<
			sanguis::server::random::amount
		>(
			sanguis::server::entities::enemies::skills::factory::create_callbacks().size()
		);
}
