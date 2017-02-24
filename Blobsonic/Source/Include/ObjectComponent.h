#pragma once

/**
* @class	ObjectComponent
* @brief	Abstract class for components attached to game object 
* @Author	Rozen Savilla
*/

namespace OC {

	class ObjectComponent {
	private:
		bool m_bGlobalMsgs;	//!< Flag has access to global msgs
		bool m_bLocalMsgs;	//!< Flag has access to local msgs

		unsigned int m_uiHandle; //Object index
	protected:
		std::vector<std::unique_ptr<ObjectComponent>> m_vptrComponents;		//!< Stores all components object has.

		std::vector<std::shared_ptr<Message>>* m_vptrGlobalMessages;			//!< Messages passed to game objects for Components to read
		std::vector<std::shared_ptr<Message>>* m_vptrLocalMessages;			//!< Messages created by this objects components, will be read by other attached components
	public:

		void setGlobalMessagePtr(std::shared_ptr<Message> ptrGlobalMsg);
		void setLocalMessagePtr(std::shared_ptr<Message> ptrLocallMsg);

		void sendLocalMsg(std::shared_ptr<Message> msg);
		void setGlobalMsg(std::shared_ptr<Message> msg);

		virtual void handleMessage(std::shared_ptr<Message> msg) = 0;

		virtual void update(float dt) = 0;

		void attachComponent(std::unique_ptr<ObjectComponent> newComponent);
		void attachGlobalMsg(std::vector<std::shared_ptr<Message>>* vptrMsgs);
		void attachLocalMsg(std::vector<std::shared_ptr<Message>>* vptrMsgs);
	};

}