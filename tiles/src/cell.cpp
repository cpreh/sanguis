#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/pos.hpp>


sanguis::tiles::cell::cell(
	sanguis::tiles::pos const _pos,
	sanguis::tiles::content const &_content
)
:
	pos_(
		_pos
	),
	content_(
		_content
	)
{
}

sanguis::tiles::pos const
sanguis::tiles::cell::pos() const
{
	return
		pos_;
}

sanguis::tiles::content const &
sanguis::tiles::cell::content() const
{
	return
		content_;
}
