Scriptname BeinzPluginLightCandleLightToggle extends activemagiceffect  

;-- Properties --------------------------------------
Spell property BeinzPluginMarkerSpell_dummy auto

;-- Variables ---------------------------------------
bool bHasSpell = false

;-- Functions ---------------------------------------

function OnEffectFinish(Actor akTarget, Actor akCaster)

	if bHasSpell
		akTarget.AddSpell(BeinzPluginMarkerSpell_dummy, false)
		bHasSpell = false
	endIf
endFunction

function OnEffectStart(Actor akTarget, Actor akCaster)

	if akTarget.HasSpell(BeinzPluginMarkerSpell_dummy as form)
		akTarget.RemoveSpell(BeinzPluginMarkerSpell_dummy)
		bHasSpell = true
	endIf
endFunction

; Skipped compiler generated GotoState

; Skipped compiler generated GetState
