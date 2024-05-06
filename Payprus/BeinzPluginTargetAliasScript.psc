scriptName BeinzPluginTargetAliasScript extends ReferenceAlias

;-- Properties --------------------------------------
Spell property BeinzPluginMarkerSpellTarget auto
Spell property BeinzPluginMarkerSpellTarget_dummy auto

;-- Variables ---------------------------------------
Actor ActorRef

;-- Functions ---------------------------------------

function Onload()

	utility.Wait(0.100000)
	ActorRef = self.GetActorReference()
	utility.Wait(0.100000)
	if ActorRef.HasSpell(BeinzPluginMarkerSpellTarget_dummy as form)
		ActorRef.RemoveSpell(BeinzPluginMarkerSpellTarget_dummy)
		utility.Wait(0.100000)
		ActorRef.AddSpell(BeinzPluginMarkerSpellTarget_dummy, true)
	elseIf ActorRef.HasSpell(BeinzPluginMarkerSpellTarget as form)
		ActorRef.RemoveSpell(BeinzPluginMarkerSpellTarget)
		utility.Wait(0.100000)
		ActorRef.AddSpell(BeinzPluginMarkerSpellTarget, true)
	endIf
endFunction

function OnDeath(Actor akKiller)

	ActorRef = self.GetActorReference()
	utility.Wait(0.100000)
	if ActorRef.HasSpell(BeinzPluginMarkerSpellTarget_dummy as form)
		ActorRef.RemoveSpell(BeinzPluginMarkerSpellTarget_dummy)
	elseIf ActorRef.HasSpell(BeinzPluginMarkerSpellTarget as form)
		ActorRef.RemoveSpell(BeinzPluginMarkerSpellTarget)
	endIf
	self.Clear()
endFunction
