#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_BASIC_GRADIENTS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_BASIC_GRADIENTS_HPP_INCLUDED

#include "basic_gradients_fwd.hpp"
#include <mizuiro/color/object_decl.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/static_assert.hpp>
#include <map>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

template<
	typename Format,
	typename Locator,
	typename Real
>
class basic_gradients
{
	FCPPT_NONCOPYABLE(basic_gradients)
public:
	typedef mizuiro::color::object<
		Format
	> value;

	BOOST_STATIC_ASSERT(
		boost::is_floating_point<
			typename Format::channel_type
		>::value
	);

	typedef Locator locator;
	typedef Real real;

	basic_gradients();

	~basic_gradients();

	void
	add(
		locator,
		value const &
	);
	
	value const
	interpolate(
		locator
	) const;
private:
	typedef
	fcppt::container::map
	<
		std::map
		<
			locator,
			value
		>
	>
	value_map;

	value_map values_;
};

}
}
}
}

#endif
