#include <sanguis/creator/name.hpp>
#include <sanguis/creator/start_name.hpp>
#include <fcppt/text.hpp>


sanguis::creator::name
sanguis::creator::start_name()
{
	return
		sanguis::creator::name(
			FCPPT_TEXT("start_area")
		);
}
