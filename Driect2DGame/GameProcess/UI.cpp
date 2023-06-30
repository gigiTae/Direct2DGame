#include "GameProcessPCH.h"
#include "UI.h"

UI::UI()
	:Component(CALL_ORDER::UI,typeid(this).name())
{
}

UI::~UI()
{

}
