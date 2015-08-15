#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/factory/make_modifiers.hpp>
#include <sanguis/server/entities/enemies/modifiers/callback.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/entities/enemies/modifiers/create_callbacks.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/create_function.hpp>
#include <sanguis/server/random/draw.hpp>
#include <sanguis/server/random/equal_function.hpp>
#include <sanguis/server/random/less_function.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::modifiers::container
sanguis::server::entities::enemies::factory::make_modifiers(
	sanguis::random_generator &_random_generator,
	sanguis::server::random::amount const _amount
)
{
	return
		sanguis::server::random::draw<
			sanguis::server::entities::enemies::modifiers::container
		>(
			_random_generator,
			sanguis::server::entities::enemies::modifiers::create_callbacks(),
			_amount,
			sanguis::server::random::create_function<
				sanguis::server::entities::enemies::modifiers::callback,
				sanguis::server::entities::enemies::modifiers::callback
			>(
				fcppt::function<
					sanguis::server::entities::enemies::modifiers::callback (
						sanguis::server::entities::enemies::modifiers::callback const &
					)
				>{
					[](
						sanguis::server::entities::enemies::modifiers::callback const &_callback
					)
					{
						return
							_callback;
					}
				}
			),
			sanguis::server::random::less_function<
				sanguis::server::entities::enemies::modifiers::callback
			>(
				fcppt::function<
					bool (
						sanguis::server::entities::enemies::modifiers::callback const &,
						sanguis::server::entities::enemies::modifiers::callback const &
					)
				>{
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
					}
				}
			),
			sanguis::server::random::equal_function<
				sanguis::server::entities::enemies::modifiers::callback
			>(
				fcppt::function<
					bool (
						sanguis::server::entities::enemies::modifiers::callback const &,
						sanguis::server::entities::enemies::modifiers::callback const &
					)
				>{
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
				}
			)
		);
}
