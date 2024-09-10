#include "Pistol.h"
#include"Application/Scene/SceneManager.h"
#include"Application/GameObject/Character/Player/Player.h"
#include"Application/GameObject/Effect/Explosion/Explosion.h"

void Pistol::Update()
{
	if (m_shotFlg)
	{
		if (m_wpParent.expired() == false)
		{
			std::shared_ptr<KdGameObject> _plaeyr = m_wpParent.lock();
			//地形各種とレイ判定
			//レイ判定用に必要パラメーターを設定する構造体を宣言
			KdCollider::RayInfo rayInfo;
			rayInfo.m_pos = _plaeyr->GetPos();
			rayInfo.m_dir =_plaeyr->GetMatrix().Backward() ;
			;
			rayInfo.m_range = 1000.f;
			rayInfo.m_type = KdCollider::TypeDamage;
			m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);//網の発射位置、線の方向、線の長さ
			std::list<KdCollider::CollisionResult> retRayList;
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				obj->Intersects(rayInfo, &retRayList);
			}
			bool hit = false;
			float maxOverLap = 0;
			Math::Vector3 groundPos = {};
			for (auto& ret : retRayList)
			{
				//レイが当たった場合の貫通した長さが一番長いもの探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					//着弾が速い場合
					maxOverLap = ret.m_overlapDistance;
					groundPos = ret.m_hitPos;
					hit = true;
				}
			}

			if (m_rayBulletFlg)
			{
				//当たっていたら
				if (hit)
				{
					//着弾地点にeffect発生「
					std::shared_ptr< Explosion> _exp = std::make_shared<Explosion>();
					_exp->Init();
					_exp->SetPos(groundPos);
					SceneManager::Instance().AddObject(_exp);
				}
			}
		}

		//弾の発射が終わったらフラグを見発射に戻す
		m_shotFlg = false;
		m_rayBulletFlg = false;

	}

	Math::Matrix _transMat = Math::Matrix::CreateTranslation({ 0.35f,-0.25f,0.2f });

	m_localMat = _transMat;
	//基底クラスの更新処理（ワールド行列作成）
	WeaponBase::Update();
}

void Pistol::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Pistol.gltf");
	}

}

void Pistol::ShotBullet(const bool rayFlg)
{
	//発射フラグON
	m_shotFlg = true;

	//レイ＝弾とするか？
	m_rayBulletFlg = rayFlg;

}
