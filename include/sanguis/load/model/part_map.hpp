#ifndef SANGUIS_LOAD_MODEL_PART_MAP_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_MAP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <sanguis/load/model/part_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

typedef
std::map<
	fcppt::string,
	sanguis::load::model::part_unique_ptr
>
part_map;

}
}
}

#endif
