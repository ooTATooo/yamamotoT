#include "Pistol.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Effect/Explosion/Explosion.h"
#include"../../../GameObject/Bullet/Bullet.h"

void Pistol::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Node/Pistol.gltf");
		
	}
	//m_mWorld = Math::Matrix::CreateTranslation({ 0.35f,-0.25f,0.2f });
	m_localMat = Math::Matrix::CreateTranslation({ 0.35f,-0.25f,0.2f });
	//m_localMuzzleMat = Math::Matrix::CreateTranslation({ -0.2f,0.18f,0.7f });
	//親から銃口へのローカル行列
	//「親から武器保体への相対位置」と「銃本体から銃口への相対位置」を混ぜる
	//m_localMuzzleMat *= m_localMat;

	//親から銃口へのローカル行列（相対位置）※モデルに仕込んだノード情報を使用

	//銃モデルの「AttachPoint」ノードを取得する
	if (m_spModel)
	{
		//blenderで作成したNULLポイントノードを探して取得
		const KdModelWork::Node* pNode= m_spModel->FindNode("AttachPoint");
		//指定ノードができたら
		if (pNode)
		{
			m_localMuzzleMat = pNode->m_worldTransform * m_localMat;
		}
	}


	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Pistol::Update()
{
	Math::Matrix parentMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>spParent = m_wpParent.lock();
	if (spParent)
	{
		//親の行列を取得
		parentMat = spParent->GetMatrix();
	}

	//銃口位置をデバッグ表示
	Math::Vector3 muzzlePos = (m_localMuzzleMat * parentMat).Translation();
	m_pDebugWire->AddDebugSphere(muzzlePos, 0.05f, kBlueColor);

	//弾を発射
	if (m_shotFlg)
	{
		//レイ情報
		KdCollider::RayInfo ray;
		ray.m_pos = GetPos();
		ray.m_dir = GetMatrix().Backward();//Bacwardでもいいし回転行列取ってTransFormNormalでもいい
		ray.m_range = 1000.0f;
		ray.m_type = KdCollider::TypeDamage;

		//当たったOBJの情報を格納する
		std::list<KdCollider::CollisionResult>retRayList;
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(ray, &retRayList);
		}

		bool hit = false;
		float maxOverLap = 0;
		Math::Vector3 hitPos = {};

		//当たった時
		for (auto& ret : retRayList)
		{
			if (ret.m_overlapDistance > maxOverLap)
			{
				maxOverLap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				hit = true;
			}
		}

		if (m_rayBulletFlg)
		{
			if (hit)
			{
				std::shared_ptr<Explosion>_explosion = std::make_shared<Explosion>();
				_explosion->Init();
				_explosion->SetPos(hitPos);
				SceneManager::Instance().AddObject(_explosion);
			}
		}
		//弾を飛ばす場合
		else
		{
			//レイの着眼点をを利用して弾を飛ばすベクトルを算出
			Math::Vector3 bulletDir = hitPos - muzzlePos;

			//発射
			std::shared_ptr<Bullet>_bullet = std::make_shared<Bullet>();
			_bullet->Init();
			_bullet->shot(muzzlePos, hitPos - muzzlePos);
			SceneManager::Instance().AddObject(_bullet);
		}

		//弾の発射が終わったらフラグを未発射に戻す
		m_shotFlg = false;
		m_rayBulletFlg = false;
	}

	WeaponBase::Update();
}

void Pistol::ShotBullet(const bool rayFlg)
{
	//発射フラグON
	m_shotFlg = true;

	//レイ= 弾とするか？
	m_rayBulletFlg = rayFlg;
}
