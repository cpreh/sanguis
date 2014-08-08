#ifndef SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_HPP_INCLUDED

#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/custom_cursor.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{

class cursor
{
	FCPPT_NONCOPYABLE(
		cursor
	);
public:
	cursor(
		sge::renderer::device::ffp &,
		sge::input::cursor::object &,
		sanguis::client::load::resource::textures const &
	);

	~cursor();

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	sge::texture::const_part_shared_ptr const texture_;

	sge::systems::custom_cursor cursor_;
};

}
}

#endif
