#include "serialization/result.hpp"
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generator/serialize.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/text.hpp>

void
sanguis::creator::generator::serialize(
	fcppt::io::ostream &_stream,
	sanguis::creator::generator::result const &_result
)
{
	if(
		!sge::parse::json::output::to_stream(
			_stream,
			sge::parse::json::start(
				sanguis::creator::generator::serialization::result(
					_result
				)
			)
		)
	)
		throw sanguis::creator::exception(
			FCPPT_TEXT("Parsing failed!")
		);
}
