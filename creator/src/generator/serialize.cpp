#include "serialization/result.hpp"
#include <sanguis/creator/generator/serialize.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>

void
sanguis::creator::generator::serialize(
	fcppt::io::ostream &_stream,
	generator::result const &_result
)
{
	sge::parse::json::output::to_stream(
		_stream,
		serialization::result(
			_result
		)
	);
}
