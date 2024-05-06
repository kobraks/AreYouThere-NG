Scriptname BeinzPluginTarget extends activemagiceffect  

;-- Properties --------------------------------------
Spell property BeinzPluginMarkerSpellTarget_dummy auto
BeinzPluginMapMarkersQuestScript Property qstMapMarker Auto

;-- Variables ---------------------------------------

;-- Functions ---------------------------------------

function OnEffectStart(Actor akTarget, Actor akCaster)
	if akTarget.HasSpell(BeinzPluginMarkerSpellTarget_dummy as form)
		qstMapMarker.RemoveMapMarker(akTarget, akTarget)
	else
		qstMapMarker.AddMapMarker(akTarget, akTarget)
	endIf
endFunction
