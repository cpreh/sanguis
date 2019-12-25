#ifndef SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_HPP_INCLUDED

#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/cursor/object.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
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
		sge::input::processor &,
		sanguis::client::load::resource::textures const &
	);

	~cursor();

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	sge::texture::part const &texture_;

	sge::cursor::object cursor_;
};

}
}

#endif
