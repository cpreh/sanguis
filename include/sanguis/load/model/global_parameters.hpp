#ifndef SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED

#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

class global_parameters
{
	FCPPT_NONASSIGNABLE(
		global_parameters
	);
public:
	global_parameters(
		boost::filesystem::path const &,
		sanguis::load::resource::textures const &,
		sanguis::load::resource::sounds const &,
		sanguis::load::model::cell_size const &,
		sanguis::model::optional_animation_delay const &,
		sanguis::model::optional_image_name const &
	);

	boost::filesystem::path const &
	path() const;

	sanguis::load::resource::textures const &
	textures() const;

	sanguis::load::resource::sounds const &
	sounds() const;

	sanguis::load::model::cell_size const &
	cell_size() const;

	sanguis::model::optional_animation_delay const &
	delay() const;

	sanguis::model::optional_image_name const &
	image() const;

	sanguis::load::model::global_parameters
	new_image(
		sanguis::model::optional_image_name const &
	) const;
private:
	boost::filesystem::path const path_;

	sanguis::load::resource::textures const &textures_;

	sanguis::load::resource::sounds const &sounds_;

	sanguis::load::model::cell_size const cell_size_;

	sanguis::model::optional_animation_delay const delay_;

	sanguis::model::optional_image_name const image_;
};

}
}
}

#endif
