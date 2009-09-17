#include "debug.hpp"
#include "spawn.hpp"

sanguis::server::waves::debug::debug()
:
	spawned(false)
{}

void 
sanguis::server::waves::debug::process(
	time_type,
	environment::object_ptr const env
)
{
	if(spawned)
		return;

	for(unsigned i = 0; i < 2; ++i)
		spawn(
			env,
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
