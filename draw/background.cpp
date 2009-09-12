#include "background.hpp"
#include "object.hpp"
#include "system.hpp"
#include "environment.hpp"
#include "z_ordering.hpp"
#include "../client/next_id.hpp"
#include "../resolution.hpp"
#include <sge/sprite/intrusive/parameters.hpp>
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
	draw::environment const &env)
:
	entity(
		env,
		client::next_id()
	),
	tex(
		env.system().renderer()->create_texture(
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
		sge::sprite::intrusive::parameters(
			env.system(),
			z_ordering::corpses
		)
		.texture(
			sge::make_shared_ptr<
				sge::texture::part_raw
			>(
				tex
			)
		)
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

void sanguis::draw::background::paint_dead(
	draw::system &sys)
{
	sge::renderer::device_ptr const rend(
		sys.renderer()
	);
	
	sge::renderer::scoped_target const scoped_(
		rend,
		tex
	);
	
	sys.render();
}

void sanguis::draw::background::update(
	time_type)
{}
