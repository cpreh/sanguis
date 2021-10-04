#ifndef SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_HPP_INCLUDED

#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sge/cursor/object.hpp>
#include <sge/input/const_processor_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client
{

class cursor
{
	FCPPT_NONMOVABLE(
		cursor
	);
public:
	cursor(
		sge::renderer::device::ffp_ref,
		sge::input::const_processor_ref,
		sanguis::client::load::resource::textures_cref
	);

	~cursor();

	void
	draw(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)
private:
	sge::texture::const_part_ref const texture_;

	sge::cursor::object cursor_;
};

}

#endif
