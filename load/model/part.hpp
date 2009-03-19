#ifndef SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED

#include "weapon_category.hpp"
#include "optional_delay.hpp"
#include "../../weapon_type.hpp"
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/math/dim/basic_decl.hpp>
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
	part(
		sge::texture::part_ptr,
		sge::renderer::dim_type const &cell_size,
		optional_delay const &opt_delay);

	void add(
		sge::parse::ini::entry_vector const &,
		sge::string const &header);

	friend class model;

	typedef std::map<
		weapon_type::type,
		weapon_category
	> category_map;

	sge::texture::part_ptr const tex;
	sge::renderer::dim_type const cell_size;
	optional_delay const opt_delay;

	category_map categories;
};

}
}
}

#endif
