#include "infinite.hpp"
#include "simple.hpp"

sanguis::server::waves::infinite::infinite(
	waves::delay const delay_,
	waves::spawn_interval const spawn_interval_,
	waves::count const count_,
	waves::spawns_per_wave const spawns_per_wave_,
	enemy_type::type const etype_
)
:
	delay_(delay_),
	spawn_interval_(spawn_interval_),
	count_(count_),
	spawns_per_wave_(spawns_per_wave_),
	etype_(etype_),
	simple_(
		new simple(
			delay_,
			spawn_interval_,
			count_,
			spawns_per_wave_,
			etype_
		)
	)
{}

sanguis::server::waves::infinite::~infinite()
{}

void
sanguis::server::waves::infinite::process(
	time_type const diff,
	environment::object_ptr const env,
	environment::load_context_ptr const load_context
)
{
	simple_->process(
		diff,
		env,
		load_context
	);

	if(simple_->ended())
	{
		// TODO: which kind of progression do we want here?
		simple_.reset(
			new simple(
				delay_ *= static_cast<time_type>(0.99f),
				spawn_interval_ *= static_cast<time_type>(0.99f),
				count_,
				spawns_per_wave_,
				etype_
			)
		);
	}
}

bool
sanguis::server::waves::infinite::ended() const
{
	return false;
}
