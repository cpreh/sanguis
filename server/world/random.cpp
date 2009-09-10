#include "random.hpp"
#include <sge/make_auto_ptr.hpp>

sanguis::server::world::object_auto_ptr
sanguis::server::world::random(
	global::context_ptr const ctx
)
{
	// TODO:
	return sge::make_auto_ptr<
		object
	>(
		ctx
	);
}
