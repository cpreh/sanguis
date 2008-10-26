#ifndef SANGUIS_DRAW_SPRITE_PART_INDEX_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_PART_INDEX_HPP_INCLUDED

#include <cstddef>

namespace sanguis
{
namespace draw
{

class sprite_part_index {
public:
	typedef std::size_t value_type;

	explicit sprite_part_index(
		value_type);
	
	value_type get() const;
private:
	value_type value;
};

}
}

#endif
