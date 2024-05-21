#include "Player.h"
#include "../../Scene/GameScene.h"
#include"../Bullet/Bullet.h"
void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_pos.x -= 5;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += 5;
	if (GetAsyncKeyState(VK_UP) & 0x8000)m_pos.y += 5;
	if (GetAsyncKeyState(VK_DOWN)&0x8000)m_pos.y -= 5;

	if (m_shotInterval == 0)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
			bullet->Init();
			bullet->SetOwner(m_owner);
			bullet->Shot(m_pos);
			m_owner->AddObject(bullet);
			m_shotInterval = 5;
		}
	}

	// 当たり判定 ・・・ 敵の情報が必要
	// オブジェクトリストを全て見ていく
	for (auto& obj : m_owner->GetObjList())
	{
		// 自分自身は当たり判定しない
		if (obj->GetObjType() == ObjectType::Player || obj->GetObjType() == ObjectType::Bullet) continue;

		// 敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			// 対象座標 - 自分座標 = 対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			// 球判定 ・・・ ベクトルの長さで判定
			if (v.Length() < 64.0f)
			{
				// Hit時の処理を行う
				obj->OnHit();
			}
		}
	}

	m_shotInterval--;
	if (m_shotInterval <= 0) { m_shotInterval = 0; }

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rc);
}

void Player::Init()
{
	m_tex.Load("Asset/Textures/player.png");
	m_pos = {};							// 0.0で初期化
	m_mat = Math::Matrix::Identity;		// 単位行列・・・拡大率全て1.0,他の値は全て0
	m_objType = ObjectType::Player;		// 種類は「プレイヤー」
}

void Player::Release()
{
	//テクスチャはKdTexture型のデストラクタで
	//自動ReleaseされるのでReleaseを呼ぶ必要はない
}
