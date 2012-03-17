#ifndef SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/load/model/object_fwd.hpp>
#include <sanguis/load/model/part_fwd.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <fcppt/random/uniform.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class object
{
	typedef boost::ptr_map<
		fcppt::string,
		part
	> part_map;

	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef part_map::value_type value_type;

	typedef part_map::const_reference const_reference;

	typedef part_map::const_iterator const_iterator;

	typedef part_map::size_type size_type;

	~object();

	part const &
	operator[](
		fcppt::string const &
	) const;

	part const &
	random_part() const;

	size_type
	size() const;

	const_iterator
	begin() const;

	const_iterator
	end() const;

	sge::renderer::dim2 const
	dim() const;

	object(
		boost::filesystem::path const &,
		resource::context const &
	);
private:
	void
	construct(
		resource::context const &
	);

	friend class collection;

	boost::filesystem::path const path_;

	sge::renderer::dim2 cell_size_;

	part_map parts_;

	typedef fcppt::random::uniform<
		part_map::size_type
	> part_rand;

	mutable fcppt::shared_ptr<
		part_rand
	> random_part_;
};

}
}
}

#endif
