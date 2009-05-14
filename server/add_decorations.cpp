#include "add_decorations.hpp"
#include "../resolution.hpp"
#include "../decoration_type.hpp"
#include "entities/decoration.hpp"
#include <sge/math/twopi.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/random/uniform.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/random/last_exclusive_range.hpp>

void sanguis::server::add_decorations(
	environment const &env)
{
	sge::random::uniform<
		space_unit
	>
		rng_x(
			sge::random::make_inclusive_range(
				static_cast<space_unit>(0),
				static_cast<space_unit>(resolution().w())
			)
		),
		rng_y(
			sge::random::make_inclusive_range(
				static_cast<space_unit>(0),
				static_cast<space_unit>(resolution().h())
			)
		),
		rng_angle(
			sge::random::make_inclusive_range(
				static_cast<space_unit>(0),
				sge::math::twopi<space_unit>()
			)
		);

	sge::random::uniform<
		unsigned
	> rng_deco_type(
		sge::random::make_last_exclusive_range(
			static_cast<unsigned>(0),
			static_cast<unsigned>(decoration_type::size)
		)
	);

	for (unsigned i = 0; i < 10; ++i)
		env.insert()(
			entities::auto_ptr(
				new entities::decoration(
					env,
					pos_type(
						rng_x(),
						rng_y()
					),
					space_unit(
						rng_angle()
					),
					static_cast<decoration_type::type>(
						rng_deco_type()
					)
				)
			)
		);
}
