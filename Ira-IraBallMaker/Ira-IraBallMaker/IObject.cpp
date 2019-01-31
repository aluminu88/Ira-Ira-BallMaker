#include "IObject.h"



//ObjectManager::ObjectManager(EditGUI* _editgutptr)
//{
//}

ObjectManager::ObjectManager()
{

}

void ObjectManager::add(const std::shared_ptr<Block>& ptr)
{
	blocks.emplace_back(ptr);
}

void ObjectManager::blockadd(const std::shared_ptr<Block>& ptr)
{
	blocks.emplace_back(ptr);
}



bool ObjectManager::update()
{
	selectflag = true;

	for (auto&& block : blocks)
	{
		block->update();
		if (block->state == IObject::SelectState::select)
		{
			if (selectflag == true) {
				
				
				selectedBlock = block;

				selectflag = false;
				
				
			}
			else block->state = IObject::SelectState::none;

			

		}
		
		if (block->gethit() == true && block->getID() ==0) { return true; }
	}

	auto iter = std::remove_if(blocks.begin(), blocks.end(), [](const std::shared_ptr<IObject>& ptr) {
		return ptr->getdelete();
	});
	blocks.erase(iter, blocks.end());

	

	return false;

}

void ObjectManager::draw() const
{
	for (const auto& block : blocks)
	{
		block->draw();
		/*if (block->gethit())
		{
			Print(block->block.pos);
		}*/
		
	}
}
