#include "animation_pack.hpp"
#include <sge/path.hpp>

sanguis::draw::animation_pack::animation_pack(
	sge::string const& basename)
: walk_((sge::path(basename) / SGE_TEXT("run")).string()),
  attack_((sge::path(basename) / SGE_TEXT("attack")).string()),
  die_((sge::path(basename) / SGE_TEXT("die")).string())
{}

sge::string const& sanguis::draw::animation_pack::walk() const
{
	return walk_;
}

sge::string const& sanguis::draw::animation_pack::attack() const
{
	return attack_;
}

sge::string const& sanguis::draw::animation_pack::die() const
{
	return die_;
}
