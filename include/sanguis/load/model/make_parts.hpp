#ifndef SANGUIS_LOAD_MODEL_MAKE_PARTS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_PARTS_HPP_INCLUDED

#include <sanguis/load/resource/context_fwd.hpp>
#include <sanguis/load/model/part_result_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::part_result
make_parts(
	boost::filesystem::path const &,
	sanguis::load::resource::context const &
);

}
}
}

#endif
