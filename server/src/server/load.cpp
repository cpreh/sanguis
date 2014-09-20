#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/path_to_json_file.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/cell_size_from_file.hpp>
#include <sanguis/server/load.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
		fcppt::from_optional(
			fcppt::container::find_opt(
				dims_,
				_model_path
			),
			[
				this,
				&_model_path
			]()
			-> sanguis::model::cell_size &
			{
				typedef
				std::pair<
					dim_map::iterator,
					bool
				>
				return_type;

				return_type const ret(
					dims_.insert(
						std::make_pair(
							_model_path,
							sanguis::model::cell_size_from_file(
								sanguis::load::model::path_to_json_file(
									sanguis::load::model::make_path(
										_model_path
									)
								)
							)
						)
					)
				);

				FCPPT_ASSERT_ERROR(
					ret.second != false
				);

				return
					ret.first->second;
			}
		);
}
