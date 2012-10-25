#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED

#include <sanguis/load/resource/texture_context_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_shared_ptr.hpp>
#include <sge/image2d/file_shared_ptr.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/texture/part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/thread/future.hpp>
#include <boost/thread/thread.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace resource
{

class texture_context_impl
{
	FCPPT_NONCOPYABLE(
		texture_context_impl
	);
public:
	texture_context_impl(
		boost::filesystem::path const &,
		sge::renderer::device::core &,
		sge::image2d::system &
	);

	bool
	update();

	sge::renderer::texture::planar_shared_ptr const
	result();

	~texture_context_impl();
private:
	typedef sge::image2d::file_shared_ptr future_value;

	boost::packaged_task<future_value> task_;

	boost::unique_future<future_value> future_;

	boost::thread thread_;

	sge::renderer::texture::planar_shared_ptr texture_result_;

	sge::renderer::device::core &rend_;

	future_value const task(
		boost::filesystem::path const &,
		sge::image2d::system &
	);
};

}
}
}

#endif
