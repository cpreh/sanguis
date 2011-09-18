#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_INDEX_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_INDEX_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

class index
{
public:
	typedef std::size_t value_type;

	explicit index(
		value_type
	);

	value_type
	get() const;
private:
	value_type value_;
};

}
}
}
}

#endif
