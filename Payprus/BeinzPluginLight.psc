Scriptname BeinzPluginLight extends activemagiceffect  

;-- Properties --------------------------------------
Spell property sFacelight auto

;-- Variables ---------------------------------------

;-- Functions ---------------------------------------

function OnEffectStart(Actor akTarget, Actor akCaster)

	if akTarget.HasSpell(sFacelight as form)
		akTarget.RemoveSpell(sFacelight)
	else
		akTarget.AddSpell(sFacelight, false)
	endIf
endFunction

; Skipped compiler generated GotoState

; Skipped compiler generated GetState
