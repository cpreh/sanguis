#include <sanguis/server/entities/enemies/modifiers/agile.hpp>
#include <sanguis/server/entities/enemies/modifiers/armored.hpp>
#include <sanguis/server/entities/enemies/modifiers/burning.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/entities/enemies/modifiers/create_callbacks.hpp>
#include <sanguis/server/entities/enemies/modifiers/fast.hpp>
#include <sanguis/server/entities/enemies/modifiers/freezing.hpp>
#include <sanguis/server/entities/enemies/modifiers/health.hpp>
#include <sanguis/server/entities/enemies/modifiers/regenerating.hpp>


namespace
{

sanguis::server::entities::enemies::modifiers::container const callbacks{
	&sanguis::server::entities::enemies::modifiers::agile,
	&sanguis::server::entities::enemies::modifiers::armored,
	&sanguis::server::entities::enemies::modifiers::burning,
	&sanguis::server::entities::enemies::modifiers::fast,
	&sanguis::server::entities::enemies::modifiers::freezing,
	&sanguis::server::entities::enemies::modifiers::health,
	&sanguis::server::entities::enemies::modifiers::regenerating
};

}

sanguis::server::entities::enemies::modifiers::container const &
sanguis::server::entities::enemies::modifiers::create_callbacks()
{
	return
		callbacks;
}
