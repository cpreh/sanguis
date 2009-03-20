#ifndef SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED

#include "weapon_category.hpp"
#include "global_parameters.hpp"
#include "../../weapon_type.hpp"
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/string.hpp>
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
	explicit part(
		global_parameters const &);

	void add(
		sge::parse::ini::entry_vector const &,
		sge::string const &header,
		sge::texture::part_ptr);

	friend class model;

	typedef std::map<
		weapon_type::type,
		weapon_category
	> category_map;

	global_parameters const param;
	category_map categories;
};

}
}
}

#endif
