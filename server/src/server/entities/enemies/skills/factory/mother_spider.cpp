#include <sanguis/server/entities/enemies/skills/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/factory/mother_spider.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::enemies::skills::unique_ptr
sanguis::server::entities::enemies::skills::factory::mother_spider(
	sanguis::server::entities::enemies::skills::factory::parameters const &
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::skills::mother_spider
		>();
}
