Scriptname BeinzPluginMapMarker_LoadGame extends ReferenceAlias  

BeinzPluginMapMarkersQuestScript Property MyQuest Auto
Spell property BeinzPluginMarkerSpell auto
Spell property BeinzPluginMarkerSpell_dummy auto

event OnPlayerLoadGame()
		MyQuest.ReloadLight(false)
endEvent

;event OnLoad()
;	utility.Wait(0.100000)
;	Actor ActorRef = self.GetActorReference()
;	utility.Wait(0.100000)
;	if ActorRef.HasSpell(BeinzPluginMarkerSpell_dummy as form)
;		ActorRef.RemoveSpell(BeinzPluginMarkerSpell_dummy)
;		utility.Wait(0.100000)
;		ActorRef.AddSpell(BeinzPluginMarkerSpell_dummy, true)
;	endIf
;endEvent
