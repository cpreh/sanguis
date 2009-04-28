#ifndef SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "weapon_category.hpp"
#include "global_parameters_fwd.hpp"
#include "../../weapon_type.hpp"
#include <sge/parse/json/object_fwd.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class part {
public:
	weapon_category const &
	operator[](
		weapon_type::type) const;
private:
	part(
		sge::parse::json::object const &,
		global_parameters const &);

	friend class model;

	typedef std::map<
		weapon_type::type,
		weapon_category
	> category_map;

	category_map categories;
};

}
}
}

#endif
