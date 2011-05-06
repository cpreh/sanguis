#include "serialization/result.hpp"
#include <sanguis/creator/generator/serialize.hpp>
#include <sanguis/creator/exception.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>

void
sanguis::creator::generator::serialize(
	fcppt::io::ostream &_stream,
	generator::result const &_result
)
{
	if(
		!sge::parse::json::output::to_stream(
			_stream,
			serialization::result(
				_result
			)
		)
	)
		throw creator::exception(
			FCPPT_TEXT("Parsing failed!")
		);
}
