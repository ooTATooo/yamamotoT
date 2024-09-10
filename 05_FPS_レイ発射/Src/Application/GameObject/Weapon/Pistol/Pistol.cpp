#include "Pistol.h"

#include "../../Effect/Explosion/Explosion.h"
#include "../../../Scene/SceneManager.h"

void Pistol::Update()
{
	if (m_shotFlg)
	{
		Math::Matrix _parentMat = Math::Matrix::Identity;
		const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
		if (_spParent)
		{
			_parentMat = _spParent->GetMatrix();
		}

		KdCollider::RayInfo _rayInfo;

		_rayInfo.m_pos = _spParent->GetPos();
		_rayInfo.m_dir = _parentMat.Backward();
		_rayInfo.m_range = 1000.0f;
		_rayInfo.m_type = KdCollider::TypeDamage;

		std::list<KdCollider::CollisionResult> retRayList;

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(_rayInfo, &retRayList);
		}

		bool _isHit;
		float _maxOverLap = 0.0f;
		Math::Vector3 _hitPos = Math::Vector3::Zero;

		for (auto& ret : retRayList)
		{
			if (maxOverLap < ret.m_overlapDistance)
			{
				_maxOverLap = ret.m_overlapDistance;
				groundPos = ret.m_hitPos;
				hit = true;
			}
		}

		if (m_rayBulletFlg)
		{
			if (_isHit)
			{
				std::shared_ptr<Explosion> exp =
			}
		}


		m_shotFlg = false;
		m_rayBulletFlg = false;
	}

	// 基底クラスの更新処理(ワールド行列作成)
	WeaponBase::Update();
}

void Pistol::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Pistol.gltf");
	}


	m_localMat = Math::Matrix::CreateTranslation(0.35f, -0.25f, 0.2f);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Pistol::ShotBullet(const bool rayFlg)
{
	m_shotFlg = true;

	m_rayBulletFlg = rayFlg;
}
