#include "Pistol.h"
#include"Application/Scene/SceneManager.h"
#include"Application/GameObject/Character/Player/Player.h"
#include"Application/GameObject/Effect/Explosion/Explosion.h"
#include"Application/GameObject/Bullet/Bullet.h"

void Pistol::Update()
{
	//銃口一をデバック表示
	Math::Matrix _parentMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();

	if (_spParent)
	{
		//親の行列を取得
		_parentMat = _spParent->GetMatrix();
	}
	//銃口位置をデバック表示
	Math::Vector3 _muzzlePos = (m_localMuzzleMat*_parentMat).Translation();
	m_pDebugWire->AddDebugSphere(_muzzlePos, .5f, kBlueColor);
	
	
	if (m_shotFlg)
	{
		if (m_wpParent.expired() == false)
		{
			std::shared_ptr<KdGameObject> _plaeyr = m_wpParent.lock();
			//地形各種とレイ判定
			//レイ判定用に必要パラメーターを設定する構造体を宣言
			KdCollider::RayInfo rayInfo;
			rayInfo.m_pos = _plaeyr->GetPos();
			rayInfo.m_dir = _plaeyr->GetMatrix().Backward() ;
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

			//レイを弾として扱う場合
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
			else //弾を飛ばす場合
			{
				//レイの着弾地点を利用して弾を飛ばすスベクトルを算出
				Math::Vector3 _bulletDir = {};
				_bulletDir = groundPos - _muzzlePos;

				//発射
				std::shared_ptr<Bullet> _bullet = std::make_shared<Bullet>();
				_bullet->Init();
				_bullet->Shot(_muzzlePos, _bulletDir);
				SceneManager::Instance().AddObject(_bullet);
			}
		}

		//弾の発射が終わったらフラグを見発射に戻す
		m_shotFlg = false;
		m_rayBulletFlg = false;

	}

	m_localMat = Math::Matrix::CreateTranslation({ 0.35f,-0.25f,0.2f });

	
	//基底クラスの更新処理（ワールド行列作成）
	WeaponBase::Update();
	//ヌルポイントノード
}

void Pistol::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Pistol.gltf");
	}

	//親から重工へのローカル行列（相対位置）
	//親から武器本体への相対位置と銃本体から受講への相対値
	//m_localMuzzleMat=Math::Matrix::CreateTranslation
	m_localMat = Math::Matrix::CreateTranslation({ 0.35f,-0.25f,-.2f });
	m_localMuzzleMat = Math::Matrix::CreateTranslation({ 0.0f,0.18f,-.7f });

	m_localMuzzleMat *= m_localMat;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Pistol::ShotBullet(const bool rayFlg)
{
	//発射フラグON
	m_shotFlg = true;

	//レイ＝弾とするか？
	m_rayBulletFlg = rayFlg;

}
