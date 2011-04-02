#include "random.hpp"
#include "object.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	world::context &_ctx,
	server::environment::load_context &_load_context,
	server::console &_console
)
{
	// TODO:
	return
		fcppt::make_unique_ptr<
			object
		>(
			fcppt::ref(
				_ctx
			),
			fcppt::ref(
				_load_context
			),
			fcppt::ref(
				_console
			)
		);
}
