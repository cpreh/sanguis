#include "random.hpp"
#include <sge/time/now.hpp>

sanguis::rand_gen_type
sanguis::create_seeded_randgen()
{
	return
		rand_gen_type(
			static_cast<
				unsigned long
			>(
				sge::time::now().time_since_epoch().count()
			)
		);
}
