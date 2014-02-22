#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/aux_/deserialize/animation_delay.hpp>
#include <sanguis/model/aux_/deserialize/cell_size.hpp>
#include <sanguis/model/aux_/deserialize/parts.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::model::object
sanguis::model::deserialize(
	boost::filesystem::path const &_path
)
try
{
	sge::parse::json::start const start{
		sge::parse::json::parse_file_exn(
			_path
		)
	};

	if(
		!fcppt::variant::holds_type<
			sge::parse::json::object
		>(
			start.variant
		)
	)
		throw
			sanguis::model::exception{
				FCPPT_TEXT("The outermost element must be an object")
			};

	sge::parse::json::object const &object{
		start.object()
	};

	return
		sanguis::model::object{
			sanguis::model::aux_::deserialize::cell_size(
				object
			),
			sanguis::model::aux_::deserialize::animation_delay(
				object
			),
			sanguis::model::aux_::deserialize::parts(
				object
			)
		};
}
catch(
	sge::parse::exception const &_error
)
{
	throw
		sanguis::model::exception{
			_error.string()
		};
}
