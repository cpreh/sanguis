#ifndef SANGUIS_MODEL_PART_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_PART_MAP_HPP_INCLUDED

#include <sanguis/model/part.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{

typedef
std::unordered_map<
	fcppt::string,
	sanguis::model::part
>
part_map;

}
}

#endif
