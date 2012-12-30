#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_BASIC_GRADIENTS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_BASIC_GRADIENTS_HPP_INCLUDED

#include <sanguis/client/draw2d/sunlight/basic_gradients_fwd.hpp>
#include <mizuiro/color/object_decl.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


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
	FCPPT_NONCOPYABLE(
		basic_gradients
	);
public:
	typedef mizuiro::color::object<
		Format
	> value;

	static_assert(
		std::is_floating_point<
			typename Format::channel_type
		>::value,
		"Format::channel_type must be a floating point type"
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
