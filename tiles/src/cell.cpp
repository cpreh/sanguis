#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/path_reference.hpp>
#include <sanguis/tiles/pos.hpp>


sanguis::tiles::cell::cell(
	sanguis::tiles::pos const _pos,
	sanguis::tiles::content const &_content,
	sanguis::tiles::path_reference const _path
)
:
	pos_(
		_pos
	),
	content_(
		_content
	),
	path_(
		_path
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

sanguis::tiles::path_reference const
sanguis::tiles::cell::path() const
{
	return
		path_;
}
