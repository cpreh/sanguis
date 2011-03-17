#include "random.hpp"
#include "object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	context_ptr const _ctx,
	sge::collision::system_ptr const _collision_system,
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
			_collision_system,
			_load_context,
			std::tr1::ref(
				_console
			)
		);
}
