#ifndef SANGUIS_TILES_IMPL_CONTENT_PATH_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_CONTENT_PATH_HPP_INCLUDED

#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/path_reference.hpp>
#include <sanguis/tiles/impl/content_path_fwd.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

class content_path
{
public:
	content_path(
		sanguis::tiles::content const &,
		sanguis::tiles::path_reference
	);

	sanguis::tiles::content const &
	content() const;

	sanguis::tiles::path_reference const
	path() const;
private:
	sanguis::tiles::content content_;

	sanguis::tiles::path_reference path_;
};

}
}
}

#endif
