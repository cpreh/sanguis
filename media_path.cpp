#include "media_path.hpp"
#include <sge/text.hpp>

sge::filesystem::path const
sanguis::media_path()
{
	return SGE_TEXT("media");
}
