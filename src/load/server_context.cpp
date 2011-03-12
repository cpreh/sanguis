#include "server_context.hpp"
#include "model/json_header.hpp"
#include "model/load_dim.hpp"
#include "model/make_path.hpp"
#include "model/parse_json.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/assert.hpp>
#include <utility>

sanguis::load::server_context::server_context()
:
	dims_()
{}

sanguis::load::server_context::~server_context()
{}

sge::renderer::dim2 const
sanguis::load::server_context::model_dim(
	fcppt::string const &model_name
) const
{
	{
		dim_map::const_iterator const it(
			dims_.find(
				model_name
			)
		);

		if(
			it != dims_.end()
		)
			return it->second;
	}

	sge::parse::json::object object_return;

	model::parse_json(
		model::make_path(
			model_name
		),
		object_return
	);

	typedef std::pair<
		dim_map::iterator,
		bool
	> return_type;

	return_type const ret(
		dims_.insert(
			std::make_pair(
				model_name,
				model::load_dim(
					model::json_header(
						object_return.members
					).members
				)
			)
		)
	);

	FCPPT_ASSERT(
		ret.second != false
	);

	return ret.first->second;
}
