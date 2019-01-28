#include "IObject.h"



ObjectManager::ObjectManager(EditGUI* _editgutptr)
{
}

void ObjectManager::add(const std::shared_ptr<IObject>& ptr)
{
	objects.emplace_back(ptr);
}



bool ObjectManager::update()
{
	selectflag = true;

	for (auto& object : objects)
	{
		object->update();
		if (object->state == IObject::SelectState::select && selectflag==true)
		{
			if (selectflag == true) {
				selectflag = false;
				
				

			}
			else object->state = IObject::SelectState::none;
		}
		
		if (object->gethit() && object->getID()<100)return true;
	}

	auto iter = std::remove_if(objects.begin(), objects.end(), [](const std::shared_ptr<IObject>& ptr) {
		return ptr->getdelete();
	});
	objects.erase(iter, objects.end());

	

	return false;

}

void ObjectManager::draw() const
{
	for (const auto& object : objects)
	{
		object->draw();
	}
}
