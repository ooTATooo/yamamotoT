#pragma once

class WoodenBox : public KdGameObject
{
public:
	WoodenBox() {}
	virtual ~WoodenBox()		override {}

	void Init()				override;
	void DrawLit()			override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3 m_pos = {};
};