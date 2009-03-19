#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include "animation.hpp"
#include "optional_delay.hpp"
#include "../../animation_type.hpp"
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

class animation;

class weapon_category {
public:
	animation const &
	operator[](
		animation_type::type) const;
private:
	weapon_category(
		sge::texture::part_ptr,
		sge::renderer::dim_type const &,
		optional_delay const &);
	
	void add(
		sge::parse::ini::entry_vector const &,
		sge::string const &header);

	friend class part;

	typedef std::map<
		animation_type::type,
		animation
	> animation_map;

	sge::texture::part_ptr const tex;
	sge::renderer::dim_type const cell_size;
	optional_delay const opt_delay;

	animation_map animations;
};

}
}
}

#endif
