#include <sge/exception.hpp>
#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/parse/json/object.hpp>
#include <sanguis/model/aux_/deserialize/object.hpp>
#include <sanguis/model/aux_/deserialize/parameters.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::model::object
sanguis::model::deserialize(
	boost::filesystem::path const &_path,
	sge::image2d::system &_image_system
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

	return
		sanguis::model::aux_::deserialize::object(
			sanguis::model::aux_::deserialize::parameters{
				_path.parent_path(),
				_image_system
			},
			start.object()
		);
}
catch(
	sge::exception const &_error
)
{
	throw
		sanguis::model::exception{
			_error.string()
		};
}
