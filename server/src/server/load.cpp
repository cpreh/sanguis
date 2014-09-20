#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/path_to_json_file.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/cell_size_from_file.hpp>
#include <sanguis/server/load.hpp>
#include <fcppt/container/get_or_insert.hpp>


sanguis::server::load::load()
:
	dims_()
{
}

sanguis::server::load::~load()
{
}

sanguis::model::cell_size const
sanguis::server::load::model_dim(
	sanguis::load::model::path const &_model_path
) const
{
	return
		fcppt::container::get_or_insert(
			dims_,
			_model_path,
			[](
				sanguis::load::model::path const &_path
			)
			{
				return
					sanguis::model::cell_size_from_file(
						sanguis::load::model::path_to_json_file(
							sanguis::load::model::make_path(
								_path
							)
						)
					);
			}
		);
}
