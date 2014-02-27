#ifndef SANGUIS_MODEL_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MODEL_DESERIALIZE_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sanguis/model/symbol.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{

SANGUIS_MODEL_SYMBOL
sanguis::model::object
deserialize(
	boost::filesystem::path const &,
	sge::image2d::system &
);

}
}

#endif
