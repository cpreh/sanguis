#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED

#include "../../diff_clock.hpp"
#include "texture_context_fwd.hpp"
#include <sge/time/timer.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/texture/part_ptr.hpp>
#include <fcppt/thread/object.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/thread/future.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class texture_context_impl
{
	FCPPT_NONCOPYABLE(texture_context_impl)
public:
	texture_context_impl(
		fcppt::filesystem::path const &,
		sge::renderer::device_ptr,
		sge::image2d::multi_loader &,
		sge::renderer::filter::texture
	);
	bool update();
	void tick(
		time_type);
	sge::texture::part_ptr const result();
	void kill();
	void revive();
	bool decayed() const;
	~texture_context_impl();
private:
	typedef sge::image2d::file_ptr future_value;
	boost::packaged_task<future_value> task_;
	boost::unique_future<future_value> future_;
	fcppt::thread::object thread_;
	sge::texture::part_ptr texture_result_;
	sge::renderer::device_ptr rend_;
	sge::renderer::filter::texture filter_;
	diff_clock clock_;
	sge::time::timer decay_timer_;

	future_value const task(
		fcppt::filesystem::path const &,
		sge::image2d::multi_loader &
	);
};
}
}
}

#endif
