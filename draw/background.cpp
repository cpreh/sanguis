#include "background.hpp"
#include "environment.hpp"
#include "z_ordering.hpp"
#include "sprite/normal/parameters.hpp"
#include "../client/next_id.hpp"
#include "../resolution.hpp"
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/image/algorithm/fill.hpp>
#include <sge/image/colors.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>

sanguis::draw::background::background(
	draw::environment const &env
)
:
	entity(
		env,
		client::next_id()
	),
	tex(
		env.client_system().renderer()->create_texture(
			sge::math::dim::structure_cast<
				sge::renderer::dim_type
			>(
				resolution() // FIXME: this sould be a power of 2!
			),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::none
		)
	),
	sprite(
		sprite::normal::parameters()
		.system(
			&env.normal_system()
		)
		.order(
			z_ordering::corpses
		)
		.texture(
			sge::make_shared_ptr<
				sge::texture::part_raw
			>(
				tex
			)
		)
		.pos(
			sprite::point::null()
		)
		.texture_size()
		.elements()
	)
{
	sge::image::algorithm::fill(
		sge::renderer::scoped_texture_lock(
			tex,
			sge::renderer::lock_mode::writeonly)
		.value(),
		sge::image::colors::transparent()
	);
}

sanguis::draw::background::~background()
{}

void
sanguis::draw::background::paint_dead(
	draw::sprite::normal::system &sys
)
{
	sge::renderer::device_ptr const rend(
		sys.renderer()
	);
	
	sge::renderer::scoped_target const scoped_(
		rend,
		tex
	);
	
	sys.render_all(
		sge::sprite::default_equal()
	);
}

void
sanguis::draw::background::update(
	time_type
)
{}
