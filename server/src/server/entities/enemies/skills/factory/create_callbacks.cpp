#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/create_callbacks.hpp>
#include <sanguis/server/entities/enemies/skills/factory/teleport.hpp>


namespace
{

sanguis::server::entities::enemies::skills::factory::container const callbacks{
	&sanguis::server::entities::enemies::skills::factory::teleport
};

}

sanguis::server::entities::enemies::skills::factory::container const &
sanguis::server::entities::enemies::skills::factory::create_callbacks()
{
	return
		callbacks;
}
