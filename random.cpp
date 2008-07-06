#include "random.hpp"
#include <sge/time/time.hpp>

sanguis::rand_gen_type
sanguis::create_seeded_randgen()
{
	return rand_gen_type(sge::time::time());
}
