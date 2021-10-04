#ifndef SANGUIS_TOOLS_ANIMATIONS_PATH_MODEL_PAIR_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_PATH_MODEL_PAIR_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/path_model_pair_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis::tools::animations
{

class path_model_pair
{
	FCPPT_NONCOPYABLE(
		path_model_pair
	);
public:
	path_model_pair(
		std::filesystem::path &&,
		sanguis::model::object &&
	);

	path_model_pair(
		path_model_pair &&
	)
	noexcept;

	path_model_pair &
	operator=(
		path_model_pair &&
	)
	noexcept;

	~path_model_pair();

	[[nodiscard]]
	std::filesystem::path const &
	path() const;

	[[nodiscard]]
	sanguis::model::object &
	model();

	[[nodiscard]]
	sanguis::model::object const &
	model() const;
private:
	std::filesystem::path path_;

	sanguis::model::object model_;
};

}

#endif
