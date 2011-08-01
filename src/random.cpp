#include "random.hpp"
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/chrono/time_point_impl.hpp>

sanguis::rand_gen_type
sanguis::create_seeded_randgen()
{
	return
		rand_gen_type(
			sge::timer::clocks::standard::now().time_since_epoch().count()
		);
}
