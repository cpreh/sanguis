#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_BASIC_GRADIENTS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_BASIC_GRADIENTS_IMPL_HPP_INCLUDED

#include <sanguis/client/draw2d/sunlight/basic_gradients.hpp>
#include <sanguis/client/draw2d/sunlight/lerp.hpp>
#include <mizuiro/color/operators/add.hpp>
#include <mizuiro/color/operators/scalar_multiply.hpp>
#include <mizuiro/color/operators/subtract.hpp>
#include <mizuiro/color/object_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <fcppt/config/external_end.hpp>

template<
	typename Value,
	typename Locator,
	typename Real
>
sanguis::client::draw2d::sunlight::basic_gradients<Value, Locator, Real>::basic_gradients()
{
}

template<
	typename Value,
	typename Locator,
	typename Real
>
sanguis::client::draw2d::sunlight::basic_gradients<Value, Locator, Real>::~basic_gradients()
{
}

template<
	typename Value,
	typename Locator,
	typename Real
>
void
sanguis::client::draw2d::sunlight::basic_gradients<Value, Locator, Real>::add(
	locator const r,
	value const &v
)
{
	values_.insert(
		r,
		v
	);
}

template<
	typename Value,
	typename Locator,
	typename Real
>
typename sanguis::client::draw2d::sunlight::basic_gradients<Value, Locator, Real>::value const
sanguis::client::draw2d::sunlight::basic_gradients<Value, Locator, Real>::interpolate(
	locator const r
) const
{
	FCPPT_ASSERT_ERROR(
		values_.size() > static_cast<typename value_map::size_type>(1)
	);

	typename value_map::const_iterator upper =
		values_.lower_bound(
			r
		);

	if (upper == values_.end())
		--upper;

	typename value_map::const_iterator lower =
		boost::prior(
			upper
		);

	locator const
		range =
			upper->first - lower->first,
		distance =
			r-lower->first;

	real const normalized =
		static_cast<real>(distance)
		/
		static_cast<real>(range);

	return
		sunlight::lerp(
			lower->second,
			upper->second,
			normalized
		);
}

#endif
