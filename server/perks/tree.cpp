#include "tree.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/container/tree_impl.hpp>
#include <sge/container/traversal.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>

namespace
{

struct perk_equal {
	explicit perk_equal(
		sanguis::perk_type::type);
	
	bool operator()(
		sanguis::server::perks::tree::tree_type const &) const;
private:
	sanguis::perk_type::type p;
};

}

sanguis::server::perks::tree::tree()
:
	impl(
		status()
	)
{
	// TODO: do this with assign::
	impl.push_back(
		status(
			perk_type::choleric,
			2,
			0	
		)
	);
	impl.push_back(
		status(
			perk_type::ias,
			0,
			0	
		)
	);
	impl.push_back(
		status(
			perk_type::ims,
			0,
			0
		)
	);
	impl.push_back(
		status(
			perk_type::irs,
			0,
			0
		)
	);
	impl.push_back(
		status(
			perk_type::health,
			0,
			0
		)
	);

	tree_type &health(impl.back());

	health.push_back(
		status(
			perk_type::regeneration,
			0,
			2	
		)
	);
}

sanguis::server::perks::tree::~tree()
{}

bool
sanguis::server::perks::tree::choosable(
	perk_type::type const p,
	server::level_type const player_level) const
{
	typedef 
	sge::container::traversal<
		tree_type const
	> traversal;
	
	traversal trav(
		impl
	);
	
	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			perk_equal(
				p
			)
		)
	);
	
	if(it == trav.end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_
				<< SGE_TEXT("Perk not found in tree")
		);
		return false;
	}

	if(
		it->value().required_player_level()
		> static_cast<level_type>(player_level)
	)
		return false;

	for(
		tree_type const *pos(&*it.internal());
		pos->has_parent();
		pos = &pos->parent()
	)
	{
		status const &status_(
			pos->value()
		);

		if(
			status_.required_parent_level()
			> pos->parent().value().level()
		)
			return false;
	}
	return true;
}

void
sanguis::server::perks::tree::take(
	perk_type::type const p)
{
	typedef 
	sge::container::traversal<
		tree_type
	> traversal;
	
	traversal trav(
		impl
	);
	
	traversal::iterator const it = std::find_if(
		trav.begin(),
		trav.end(),
		perk_equal(
			p
		)
	);
	
	if(it == trav.end())
		throw exception(
			SGE_TEXT("Perk not found in the tree!"));
	
	(*it).value().choose();
}

sanguis::server::perks::list const
sanguis::server::perks::tree::choosables(
	server::level_type const player_level) const
{
	// TODO: very wasteful but easy
	list ret;

	for(unsigned i = 0; i < perk_type::size; ++i)
	{
		perk_type::type const pt(
			static_cast<
				perk_type::type
			>(
				i
			)
		);

		if(
			choosable(
				pt,
				player_level
			)
		)
			ret.push_back(pt);
	}
	return ret;
}

namespace
{

perk_equal::perk_equal(
	sanguis::perk_type::type const p)
:
	p(p)
{}
	
bool
perk_equal::operator()(
	sanguis::server::perks::tree::tree_type const &t
) const
{
	return t.value().type() == p;
}

}

