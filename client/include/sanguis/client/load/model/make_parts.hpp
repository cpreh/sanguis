#ifndef SANGUIS_CLIENT_LOAD_MODEL_MAKE_PARTS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_MAKE_PARTS_HPP_INCLUDED

#include <sanguis/client/load/model/part_result_fwd.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
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

sanguis::client::load::model::part_result
make_parts(
	fcppt::log::object &,
	std::filesystem::path const &,
	sanguis::client::load::resource::context const &
);

}
}
}
}

#endif
