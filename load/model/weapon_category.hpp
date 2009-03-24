#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "animation.hpp"
#include "global_parameters.hpp"
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
namespace model
{

class weapon_category {
public:
	animation const &
	operator[](
		animation_type::type) const;
private:
	explicit weapon_category(
		global_parameters const &);
	
	void add(
		sge::parse::ini::entry_vector const &,
		sge::string const &header,
		sge::texture::part_ptr);

	friend class part;

	typedef std::map<
		animation_type::type,
		animation
	> animation_map;

	global_parameters const param;
	animation_map animations;
};

}
}
}

#endif
