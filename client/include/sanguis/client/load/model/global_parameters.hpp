#ifndef SANGUIS_CLIENT_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/resource/sounds_cref.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

class global_parameters
{
public:
	global_parameters(
		std::filesystem::path &&,
		sanguis::client::load::resource::textures_cref,
		sanguis::client::load::resource::sounds_cref,
		sanguis::model::cell_size,
		sanguis::model::optional_animation_delay,
		sanguis::model::optional_image_name &&
	);

	[[nodiscard]]
	std::filesystem::path const &
	path() const;

	[[nodiscard]]
	sanguis::client::load::resource::textures const &
	textures() const;

	[[nodiscard]]
	sanguis::client::load::resource::sounds const &
	sounds() const;

	[[nodiscard]]
	sanguis::model::cell_size const &
	cell_size() const;

	[[nodiscard]]
	sanguis::model::optional_animation_delay const &
	delay() const;

	[[nodiscard]]
	sanguis::model::optional_image_name const &
	image() const;

	[[nodiscard]]
	sanguis::client::load::model::global_parameters
	new_image(
		sanguis::model::optional_image_name &&
	) const;
private:
	std::filesystem::path path_;

	sanguis::client::load::resource::textures_cref textures_;

	sanguis::client::load::resource::sounds_cref sounds_;

	sanguis::model::cell_size cell_size_;

	sanguis::model::optional_animation_delay delay_;

	sanguis::model::optional_image_name image_;
};

}
}
}
}

#endif
