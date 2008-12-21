#ifndef SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED

#include "weapon_category.hpp"
#include "../../weapon_type.hpp"
#include <sge/path.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{
class context;
}
namespace model
{

class part {
public:
	weapon_category const &
	operator[](
		weapon_type::type) const;
private:
	sge::path path;

	part(
		sge::path const &,
		resource::context const &);

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
