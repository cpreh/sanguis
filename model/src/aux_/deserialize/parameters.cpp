#include <sanguis/model/aux_/deserialize/parameters.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::model::aux_::deserialize::parameters::parameters(
	boost::filesystem::path const &_dir_path,
	sge::image2d::system &_image_system
)
:
	dir_path_(
		_dir_path
	),
	image_system_(
		_image_system
	)
{
}

boost::filesystem::path const &
sanguis::model::aux_::deserialize::parameters::dir_path() const
{
	return
		dir_path_;
}

sge::image2d::system &
sanguis::model::aux_::deserialize::parameters::image_system() const
{
	return
		image_system_;
}
