#include "debug.hpp"
#include "spawn.hpp"

sanguis::server::waves::debug::debug()
:
	spawned(false)
{}

void 
sanguis::server::waves::debug::process(
	time_type,
	environment::object_ptr const env,
	environment::load_context_ptr const load_context
)
{
	if(spawned)
		return;

	for(unsigned i = 0; i < 2; ++i)
		spawn(
			env,
			load_context,
			static_cast<
				enemy_type::type
			>(i)
		);
	
	spawned = true;
}

bool
sanguis::server::waves::debug::ended() const
{
	return spawned;
}
