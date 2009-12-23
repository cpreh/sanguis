#include "make_screenshot_path.hpp"
#include <sge/time/time.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>

fcppt::filesystem::path const sanguis::client::make_screenshot_path()
{
	sge::string const type = 
		FCPPT_TEXT("png");
	sge::string const filename = 
		fcppt::lexical_cast<sge::string>(
			sge::time::time())+FCPPT_TEXT(".")+type;
	return fcppt::filesystem::path(filename);
}
