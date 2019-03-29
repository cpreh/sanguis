#ifndef SANGUIS_CLIENT_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
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
		boost::filesystem::path const &,
		sanguis::client::load::resource::textures const &,
		sanguis::client::load::resource::sounds const &,
		sanguis::model::cell_size const &,
		sanguis::model::optional_animation_delay const &,
		sanguis::model::optional_image_name const &
	);

	boost::filesystem::path const &
	path() const;

	sanguis::client::load::resource::textures const &
	textures() const;

	sanguis::client::load::resource::sounds const &
	sounds() const;

	sanguis::model::cell_size const &
	cell_size() const;

	sanguis::model::optional_animation_delay const &
	delay() const;

	sanguis::model::optional_image_name const &
	image() const;

	sanguis::client::load::model::global_parameters
	new_image(
		sanguis::model::optional_image_name const &
	) const;
private:
	boost::filesystem::path path_;

	fcppt::reference<
		sanguis::client::load::resource::textures const
	> textures_;

	fcppt::reference<
		sanguis::client::load::resource::sounds const
	> sounds_;

	sanguis::model::cell_size cell_size_;

	sanguis::model::optional_animation_delay delay_;

	sanguis::model::optional_image_name image_;
};

}
}
}
}

#endif
