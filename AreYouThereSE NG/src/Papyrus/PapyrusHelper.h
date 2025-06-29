#pragma once

namespace BeinzPlugin {
	class Mod;
	class Actor;
	class ActorBase;

	std::shared_ptr<Mod> GetMod(uint32_t modIndex);
	std::shared_ptr<Actor> GetActor(uint32_t modIndex, uint32_t actorIndex);
	std::shared_ptr<ActorBase> GetActorBase(uint32_t modIndex, uint32_t actorIndex);
}