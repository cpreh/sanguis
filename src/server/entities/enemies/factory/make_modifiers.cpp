#include <sanguis/random_generator.hpp>
#include <sanguis/server/draw_random.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/factory/make_modifiers.hpp>
#include <sanguis/server/entities/enemies/modifiers/agile.hpp>
#include <sanguis/server/entities/enemies/modifiers/callback.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/entities/enemies/modifiers/fast.hpp>
#include <sanguis/server/entities/enemies/modifiers/health.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::server::entities::enemies::modifiers::container const callbacks{
	&sanguis::server::entities::enemies::modifiers::health,
	&sanguis::server::entities::enemies::modifiers::fast,
	&sanguis::server::entities::enemies::modifiers::agile
};

}


sanguis::server::entities::enemies::modifiers::container
sanguis::server::entities::enemies::factory::make_modifiers(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	return
		sanguis::server::draw_random<
			sanguis::server::entities::enemies::modifiers::container
		>(
			_random_generator,
			callbacks,
			2u, // TODO: Maybe calculate the limit depending on the difficulty?
			[](
				sanguis::server::entities::enemies::modifiers::callback const &_callback
			)
			{
				return
					_callback;
			},
			[](
				sanguis::server::entities::enemies::modifiers::callback const &_callback1,
				sanguis::server::entities::enemies::modifiers::callback const &_callback2
			)
			{
				return
					std::less<
						sanguis::server::entities::enemies::modifiers::callback
					>()(
						_callback1,
						_callback2
					);
			},
			[](
				sanguis::server::entities::enemies::modifiers::callback const &_callback1,
				sanguis::server::entities::enemies::modifiers::callback const &_callback2
			)
			{
				return
					_callback1
					==
					_callback2;
			}
		);
}
