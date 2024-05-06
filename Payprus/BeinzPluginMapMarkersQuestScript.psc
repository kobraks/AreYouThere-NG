Scriptname BeinzPluginMapMarkersQuestScript extends Quest  

Spell Property BeinzPluginMarkerSpell Auto
Spell Property BeinzPluginMarkerSpellTarget Auto

Spell property BeinzPluginMarkerSpell_dummy auto
Spell property BeinzPluginMarkerSpellTarget_dummy auto

import Game
import Debug

Event OnInit()
				;debug.Trace("Beinz Face Map marker OnInit()")
		;Game.GetPlayer().AddSpell(BeinzPluginMarkerSpell)
		;Game.GetPlayer().AddSpell(BeinzPluginMarkerSpellTarget)
	Parent.SetActive(true)
EndEvent

function ReloadLight(bool bForceSpell)
				;debug.Trace("Beinz Face Map marker ReloadLight()")
	ReferenceAlias refAlias
	int iIndex
	Actor ActorRef
		iIndex = 1
		While iIndex < GetNumAliases()
			refAlias = GetNthAlias(iIndex) as ReferenceAlias
			ActorRef = refAlias.GetActorReference()
			If ActorRef == none
					;debug.Trace("Beinz Face Map marker ReloadLight() - remove invlid alias")
					refAlias.Clear()
					SetObjectiveDisplayed(iIndex, False, True)
			;else
			;		ActorRef.AddSpell(BeinzPluginMarkerSpell_dummy, true)
			;		utility.Wait(0.025)
			else 
				if bForceSpell == true
					if ActorRef.HasSpell(BeinzPluginMarkerSpell_dummy as form)
						ActorRef.RemoveSpell(BeinzPluginMarkerSpell_dummy)
						utility.Wait(0.100000)
						ActorRef.AddSpell(BeinzPluginMarkerSpell_dummy, true)
					elseIf ActorRef.HasSpell(BeinzPluginMarkerSpellTarget_dummy as form)
						ActorRef.RemoveSpell(BeinzPluginMarkerSpellTarget_dummy)
						utility.Wait(0.100000)
						ActorRef.AddSpell(BeinzPluginMarkerSpellTarget_dummy, true)
					endIf
				endIf
			EndIf
			iIndex += 1
		EndWhile

endFunction

Function AddMapMarker(ObjectReference objMarked, Actor akTarget)
;debug.Notification("AddMapMarker, objMarked.GetDisplayName():" + objMarked.GetDisplayName())
	ReferenceAlias refAlias
	int iIndex
	if objMarked
				akTarget.AddSpell(BeinzPluginMarkerSpell_dummy, true)
		;find an empty alias to store this
		iIndex = 1
		While iIndex < GetNumAliases()
			refAlias = GetNthAlias(iIndex) as ReferenceAlias
;debug.Notification("iIndex:" + iIndex + ", refAlias.GetRef():" + refAlias.GetRef())
			if refAlias.GetRef() == none

				refAlias.Clear()
				refAlias.ForceRefTo(objMarked)	;assign to target
				;refAlias.ForceRefIfEmpty(objMarked)
;debug.Notification("AddMapMarker, refAlias.GetRef().GetDisplayName():" + refAlias.GetRef().GetDisplayName())
				SetObjectiveDisplayed(iIndex, True, True)
				debug.Notification("Beinz Face Map marker added " + iIndex as string + " : " + refAlias.GetRef().GetDisplayName())
				return
			EndIf
			iIndex += 1
		EndWhile
		debug.Notification("Maximum number of markers reached. Free up markers.")
	EndIf
EndFunction

Function RemoveMapMarker(ObjectReference objMarked, Actor akTarget)
;debug.Notification("RemoveMapMarker, objMarked.GetDisplayName():" + objMarked.GetDisplayName())
	ReferenceAlias refAlias
	int iIndex
	if objMarked
				akTarget.RemoveSpell(BeinzPluginMarkerSpell_dummy)
		;first see if one of the aliases points to this ObjectReference
		iIndex = 1
		While iIndex < GetNumAliases()
			refAlias = GetNthAlias(iIndex) as ReferenceAlias
;debug.Trace("iIndex:" + iIndex + ", refAlias.GetRef().GetDisplayName():" + refAlias.GetRef().GetDisplayName())
			If refAlias.GetRef() == objMarked
				string strDisplayName = refAlias.GetRef().GetDisplayName()
				refAlias.Clear()
				SetObjectiveDisplayed(iIndex, False, True)
				debug.Notification("Facelight Map marker removed " + iIndex as string + " : " + strDisplayName)
				return
			EndIf
			iIndex += 1
		EndWhile
	EndIf
EndFunction
