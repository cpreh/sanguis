#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_PARAMETERS_HPP_INCLUDED

#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		boost::filesystem::path const &,
		sge::image2d::system &
	);

	boost::filesystem::path const &
	dir_path() const;

	sge::image2d::system &
	image_system() const;
private:
	boost::filesystem::path const dir_path_;

	sge::image2d::system &image_system_;
};

}
}
}
}

#endif
