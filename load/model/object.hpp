#ifndef SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "part.hpp"
#include <fcppt/random/uniform.hpp>
#include <fcppt/filesystem/path.hpp>
#include <sge/renderer/dim_type.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/shared_ptr.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class object
{
	typedef std::map<
		fcppt::string,
		part
	> part_map;
public:
	typedef part_map::value_type     value_type;
	typedef part_map::const_iterator const_iterator;
	typedef part_map::size_type      size_type;

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

	sge::renderer::dim_type const
	dim() const;
private:
	object(
		fcppt::filesystem::path const &,
		resource::context const &
	);
	
	void
	construct(
		resource::context const &
	);

	friend class collection;

	fcppt::filesystem::path const path;

	sge::renderer::dim_type cell_size;

	part_map parts;

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