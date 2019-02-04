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

void ObjectManager::wireadd(const std::shared_ptr<Wire>& ptr)
{
	wires.emplace_back(ptr);
}



bool ObjectManager::update()
{
	

	//---

	//Block�̑S�̏����A�폜���s

	for (auto&& block : blocks)
	{
		block->update();
		if (block->state == IObject::SelectState::select || block->state == IObject::SelectState::d_select)
		{
			if (selectflag == true) {
				
				
				selectedBlock = block;

				selectflag = false;
				
				
			}
			else block->state = IObject::SelectState::none;			

		}
		
		if (block->gethit() == true && block->getID() ==0) { return true; }
	}

	auto iter_B = std::remove_if(blocks.begin(), blocks.end(), [](const std::shared_ptr<IObject>& ptr) {
		return ptr->getdelete();
	});
	blocks.erase(iter_B, blocks.end());

	//Wire�̑S�̏����A�폜���s

	for (auto&& wire : wires)
	{
		wire->update();

		//if(wire->grabbing()){break;}//select�܂���d_selected���L���Ȃ��΂�

		if (wire->state == IObject::SelectState::select || wire->state == IObject::SelectState::d_select)
		{
			if (selectflag == true) {


				selectedWire = wire;

				selectflag = false;


			}
			else wire->state = IObject::SelectState::none;



		}

		if (wire->gethit() == true && wire->getID() == 0) { return true; }
	}

	auto iter_W = std::remove_if(wires.begin(), wires.end(), [](const std::shared_ptr<IObject>& ptr) {
		return ptr->getdelete();
	});
	wires.erase(iter_W, wires.end());
	
	//---
	selectflag = true;
	return false;

}

void ObjectManager::draw() const
{

	//Block�̑S�̕`��
	for (const auto& block : blocks)
	{
		block->draw();
		/*if (block->gethit())
		{
			Print(block->block.pos);
		}*/
		
	}
	//Wire�̑S�̕`��
	for (const auto& wire : wires)
	{
		wire->draw();
		/*if (block->gethit())
		{
			Print(block->block.pos);
		}*/

	}


}
