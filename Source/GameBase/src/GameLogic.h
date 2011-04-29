#pragma once

#include <memory>

namespace GameBase
{
	class IActor;

	typedef unsigned int ActorId;

	class IGameLogic
	{
	public:
		virtual std::tr1::shared_ptr<IActor> VGetActor(const ActorId id) = 0;
		virtual void AddActor(shared_ptr<IActor> actor, struct ActorParams * p) = 0;
		virtual void RemoveActor(ActorId id) = 0;
		virtual void OnUpdate(float time, float elapsedTime) = 0;
	};
}