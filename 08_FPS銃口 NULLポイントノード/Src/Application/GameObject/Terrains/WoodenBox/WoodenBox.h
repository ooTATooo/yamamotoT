#pragma once

class WoodenBox : public KdGameObject
{
public:
	WoodenBox() {}
	virtual ~WoodenBox()		override {}

	void Init()				override;
	void DrawLit()			override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};