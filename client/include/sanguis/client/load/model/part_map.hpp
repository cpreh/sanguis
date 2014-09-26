#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_MAP_HPP_INCLUDED

#include <sanguis/client/load/model/part_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

typedef
std::map<
	fcppt::string,
	sanguis::client::load::model::part_unique_ptr
>
part_map;

}
}
}
}

#endif
