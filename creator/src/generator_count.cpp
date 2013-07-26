#include <sanguis/creator/generator_count.hpp>
#include <sanguis/creator/generator_count_type.hpp>
#include <sanguis/creator/aux/generator_map.hpp>


sanguis::creator::generator_count_type
sanguis::creator::generator_count()
{
	return
		static_cast<
			sanguis::creator::generator_count_type
		>(
			sanguis::creator::aux::generator_map().size()
		);
}
