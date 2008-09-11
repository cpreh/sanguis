#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/su.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/scoped_state.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/input/key_type.hpp>
#include <sge/math/matrix_util.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/scoped_connection.hpp>
#include <exception>
#include <iostream>
#include "file_to_string.hpp"

namespace
{
class input_functor
{
    public:
    input_functor(bool &running) 
        : running(running) 
    {
    }

    void operator()(sge::input::key_pair const &k) const
    {
        if (k.key().code() == sge::input::kc::key_escape)
            running = false;
    }
    private:
    bool &running;
};

class quad
{
	public:
	quad(sge::renderer::device_ptr rend,sge::math::rect const &,sge::renderer::pos3::value_type z);
	void render();
	public:
	sge::math::rect const &r;
	sge::renderer::device_ptr const rend;
	sge::renderer::vertex_buffer_ptr const vb;
	sge::renderer::index_buffer_ptr const ib;
};

void quad::render()
{
	rend->render(vb,ib,0,4,sge::renderer::indexed_primitive_type::triangle,2,0);
}

quad::quad(
	sge::renderer::device_ptr const rend,
	sge::math::rect const &r,
	sge::renderer::pos3::value_type const z)
	: r(r),
		rend(rend),
	  vb(
			rend->create_vertex_buffer(
				sge::renderer::vertex_format()
					.add(sge::renderer::vertex_usage::pos)
					.add(sge::renderer::vertex_usage::tex),
				static_cast<sge::renderer::vertex_buffer::size_type>(4),
				sge::renderer::resource_flags::dynamic)),
		ib(
			rend->create_index_buffer(
				sge::renderer::index_format::index16,
				static_cast<sge::renderer::index_buffer::size_type>(6),
				sge::renderer::resource_flags::dynamic))
{
	sge::renderer::scoped_vertex_lock const vblock(
			sge::renderer::make_scoped_lock(
				vb,
				sge::renderer::lock_flags::writeonly));
	
	sge::renderer::vertex_buffer::view_type vview = 
		boost::get<sge::renderer::vertex_buffer::view_type>(vblock.value());

	sge::renderer::vertex_buffer::view_type::iterator i = vview.begin();
	i->pos() = sge::renderer::pos3(r.left(),r.top(),z);
	i->tex() = sge::renderer::tex_pos(
		static_cast<sge::renderer::tex_pos::value_type>(0),
		static_cast<sge::renderer::tex_pos::value_type>(0));
	++i;
	i->pos() = sge::renderer::pos3(r.left(),r.bottom(),z);
	i->tex() = sge::renderer::tex_pos(
		static_cast<sge::renderer::tex_pos::value_type>(0),
		static_cast<sge::renderer::tex_pos::value_type>(1));
	++i;
	i->pos() = sge::renderer::pos3(r.right(),r.bottom(),z);
	i->tex() = sge::renderer::tex_pos(
		static_cast<sge::renderer::tex_pos::value_type>(1),
		static_cast<sge::renderer::tex_pos::value_type>(1));
	++i;
	i->pos() = sge::renderer::pos3(r.right(),r.top(),z);
	i->tex() = sge::renderer::tex_pos(
		static_cast<sge::renderer::tex_pos::value_type>(1),
		static_cast<sge::renderer::tex_pos::value_type>(0));
	
	sge::renderer::scoped_index_lock const iblock(
			sge::renderer::make_scoped_lock(
				ib,
				sge::renderer::lock_flags::writeonly));
	
	sge::renderer::index_view_16 iview = 
		boost::get<sge::renderer::index_view_16>(iblock.value());

	sge::renderer::index_view_16::iterator i2 = iview.begin();
	*i2++ = static_cast<sge::renderer::index_view_16::value_type>(0);
	*i2++ = static_cast<sge::renderer::index_view_16::value_type>(1);
	*i2++ = static_cast<sge::renderer::index_view_16::value_type>(2);
	*i2++ = static_cast<sge::renderer::index_view_16::value_type>(2);
	*i2++ = static_cast<sge::renderer::index_view_16::value_type>(3);
	*i2 =   static_cast<sge::renderer::index_view_16::value_type>(0);
}
}

int main()
try
{
    sge::systems sys;
    sys.init<sge::init::core>();
    sys.init<sge::init::image_loader>();
    sys.init<sge::init::renderer>(sge::renderer::screen_size_t(1024,768));
		sys.init<sge::init::input>();

    sge::sprite::system ss(sys.renderer);
    sge::image::object_ptr bgimage = 
        sys.image_loader->load_image(SGE_TEXT("media/grass_tile2.jpg"));

    sge::image::object_ptr swimage = 
        sys.image_loader->load_image(SGE_TEXT("media/ring.png"));

		sge::renderer::texture_ptr background_tex = 
			sys.renderer->create_texture(
				bgimage->view(),
				sge::renderer::linear_filter,
				sge::renderer::resource_flags::none);

		sge::renderer::texture_ptr sw_tex = 
			sys.renderer->create_texture(
				swimage->view(),
				sge::renderer::linear_filter,
				sge::renderer::resource_flags::none);

		sge::math::vector3 const expl_center(300,300,0);

		quad background(sys.renderer,sge::math::rect(sge::su(0),sge::su(0),sge::su(1024),sge::su(1024)),0);
		quad shockwave(sys.renderer,sge::math::rect(expl_center.x()-128,expl_center.y()-128,expl_center.x()+128,expl_center.y()+128),1);

    bool running = true;

    sge::scoped_connection conn = 
        sys.input_system->register_callback(input_functor(running));

		sge::renderer::glsl::program_ptr shader = 
			sys.renderer->create_glsl_program(file_to_string("vertex.glsl"),file_to_string("fragment.glsl"));

		sys.renderer->set_glsl_program(shader);

		sge::renderer::glsl::uniform_variable_ptr expl_center_var = shader->uniform("expl_center");
		expl_center_var->set(sge::math::vector2(expl_center.x(),expl_center.y()));

		static const int grass_id = 0;
		static const int expl_id = 1;

		sge::renderer::glsl::uniform_variable_ptr grass_sampler = shader->uniform("grasstex");
		sge::renderer::glsl::uniform_variable_ptr expl_sampler = shader->uniform("expltex");
		grass_sampler->set(grass_id);
		expl_sampler->set(expl_id);

		sys.renderer->set_glsl_program(sge::renderer::device::no_program);
		sys.renderer->projection(sge::math::matrix_orthogonal_xy());
		sys.renderer->transform(sge::renderer::matrix_pixel_to_space(sys.renderer->screen_size()));
		sge::renderer::scoped_state const state_(
			sys.renderer,
			sge::renderer::state_list
				(sge::renderer::bool_state::enable_lighting = false)
				(sge::renderer::bool_state::enable_alpha_blending = true)
				(sge::renderer::source_blend_func::src_alpha)
				(sge::renderer::dest_blend_func::inv_src_alpha)
				(sge::renderer::cull_mode::off)
				(sge::renderer::depth_func::off)
				(sge::renderer::stencil_func::off)
				(sge::renderer::draw_mode::fill)
		);

    while (running)
    {
			sge::window::dispatch();
			sge::renderer::scoped_block block_(sys.renderer);

			sys.renderer->set_glsl_program(sge::renderer::device::no_program);
			sys.renderer->set_texture(background_tex,grass_id);
			sys.renderer->set_texture(sge::renderer::device::no_texture,expl_id);
			background.render();

			sys.renderer->set_glsl_program(shader);
			sys.renderer->set_texture(background_tex,grass_id);
			sys.renderer->set_texture(sw_tex,expl_id);
			shockwave.render();
    }
} 
catch (sge::exception const &e)
{
    sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT("\n");
}
catch (std::exception const &e)
{
    std::cerr << "caught std exception: " << e.what() << "\n";
}
