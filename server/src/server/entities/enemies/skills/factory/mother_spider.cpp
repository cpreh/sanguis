#include <sanguis/server/entities/enemies/skills/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::server::entities::enemies::skills::unique_ptr
sanguis::server::entities::enemies::skills::factory::mother_spider(
	sanguis::server::entities::enemies::skills::factory::parameters const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::enemies::skills::skill
		>(
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::skills::mother_spider
			>()
		);
}
