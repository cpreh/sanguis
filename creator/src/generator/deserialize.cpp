#include "deserialization/result.hpp"
#include <sanguis/creator/generator/deserialize.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <fcppt/text.hpp>


sanguis::creator::generator::result const
sanguis::creator::generator::deserialize(
	fcppt::io::istream &_stream
)
{
	sge::parse::json::start ret;

	if(
		!sge::parse::json::parse_stream(
			_stream,
			ret
		)
	)
		throw sanguis::creator::exception(
			FCPPT_TEXT("Deserialize failed!")
		);

	return
		sanguis::creator::generator::deserialization::result(
			ret.object()
		);
}
