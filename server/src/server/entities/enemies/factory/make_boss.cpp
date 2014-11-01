#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/boss.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/make_boss.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::make_boss(
	sanguis::server::entities::enemies::parameters &&_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::boss
		>(
			std::move(
				_parameters
			)
		);
}
