#include "bounding_sphere.h"
#include "collider_component.h"
#include "entity.h"
#include "simulation_utils.h"

using namespace Blade;


BoundingSphere::BoundingSphere(float radius):
	m_Radius{radius}
{

}

bool BoundingSphere::Collide(const Collider* collider, ContactManifold& manifold) const noexcept
{
	return collider->Collide(this, manifold);
}

const float BoundingSphere::GetRadius() const noexcept
{
	return m_Radius;
}

bool BoundingSphere::Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept
{
	return SimulationUtils::SphereAndSphereCollision(this, bsphere, manifold);
}

bool BoundingSphere::Collide(const PlaneCollider* plane, ContactManifold& manifold) const noexcept
{
	return SimulationUtils::SphereAndPlane(this, plane, manifold);
}

