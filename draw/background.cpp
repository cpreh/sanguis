#include "background.hpp"
#include "object.hpp"
#include "system.hpp"
#include "environment.hpp"
#include "z_ordering.hpp"
#include "../client/next_id.hpp"
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/make_shared_ptr.hpp>

sanguis::draw::background::background(
	draw::environment const &env)
:
	entity(
		env,
		client::next_id()),
	tex(
		env.system().renderer()->create_texture(
			sge::renderer::dim_type(
				1024,
				1024),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::none
			)),
	sprite(
		env.system(),
		z_ordering::corpses,
		sge::sprite::point::null(),
		sge::texture::const_part_ptr(
			sge::make_shared_ptr<
				sge::texture::part_raw
			>(
				tex)),
		sge::sprite::texture_dim)
{}

void sanguis::draw::background::paint_dead(
	draw::system &sys)
{
	sge::renderer::device_ptr const rend(
		sys.renderer());
	
	sge::renderer::scoped_target const scoped_(
		rend,
		tex);
	
	sys.render();
}

void sanguis::draw::background::update(
	time_type)
{}
