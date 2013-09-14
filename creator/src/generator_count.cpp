#include <sanguis/creator/generator_count.hpp>
#include <sanguis/creator/generator_count_type.hpp>
#include <sanguis/creator/aux_/generator_map.hpp>
#include <fcppt/cast/size.hpp>


sanguis::creator::generator_count_type
sanguis::creator::generator_count()
{
	return
		fcppt::cast::size<
			sanguis::creator::generator_count_type
		>(
			sanguis::creator::aux_::generator_map().size()
		);
}
