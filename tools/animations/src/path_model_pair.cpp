#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/path_model_pair.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::path_model_pair::path_model_pair(
	std::filesystem::path &&_path,
	sanguis::model::object &&_model
)
:
	path_(
		std::move(
			_path
		)
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
)
noexcept
= default;

sanguis::tools::animations::path_model_pair &
sanguis::tools::animations::path_model_pair::operator=(
	path_model_pair &&
)
noexcept
= default;

sanguis::tools::animations::path_model_pair::~path_model_pair()
= default;

std::filesystem::path const &
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
