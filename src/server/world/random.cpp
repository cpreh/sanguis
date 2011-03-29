#include "random.hpp"
#include "object.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	context_ptr const _ctx,
	server::environment::load_context_ptr const _load_context,
	server::console &_console
)
{
	// TODO:
	return
		fcppt::make_unique_ptr<
			object
		>(
			_ctx,
			_load_context,
			fcppt::ref(
				_console
			)
		);
}
