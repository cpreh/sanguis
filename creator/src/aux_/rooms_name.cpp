#include <sanguis/creator/name.hpp>
#include <sanguis/creator/aux_/rooms_name.hpp>
#include <fcppt/text.hpp>


sanguis::creator::name
sanguis::creator::aux_::rooms_name()
{
	return
		sanguis::creator::name(
			FCPPT_TEXT("rooms")
		);
}
