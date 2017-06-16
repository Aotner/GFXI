#include "player.h"
#include "engine_context.h"
#include <iostream>
#include "weapon_component.h"

using namespace Blade;

Player::Player(const std::string& name,const int id)
	: Entity(name),m_Id{id}
{
}

bool Player::AddWeapon(Weapon* weapon) noexcept
{
	if (m_WeaponCount < 2)
	{
		BLADE_TRACE("Add weapon");
		++m_WeaponCount;
		weapon->SetPosition(Vec3f(.0f,.0f,.0f));
		if (m_WeaponCount == 1)
		{
			GetEntityFromHierarchy("LeftWeaponSocket")->AddChild(weapon);
		}
		else
		{
			GetEntityFromHierarchy("RightWeaponSocket")->AddChild(weapon);
		}

		weapon->OnPickUp();
		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());
		//GetEntityFromHierarchy("LeftWeaponSocket")->AddChild(weapon);
		//AddChild(weapon);

		auto weaponComp{ static_cast<WeaponComponent*>(weapon->GetComponent("co_weapon")) };
		weaponComp->SetWeaponPosition(static_cast<WeaponPosition>(m_WeaponCount-1));
		weapon->RemoveComponent(weaponComp->GetId());
		AddComponent(weaponComp);
		weaponComp->SetParent(this);

		return true;
	}
	return false;
}

Vec3f Player::GetHeading() const noexcept
{
	//change orientation
	Quatf q = this->GetOrientation();
	Vec3f output = Vec3f(Mat4f(q) * Vec4f(0, 0, 1, 0));
	
	return output;
}

void Player::SetWeaponPositions(const Vec3f& leftWeaponPos, const Vec3f& rightWeaponPos) noexcept
{
	m_LeftWeaponPos = leftWeaponPos;

	m_RightWeaponPos = rightWeaponPos;
}

Vec3f Player::GetLeftWeaponPos() const noexcept
{
	return (GetXform() * Vec4f(m_LeftWeaponPos, 1.0f)).xyz;
}

Vec3f Player::GetRightWeaponPos() const noexcept
{
	return (GetXform() * Vec4f(m_RightWeaponPos, 1.0f)).xyz;
}

int Player::GetID() const noexcept
{
	return m_Id;
}
