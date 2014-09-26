#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/load/destructible_name.hpp>
#include <sanguis/load/model/destructible_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::destructible_path(
	sanguis::creator::destructible_type const _type
)
{
	return
		sanguis::load::model::path{
			boost::filesystem::path{
				FCPPT_TEXT("destructibles")
			}
			/
			sanguis::load::destructible_name(
				_type
			)
		};
}
