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
	environment::object_ptr const _env,
	environment::load_context_ptr const _load_context
)
{
	if(
		spawned_
	)
		return;

	for(
		unsigned i = 0;
		i < 2;
		++i
	)
		waves::spawn(
			_env,
			_load_context,
			static_cast<
				enemy_type::type
			>(
				i
			)
		);
	
	spawned_ = true;
}

bool
sanguis::server::waves::debug::ended() const
{
	return spawned_;
}
