#include "infinite.hpp"
#include "../entities/spawns/limited.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/insert_parameters_pos.hpp"
#include "../environment/object.hpp"
#include <sge/time/second_f.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::waves::infinite::infinite(
	waves::delay const delay_,
	waves::spawn_interval const spawn_interval_,
	waves::spawns_per_wave const spawns_per_wave_,
	enemy_type::type const etype_
)
:
	diff_clock_(),
	delay_time_(
		sge::time::second_f(
			delay_
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	spawn_interval_(spawn_interval_),
	spawns_per_wave_(spawns_per_wave_),
	etype_(etype_)
{}

sanguis::server::waves::infinite::~infinite()
{}

void
sanguis::server::waves::infinite::process(
	time_type const diff,
	environment::object_ptr const env,
	environment::load_context_ptr const
)
{
	// TODO: the waves system must be replaced sometime

	diff_clock_.update(
		diff
	);

	if(
		delay_time_.update_b()
	)
	{
		delay_time_.deactivate();

		entities::auto_ptr spawn_(
			new entities::spawns::limited(
				etype_,
				entities::spawns::count_per_wave(
					spawns_per_wave_
				),
				entities::spawns::interval(
					sge::time::second_f(
						spawn_interval_
					)
				),
				entities::spawns::limit(
					10
				) // TODO!
			)
		);

		env->insert(
			spawn_,
			entities::insert_parameters_pos(
				pos_type::null() // TODO!
			)
		);
	}
}

bool
sanguis::server::waves::infinite::ended() const
{
	return false;
}
