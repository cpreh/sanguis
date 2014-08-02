#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/path_model_pair.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::path_model_pair::path_model_pair(
	boost::filesystem::path const &_path,
	sanguis::model::object &&_model
)
:
	path_(
		_path
	),
	model_(
		std::move(
			_model
		)
	)
{
}

sanguis::tools::animations::path_model_pair::path_model_pair(
	path_model_pair &&
) = default;

sanguis::tools::animations::path_model_pair &
sanguis::tools::animations::path_model_pair::operator=(
	path_model_pair &&
) = default;

sanguis::tools::animations::path_model_pair::~path_model_pair()
{
}

boost::filesystem::path const &
sanguis::tools::animations::path_model_pair::path() const
{
	return
		path_;
}

sanguis::model::object &
sanguis::tools::animations::path_model_pair::model()
{
	return
		model_;
}

sanguis::model::object const &
sanguis::tools::animations::path_model_pair::model() const
{
	return
		model_;
}