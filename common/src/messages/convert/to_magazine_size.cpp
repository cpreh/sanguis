#include <sanguis/magazine_type.hpp>
#include <sanguis/messages/convert/to_magazine_size.hpp>
#include <sanguis/messages/types/magazine_size.hpp>
#include <fcppt/cast/truncation_check.hpp>


sanguis::messages::types::magazine_size
sanguis::messages::convert::to_magazine_size(
	sanguis::magazine_type const _size
)
{
	return
		fcppt::cast::truncation_check<
			sanguis::messages::types::magazine_size
		>(
			_size
		);
}
