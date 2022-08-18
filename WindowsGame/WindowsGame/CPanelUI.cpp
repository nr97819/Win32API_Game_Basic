#include "CPanelUI.h"


// 부모인 CUI가 기본생성자가 없으므로, [명시적으로] bool을 받는 생성자 호출
CPanelUI::CPanelUI() 
	: CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}
