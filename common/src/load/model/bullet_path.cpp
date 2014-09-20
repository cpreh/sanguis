#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/bullet_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::bullet_path()
{
	return
		sanguis::load::model::path{
			boost::filesystem::path{
				FCPPT_TEXT("bullet")
			}
		};
}
