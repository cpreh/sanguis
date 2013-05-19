#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/deserialize.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/aux/deserialization/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/istream.hpp>


sanguis::creator::result const
sanguis::creator::deserialize(
	fcppt::io::istream &_stream
)
{
	sge::parse::json::start result;

	sge::parse::result const ret(
		sge::parse::json::parse_stream(
			_stream,
			result
		)
	);

	if(
		ret.result_code()
		!=
		sge::parse::result_code::ok
	)
		throw sanguis::creator::exception(
			FCPPT_TEXT("Deserialize failed! ")
			+
			ret.error_string()->get()
		);

	return
		sanguis::creator::aux::deserialization::result(
			result.object()
		);
}
