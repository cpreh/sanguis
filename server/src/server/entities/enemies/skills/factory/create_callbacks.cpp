#include <sanguis/server/entities/enemies/skills/factory/callback_vector.hpp>
#include <sanguis/server/entities/enemies/skills/factory/create_callbacks.hpp>
#include <sanguis/server/entities/enemies/skills/factory/teleport.hpp>


namespace
{

sanguis::server::entities::enemies::skills::factory::callback_vector const callbacks{
	&sanguis::server::entities::enemies::skills::factory::teleport
};

}

sanguis::server::entities::enemies::skills::factory::callback_vector const &
sanguis::server::entities::enemies::skills::factory::create_callbacks()
{
	return
		callbacks;
}
