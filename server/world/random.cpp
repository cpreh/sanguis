#include "random.hpp"
#include "object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	context_ptr const ctx_,
	sge::collision::system_ptr const collision_system_,
	server::environment::load_context_ptr const load_context_,
	server::console &console_
)
{
	// TODO:
	return
		fcppt::make_unique_ptr<
			object
		>(
			ctx_,
			collision_system_,
			load_context_,
			std::tr1::ref(
				console_
			)
		);
}
