#include <sanguis/doodad_type.hpp>
#include <sanguis/load/doodad_name.hpp>
#include <sanguis/load/model/doodad_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::doodad_path(
	sanguis::doodad_type const _type
)
{
	return
		sanguis::load::model::path{
			boost::filesystem::path{
				FCPPT_TEXT("doodads")
			}
			/
			sanguis::load::doodad_name(
				_type
			)
		};
}
