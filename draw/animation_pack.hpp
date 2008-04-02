#ifndef SANGUIS_DRAW_ANIMATION_PACK_HPP_INCLUDED
#define SANGUIS_DRAW_ANIMATION_PACK_HPP_INCLUDED

#include <sge/string.hpp>

namespace sanguis
{
namespace draw
{

class animation_pack {
public:
	explicit animation_pack(
		sge::string const& basename);

	sge::string const& walk() const;
	sge::string const& attack() const;
	sge::string const& die() const;
private:
	sge::string const walk_,
	                  attack_,
	                  die_;
};

}
}

#endif
