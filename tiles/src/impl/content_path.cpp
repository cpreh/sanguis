#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/path_reference.hpp>
#include <sanguis/tiles/impl/content_path.hpp>


sanguis::tiles::impl::content_path::content_path(
	sanguis::tiles::content const &_content,
	sanguis::tiles::path_reference const _path
)
:
	content_(
		_content
	),
	path_(
		_path
	)
{
}

sanguis::tiles::content const &
sanguis::tiles::impl::content_path::content() const
{
	return
		content_;
}

sanguis::tiles::path_reference const
sanguis::tiles::impl::content_path::path() const
{
	return
		path_;
}
