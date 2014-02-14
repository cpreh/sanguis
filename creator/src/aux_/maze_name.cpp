#include <sanguis/creator/name.hpp>
#include <sanguis/creator/aux_/maze_name.hpp>
#include <fcppt/text.hpp>


sanguis::creator::name
sanguis::creator::aux_::maze_name()
{
	return
		sanguis::creator::name(
			FCPPT_TEXT("maze")
		);
}
