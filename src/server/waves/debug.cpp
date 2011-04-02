#include "debug.hpp"
#include "spawn.hpp"

sanguis::server::waves::debug::debug()
:
	spawned_(false)
{
}

sanguis::server::waves::debug::~debug()
{
}

void 
sanguis::server::waves::debug::process(
	time_type,
	environment::object &_env,
	environment::load_context &_load_context
)
{
	if(
		spawned_
	)
		return;

	for(
		unsigned index = 0;
		index < 2;
		++index
	)
		waves::spawn(
			_env,
			_load_context,
			static_cast<
				enemy_type::type
			>(
				index
			)
		);
	
	spawned_ = true;
}

bool
sanguis::server::waves::debug::ended() const
{
	return spawned_;
}
