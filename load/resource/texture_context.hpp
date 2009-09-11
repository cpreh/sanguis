#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_HPP_INCLUDED

#include "texture_context_fwd.hpp"
#include <sge/thread/future/packaged_task.hpp>
#include <sge/thread/future/shared_object.hpp>
#include <sge/thread/object.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <sge/texture/part_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class texture_context
{
SGE_NONCOPYABLE(texture_context)
public:
	texture_context(
		sge::filesystem::path const &,
		sge::renderer::device_ptr,
		sge::image::loader_ptr,
		sge::renderer::filter::texture);
	bool update();
	sge::texture::part_ptr const result();
private:
	sge::thread::future::packaged_task<sge::texture::part_ptr> task_;
	sge::thread::future::shared_object<sge::texture::part_ptr> future_;
	//sge::thread::object thread_;
	sge::texture::part_ptr debug_result_;

	sge::texture::part_ptr const task(
		sge::filesystem::path const &,
		sge::renderer::device_ptr,
		sge::image::loader_ptr,
		sge::renderer::filter::texture);
};
}
}
}

#endif
