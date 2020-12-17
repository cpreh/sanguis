#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/is_background.hpp>
#include <sanguis/tiles/path_reference.hpp>
#include <sanguis/tiles/pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tiles::cell::cell(
	sanguis::tiles::pos _pos,
	sanguis::tiles::content const &_content,
	sanguis::tiles::path_reference const _path,
	sanguis::tiles::is_background const _is_background
)
:
	pos_(
		std::move(
			_pos
		)
	),
	content_(
		_content
	),
	path_(
		_path
	),
	is_background_(
		_is_background
	)
{
}

sanguis::tiles::pos
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

sanguis::tiles::path_reference
sanguis::tiles::cell::path() const
{
	return
		path_;
}

sanguis::tiles::is_background
sanguis::tiles::cell::is_background() const
{
	return
		is_background_;
}
