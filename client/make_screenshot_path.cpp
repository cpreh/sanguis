#include "make_screenshot_path.hpp"
#include <sge/time/time.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/text.hpp>

fcppt::filesystem::path const sanguis::client::make_screenshot_path()
{
	sge::string const type = 
		SGE_TEXT("png");
	sge::string const filename = 
		sge::lexical_cast<sge::string>(
			sge::time::time())+SGE_TEXT(".")+type;
	return fcppt::filesystem::path(filename);
}
