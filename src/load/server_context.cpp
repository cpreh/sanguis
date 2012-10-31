#include <sanguis/load/server_context.hpp>
#include <sanguis/load/model/json_header.hpp>
#include <sanguis/load/model/load_dim.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/parse_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::load::server_context::server_context()
:
	dims_()
{}

sanguis::load::server_context::~server_context()
{}

sge::renderer::dim2 const
sanguis::load::server_context::model_dim(
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
			return it->second;
	}


	sge::parse::json::start const start_return(
		model::parse_json(
			model::make_path(
				_model_name
			)
		)
	);

	typedef std::pair<
		dim_map::iterator,
		bool
	> return_type;

	return_type const ret(
		dims_.insert(
			std::make_pair(
				_model_name,
				model::load_dim(
					model::json_header(
						start_return.object().members
					).members
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ret.second != false
	);

	return ret.first->second;
}
