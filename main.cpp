#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/random/uniform.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/math/matrix_util.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/system.hpp>
#include <sge/image/object.hpp>
#include <sge/image/loader.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/window.hpp>
#include <sge/scoped_connection.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

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
}

int main()
try
{
    sge::systems::instance const sys(
        sge::systems::list()
        (sge::renderer::parameters(
            sge::renderer::display_mode(
                sge::renderer::screen_size_t(
                    640,
                    480),
                sge::renderer::bit_depth::depth32),
            sge::renderer::depth_buffer::off,
            sge::renderer::stencil_buffer::off,
            sge::renderer::window_mode::windowed))
        (sge::systems::parameterless::input)
        (sge::systems::parameterless::image));

    sge::sprite::system ss(sys.renderer());

    sge::image::object_ptr const image = 
        sys.image_loader()->load(SGE_TEXT("media/dirt_tile.jpg"));

    sge::renderer::texture_ptr const image_texture = 
        sys.renderer()->create_texture(
            image->view(),
            sge::renderer::linear_filter,
            sge::renderer::resource_flags::readable);

    sge::sprite::object my_object(
            sge::sprite::point(0,0),
            sge::texture::part_ptr(new sge::texture::part_raw(image_texture)),
            sge::sprite::texture_dim);

    bool running = true;

    sge::scoped_connection const conn = 
        sys.input_system()->register_callback(input_functor(running));

		sge::time::timer frame_timer(sge::time::second(static_cast<sge::space_unit>(0.05)));

		sys.renderer()->set_state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::clear_backbuffer = true)
				(sge::renderer::state::color_::clear_color = sge::renderer::rgba8_color(0, 0, 0, 0))
			);

		sge::math::vector2 add(0,0);
    while (running)
    {
    	sge::window::dispatch();
    	sge::renderer::scoped_block const block_(sys.renderer());
			if (frame_timer.update_b())
			{
				static sge::random::uniform<sge::space_unit>
					rng(
						sge::random::inclusive_range<sge::space_unit>(
							sge::su(-0.1f),
							sge::su( 0.1f)));

				add.x() = rng();
				add.y() = rng();

				ss.projection(sge::math::matrix_orthogonal_xy(-1+add.x(),1+add.x(),1+add.y(),-1+add.y(),1,-1));
			}
			ss.render(my_object);
    }
} 
catch (sge::exception const &e)
{
    sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
    return EXIT_FAILURE;
}
catch (std::exception const &e)
{
    std::cerr << "caught std exception: " << e.what() << '\n';
    return EXIT_FAILURE;
}
