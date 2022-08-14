#pragma once


class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);


// 어떤 vector 형태에 대해 Delete를 수행할 지, 알 수 없으므로 template을 이용
template<typename T> // (*) Template은 header 파일에 모두 구현해야 한다. (주의)
void Safe_Delete_Vec(vector<T>& _vec) // 원본 vec를 받아서 비워야하므로, 참조(&) 형태로 받는 것 주의
{
	// (32개 그룹 중), 특정 그룹 (eType)의 오브젝트의 memory 해제 & 그룹 vector clear()
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if(nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

