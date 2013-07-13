#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/top_result_fwd.hpp>
#include <sanguis/creator/serialize.hpp>
#include <sanguis/creator/aux/serialization/top_result.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>


void
sanguis::creator::serialize(
	fcppt::io::ostream &_stream,
	sanguis::creator::top_result const &_top_result
)
{
	if(
		!sge::parse::json::output::to_stream(
			_stream,
			sge::parse::json::start(
				sanguis::creator::aux::serialization::top_result(
					_top_result
				)
			)
		)
	)
		throw sanguis::creator::exception(
			FCPPT_TEXT("Parsing failed!")
		);
}
