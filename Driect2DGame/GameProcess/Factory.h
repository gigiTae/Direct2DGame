
#include "IFactory.h"

class ManagerSet;

namespace SC
{

	class Factory : public IFactory
	{
	public:
		Factory(const ManagerSet* _managerSet);
		~Factory();

	public:

		GameObject* CreateFrontUI();
		GameObject* CreateController();
		GameObject* CreateFlySlime(Vector2 _position);
	
	private:
		const ManagerSet* m_managerSet;
	};

}