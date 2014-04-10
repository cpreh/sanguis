#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path_to_json_file.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/cell_size_from_file.hpp>
#include <sanguis/server/load.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/error.hpp>
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
	fcppt::string const &_model_name
) const
{
	{
		dim_map::const_iterator const it(
			dims_.find(
				_model_name
			)
		);

		if(
			it != dims_.end()
		)
			return
				it->second;
	}

	typedef std::pair<
		dim_map::iterator,
		bool
	> return_type;

	return_type const ret(
		dims_.insert(
			std::make_pair(
				_model_name,
				sanguis::model::cell_size_from_file(
					sanguis::load::model::path_to_json_file(
						sanguis::load::model::make_path(
							_model_name
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
