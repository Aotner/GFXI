#include "weapon_factory.h"
#include "cannon_weapon_component.h"
#include "other_weapon_component.h"
#include "emitter_component.h"
#include  "entity.h"
#include "collider_component.h"
#include "bounding_sphere.h"
#include "render_component.h"
#include "engine_context.h"
#include "d3d\D3D11_texture.h"

using namespace Blade;

WeaponFactory::WeaponFactory()
{
	m_DescriptorWeapon1.active = true;
	m_DescriptorWeapon1.lifespan = 0.5f;
	m_DescriptorWeapon1.maxParticles = 1000.0f;
	m_DescriptorWeapon1.spawnRate = 200.0f;
	m_DescriptorWeapon1.particleSize = 1.0f;
	m_DescriptorWeapon1.velocity = Vec3f(0.01f, 0.01f, 0.01f);
	m_DescriptorWeapon1.velocityRange = 1.0f;	
	m_DescriptorWeapon1.startColor = Vec4f(1.0f,0.1f,0.0f,1.0f);
	m_DescriptorWeapon1.endColor = Vec4f(1.0f,0.1f,0.0f,0.1f);
	m_DescriptorWeapon1.blendStateType = RenderStateType::BS_BLEND_ADDITIVE;
	m_DescriptorWeapon1.externalForce = Vec3f(-5.f, -.5f, -.5f);
	m_DescriptorWeapon1.particlesToSpawn = 2000.0f;
	m_DescriptorWeapon1.spawnRadius = 1.0f;

	//#todo add new weapon descriptors
	m_DescriptorWeapon2 = m_DescriptorWeapon1;
	m_DescriptorWeapon2.startColor = Vec4f(0.0f, 1.0f, 0.0f, 1.0f);
	m_DescriptorWeapon2.endColor = Vec4f(0.0f, 1.0f, 0.0f, 0.1f);



}

Weapon* WeaponFactory::CreateWeapon1(const std::string & name)
{
	Weapon* weapon{ new Weapon{name} };
	weapon->SetPosition(Vec3f(1.0f, 1.0f, 1.0f));
	auto cwc{ new CannonWeaponComponent{weapon} };
	auto emc{ new EmitterComponent{weapon, m_DescriptorWeapon1} };
	emc->SetTexture(G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"star.jpg"));
	emc->SetMesh(G_ResourceManager.Get<Mesh>(L"plane"));
	auto cc{ new ColliderComponent(weapon,std::make_unique<BoundingSphere>(1.0f)) };
#if _DEBUG
	RenderComponent* rc{ new RenderComponent{ weapon } };
	Material material;
	material.diffuse = Vec4f{ 1.0f, 0.1f, 0.1f, 1.0f };
	material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

	rc->SetMesh(G_ResourceManager.Get<Mesh>(L"cube"));
	rc->SetMaterial(material);

#endif


	weapon->SetPosition(Vec3f(1.0f, 1.5f, 0.0f));
	return weapon;

	
}

Weapon* WeaponFactory::CreateWeapon2(const std::string & name)
{
	Weapon* weapon{ new Weapon{ name } };
	weapon->SetPosition(Vec3f(-1.0f, 1.0f, -3.0f));
	auto cwc{ new OtherWeaponComponent{ weapon } };
	auto emc{ new EmitterComponent{ weapon, m_DescriptorWeapon2 } };
	emc->SetTexture(G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"star.jpg"));
	emc->SetMesh(G_ResourceManager.Get<Mesh>(L"plane"));
	auto cc{ new ColliderComponent(weapon,std::make_unique<BoundingSphere>(1.0f)) };
#if _DEBUG
	RenderComponent* rc{ new RenderComponent{ weapon } };
	Material material;
	material.diffuse = Vec4f{ 0.0f, 1.0f, 0.1f, 1.0f };
	material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

	rc->SetMesh(G_ResourceManager.Get<Mesh>(L"cube"));
	rc->SetMaterial(material);

#endif


	weapon->SetPosition(Vec3f(1.0f, 1.5f, 0.0f));
	return weapon;
}
