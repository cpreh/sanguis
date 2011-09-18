#include <sanguis/media_path.hpp>
#include <sanguis/build/media_path.hpp>

fcppt::filesystem::path const
sanguis::media_path()
{
	// TODO: cache this somewhere?
	return sanguis::build_media_path();
}
