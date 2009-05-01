#include "infinite.hpp"
#include "simple.hpp"

sanguis::server::waves::infinite::infinite(
	time_type const delay_,
	time_type const spawn_interval_,
	unsigned const waves_,
	unsigned const spawns_per_wave_,
	enemy_type::type const etype_)
:
	delay_(delay_),
	spawn_interval_(spawn_interval_),
	waves_(waves_),
	spawns_per_wave_(spawns_per_wave_),
	etype_(etype_),
	simple_(
		new simple(
			delay_,
			spawn_interval_,
			waves_,
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
	environment const &env)
{
	simple_->process(
		diff,
		env
	);

	if(simple_->ended())
	{
		// TODO: which kind of progression do we want here?
		simple_.reset(
			new simple(
				delay_,
				spawn_interval_,
				waves_,
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
