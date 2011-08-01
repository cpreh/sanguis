#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED

#include "texture_context_fwd.hpp"
#include <sge/renderer/device_fwd.hpp>
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
	FCPPT_NONCOPYABLE(
		texture_context_impl
	);
public:
	texture_context_impl(
		fcppt::filesystem::path const &,
		sge::renderer::device &,
		sge::image2d::multi_loader &
	);

	bool
	update();

	sge::texture::part_ptr const
	result();

	~texture_context_impl();
private:
	typedef sge::image2d::file_ptr future_value;

	boost::packaged_task<future_value> task_;

	boost::unique_future<future_value> future_;

	fcppt::thread::object thread_;

	sge::texture::part_ptr texture_result_;

	sge::renderer::device &rend_;

	future_value const task(
		fcppt::filesystem::path const &,
		sge::image2d::multi_loader &
	);
};

}
}
}

#endif
