#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include "animation.hpp"
#include "base_animation_not_found.hpp"
#include "../../animation_type.hpp"
#include <sge/filesystem/path.hpp>
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

class weapon_category {
public:
	animation const &
	operator[](
		animation_type::type) const;
private:
	sge::filesystem::path path;
	
	weapon_category(
		sge::filesystem::path const &,
		resource::context const &);

	friend class part;

	typedef std::map<
		animation_type::type,
		animation
	> animation_map;

	animation_map animations;
};

}
}
}

#endif
