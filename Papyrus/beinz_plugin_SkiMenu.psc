scriptname beinz_plugin_SkiMenu extends SKI_ConfigBase

; SCRIPT VERSION ----------------------------------------------------------------------------------

int function GetVersion()
	return 10;
endFunction


; PRIVATE VARIABLES -------------------------------------------------------------------------------

GlobalVariable Property BeinzPluginMarkerLightOn Auto
BeinzPluginMapMarkersQuestScript Property MyQuest Auto 

int MCMPage_Init = 0
int MCMPage_Mods = 1
int MCMPage_Acto = 2
int MCMPage_Base = 3
int MCMPage_Ligh = 4
int MCMPage_Find = 5

bool hideVal
bool m_Inited = false

int m_ActorsPageMax = 110
int m_ActorsPerPage = 100
int m_ModsPerPage = 64
int m_MaxMarker = 64

int m_ModCount = 0
int m_ActorCount = 0
int m_NpcCount = 0

int m_EntriesFound = 0

int m_ModsPage
int m_SelectedMod

int m_ActorsPage
int m_ActorsIndex

int m_NPCPage

int m_MarkerPage
int m_ChoiceStates

int m_IdTextModPages
int m_IdTextActorsPages
int m_IdTextNPCsPages
int m_IdTextMarkerPages
int m_IdTextMarkerPageSelect
int m_IdTextFound
int m_idTextTest
int m_IdTextFoundPages

int[] m_IdTextMods
int[] m_IdTextNPCs
int[] m_IdTextActors
int[] m_IdTextMarker
int[] m_IdTextFindActors

int[] m_ModActorCounts
int[] m_ModNPCCounts
int[] m_ModIndices 

string m_NullOption = "--------"
string m_LastSearched

string[] m_Actions
string[] m_Choices

string[] m_ActorPages
string[] m_NPCPages
string[] m_MarkerPages
string[] m_ModPages

string[] m_ModNames

Actor[] m_ActorsFound

string[] m_FoundPages
string[] m_FoundPagesDefault

int m_FoundPageCount = 0
int m_FoundPage = 0
int m_SearchIndex = 0

function DoAction(Actor target, int selectedAction)
	;self.ShowMessage("Selected Actor : [0x" + BeinzPluginScript.IntToHexString(target.GetFormID()) + "]" + target.GetActorBase().GetName(), false)

	Debug.Trace("AreYouThere: Selected actor: [0x" + BeinzPluginScript.IntToHexString(target.GetFormID())+"]" + target.GetActorBase().GetName())

	if (!target)
		Debug.Trace("AreYouThere: Selected null actor", 2)
		return
	endIf

	if (selectedAction == 0)
		Debug.Trace("AreYouThere: Nulll action selected")
	elseIf (selectedAction == 1)
		Debug.Trace("AreYouThere: Moving selected actor to player")
		target.MoveTo(Game.GetPlayer())
	elseIf (selectedAction == 2)
		Debug.Trace("AreYouThere: Moving player to selected actor")
		Game.GetPlayer().MoveTo(target)
	elseIf (selectedAction == 3)
		Debug.Trace("AreYouThere: Adding map marker to selected actor")
		MyQuest.AddMapMarker(target, target)
	elseIf (selectedAction == 4)
		Debug.Trace("AreYouThere: Removing map marker to selected actor")
		MyQuest.RemoveMapMarker(target, target)
	elseIf (selectedAction == 5)
		ActorBase refActorBase = target.GetBaseObject() as ActorBase
		if (refActorBase.isEssential())
			Debug.Trace("AreYouThere: Marking selected actor as not essential")
			refActorBase.SetEssential(false)
		else
			Debug.Trace("AreYouThere: Marking selected actor as essential")
			refActorBase.SetEssential(true)
		endIf
	elseIf (selectedAction == 6)
		if (target.IsEnabled())
			Debug.Trace("AreYouThere: Disabling seleccted actor")
			target.Disable()
		else
			Debug.Trace("AreYouThere: Enabling seleccted actor")
			target.Enable()
		endIf
	endIf
endFunction

Function SelectMod(int modindex)
	m_SelectedMod = modIndex

	m_ActorPages = BeinzPluginScript.GenerateActorPageStrings(m_SelectedMod)
	m_NPCPages = BeinzPluginScript.GenerateNPCPageStrings(m_SelectedMod)

	m_ActorsPage = 0
	m_NpcPage = 0

	Debug.Trace("AreYouThere: Selected mod: " + BeinzPluginScript.GetModName(m_SelectedMod) + " Actor Pages: " + m_ActorPages.Length + " Npc Pages: " + m_NPCPages.Length)
EndFunction

Function SelectModPage(int modPage)
	m_ModActorCounts = BeinzPluginScript.GetModActorCounts(modPage)
	m_ModNPCCounts = BeinzPluginScript.GetModNPCCounts(modPage)
	m_ModNames = BeinzPluginScript.GetModNames(modPage)
	m_ModIndices = BeinzPluginScript.GetModIndexes(modPage)

	Debug.Trace("Selected mod page: " + modPage + " " + m_ModPages[modPage])
EndFunction

Function ClearSearchCache()
	BeinzPluginScript.ClearSearchCache()
	m_LastSearched = ""
	m_EntriesFound = 0

	m_SearchIndex = 0

	m_FoundPages = m_FoundPagesDefault
	m_FoundPageCount = 0
	m_FoundPage = 0

	Debug.Trace("AreYouThere: Clearing Cache search results")
EnDFunction

event OnConfigInit()
	ModName = "Are You There ?"

	Pages = new string[6]
	Pages[MCMPage_Init] = "1 Init"
	Pages[MCMPage_Mods] = "2 Select Mods"
	Pages[MCMPage_Acto] = "3-a Actors"
	Pages[MCMPage_Base] = "3-b NPC bases"
	Pages[MCMPage_Ligh] = "Marked Actors"
	Pages[MCMPage_Find] = "Find Actors"
	
	m_IdTextMods = new int [64]
	m_IdTextActors = new int [100]
	m_IdTextNPCs = new int [100]
	m_IdTextMarker = new int [64]
	m_IdTextFindActors = new int [100]

	m_Actions = new string[7]
	m_Actions[0] = m_NullOption
	m_Actions[1] = "Call target to player"
	m_Actions[2] = "Player move to target"
	m_Actions[3] = "Add MapMarker"
	m_Actions[4] = "Remove MapMarker"
	m_Actions[5] = "Toggle Essential"
	m_Actions[6] = "Toggle Enabled"

	m_MarkerPages = new string[4]
	m_MarkerPages[0] = "p1 : No.01 ~ No.16"
	m_MarkerPages[1] = "p2 : No.17 ~ No.32"
	m_MarkerPages[2] = "p3 : No.33 ~ No.48"
	m_MarkerPages[3] = "p4 : No.49 ~ No.64"

	m_Choices = new string[6]
	m_Choices[0] = m_NullOption
	m_Choices[1] = "Call to Player"
	m_Choices[2] = "Player move to"
	m_Choices[3] = "Remove MapMarker"
	m_Choices[4] = "Toggle Essential"
	m_Choices[5] = "Toggle Enabled"

	m_ModsPage = 0
	m_SelectedMod = -1

	m_NPCPage = 0

	m_ActorsPage = 0
	m_Actorsindex = -1

	m_SearchIndex = 0
	m_EntriesFound = 0
	m_FoundPage = 0
	m_FoundPageCount = 1
	m_LastSearched = ""

	m_FoundPages = new string[1]
	m_FoundPages[0] = "Empty"

	m_FoundPagesDefault = m_FoundPages
EndEvent

event OnVersionUpdate(int version)
	OnConfigInit()
endEvent

event OnGameReload()
	m_Inited = false
endEvent


event OnPageReset(string page)
	Debug.Trace("AreYouThere: Page: " + page)
	if (Pages[MCMPage_Mods] == page)
		SetCursorFillMode(TOP_TO_BOTTOM)

		if (m_Inited)
			AddTextOption("Total Mods: " + m_ModCount + "\tbaseNPCs/Actors", "", OPTION_FLAG_DISABLED)
			AddHeaderOption("")

			int pageAdd = m_ModsPerPage * m_ModsPage
			int pageLast = pageAdd + m_ModsPerPage - 1
			int pageHalf = m_ModsPerPage / 2

			if (pageAdd >= m_ModCount)
				AddHeaderOption("No more pages")
				SetCursorPosition(1)
				m_IdTextModPages = AddMenuOption("Mods Page (64Mods/page)", m_ModPages[m_ModsPage], 0)
				AddHeaderOption("")
			else
				SelectModPage(m_ModsPage)

				int loop = 0
				int modIndex = pageAdd
				while ((loop < m_ModsPerPage) && (modIndex < m_ModCount))
					int actors = m_ModActorCounts[loop]
					int npcs = m_ModNPCCounts[loop]
					int option = 0

					If (actors == 0 && npcs == 0)
						option = OPTION_FLAG_DISABLED
					EndIf
					If (m_ModIndices[loop] == 0xFF)
						option = OPTION_FLAG_DISABLED
					EndIf

					m_IdTextMods[loop] = self.AddTextOption(m_ModNames[loop], npcs + " / " + actors, option)

					loop += 1
					modIndex += 1

					if (loop == pageHalf)
						SetCursorPosition(1)
						m_IdTextModPages = AddMenuOption("Mods Page (64Mods/page)", m_ModPages[m_ModsPage], 0)
						AddHeaderOption("")
					EndIf
				EndWhile
				If (loop < pageHalf)
					SetCursorPosition(1)
					m_IdTextModPages = AddMenuOption("Mods Page (64Mods/page)", m_ModPages[m_ModsPage], 0)
					AddHeaderOption("")
				Endif
			EndIf
		else
			self.ShowMessage("Do Init First", false)
		endif
	ElseIf (Pages[MCMPage_Acto] == page)
		SetCursorFillMode(TOP_TO_BOTTOM)

		If (m_Inited && m_SelectedMod >= 0)
			int modIndex = m_SelectedMod % m_ModsPerPage
			AddTextOption(m_ModNames[modIndex], m_ModActorCounts[modIndex], OPTION_FLAG_DISABLED)
			AddHeaderOption("")

			int pageAdd = m_ActorsPerPage * m_ActorsPage
			int pageLast = pageAdd + m_ActorsPerPage - 1
			int pageHalf = m_ActorsPerPage / 2

			int loop = 0
			int actorIndex = pageAdd
			int modActorCount = BeinzPluginScript.GetModActorCount(m_SelectedMod)
			Actor[] actorsInPage = BeinzPluginScript.GetActorsInPage(m_SelectedMod, actorIndex)

			While ((loop < m_ActorsPerPage) && (actorIndex < modActorCount))
				Actor current = actorsInPage[loop]

				If (current && current.GetFormID() != 0)
					m_IdTextActors[loop] = AddMenuOption("[" + BeinzPluginScript.IntToHexString(current.GetFormID()) + "]" + current.GetActorBase().GetName(), m_Actions[0], 0)
				else
					m_IdTextActors[loop] = AddMenuOption("[" + BeinzPluginScript.IntToHexString(current.GetFormID()) + "]", "", OPTION_FLAG_DISABLED)
				EndIf

				loop += 1
				actorIndex += 1

				If (loop == pageHalf)
					SetCursorPosition(1)
					m_IdTextActorsPages = AddMenuOption("Page (100Actors/page)", m_ActorPages[m_ActorsPage], 0)
					AddHeaderOption("")
				EndIf
			EndWhile
			If (loop < pageHalf)
				SetCursorPosition(1)
				m_IdTextActorsPages = AddMenuOption("Page (100Actors/page)", m_ActorPages[m_ActorsPage], 0)
				AddHeaderOption("")
			EndIf
		Else
			self.ShowMessage("Do 1 Init -> 2 Select Mods", false)
		EndIf
	ElseIf (Pages[MCMPage_Base] == page)
		SetCursorFillMode(TOP_TO_BOTTOM)

		If (m_Inited && m_SelectedMod >= 0)
			int modIndex = m_SelectedMod % m_ModsPerPage
			
			AddTextOption(m_ModNames[modIndex], m_ModNPCCounts[modIndex], OPTION_FLAG_DISABLED)
			AddHeaderOption("Just click to Clone it", 0)

			int pageAdd = m_ActorsPerPage * m_NPCPage
			int pageLast = pageAdd + m_ActorsPerPage - 1
			int pageHalf = m_ActorsPerPage / 2

			int loop = 0
			int actorIndex = pageAdd
			int modActorCount = BeinzPluginScript.GetModNPCCount(m_SelectedMod)
			ActorBase[] actorsInPage = BeinzPluginScript.GetNPCsInPage(m_SelectedMod, actorIndex)

			While((loop < m_ActorsPerPage) && (ActorIndex < modActorCount))
				ActorBase npc = actorsInPage[loop]
				if (npc)
					m_IdTextNPCs[loop] = AddTextOption("[" + BeinzPluginScript.IntToHexString(npc.GetFormID()) + "]" , npc.GetName(), 0)
				else
					m_IdTextNPCs[loop] = AddTextOption("[" + BeinzPluginScript.IntToHexString(npc.GetFormID()) + "]", "", OPTION_FLAG_DISABLED)
				EndIf

				loop += 1
				actorIndex += 1

				if (loop == pageHalf)
					SetCursorPosition(1)
					m_IdTextNPCsPages = AddMenuOption("Page (100Actors/page)", m_NPCPages[m_NPCPage], 0)
					AddHeaderOption("")
				EndIf
			EndWhile
			if (loop < pageHalf)
				SetCursorPosition(1)
				m_IdTextNPCsPages = AddMenuOption("Page (100Actors/page)", m_NPCPages[m_NPCPage], 0)
				AddHeaderOption("")
			EndIf
		Else
			self.ShowMessage("Do 1 Init -> 2 Select Mods", false)
		EndIf
	ElseIf (Pages[MCMPage_Ligh] == page)
		SetCursorFillMode(TOP_TO_BOTTOM)

		m_IdTextMarkerPages = AddHeaderOption("Page" + (m_MarkerPage + 1) as string, 0)

		int index = m_MarkerPage * 16 + 1
		int end = index + 16

		while (index < end)
			ReferenceAlias refAlias = GetNthAlias(index) as ReferenceAlias
			Actor refActor = refAlias.GetActorRef() as Actor

			if (refActor != none)
				string status
				if (refAlias.GetactorRef().isDead())
					status = "   [Dead]"
				else
					ActorBase refActorBase = refActor.GetBaseObject() as ActorBase
					if (refActorBase.IsInvulnerable())
						status = "	[Invulnerable]"
					else
						if (refActorBase.isEssential())
							status = "	[Essential]"
						elseif (refActorBase.IsUnique())
							status = "	[Unique]"
						elseif (refActorBase.IsProtected())
							status = "	[Protected]"
						elseif (refActor.isChild())
							status = "	[Child]"
						elseif (refActor.IsEnabled())
							status = "	[Enabled]"
						elseIf (refActor.IsDisabled())
							status = "	[Disabled]"
						else
							status = ""
						EndIf
					EndIf
				EndIf

				m_IdTextMarker[index] = AddMenuOption(index + ". " + refAlias.GetRef().GetDisplayName() + status, m_Choices[m_ChoiceStates], 0)
			else
				m_IdTextMarker[index] = AddTextOption(index + ". ", "", OPTION_FLAG_DISABLED)
			EndIF

			index += 1

			if end - index == 8
				SetCursorPosition(1)
				m_IdTextMarkerPageSelect = AddMenuOption("16Markers/page", m_MarkerPages[m_MarkerPage], 0)
			EndIf

		EndWhile
	ElseIf (Pages[MCMPage_Find] == page)
		SetCursorFillMode(TOP_TO_BOTTOM)

		if (m_Inited)
			AddInputOptionST("SearchST", "Actor Name: ", m_LastSearched)
			m_IdTextFound = AddTextOption("Found: " + m_EntriesFound, "", 0)
			AddHeaderOption("")

			int pageAdd = m_ActorsPerPage * m_FoundPage
			int pageHalf = m_ActorsPerPage / 2
			int loop = 0

			if (m_EntriesFound != 0)
				int[] modIndices = BeinzPluginScript.FindCharactersByNameModIndices(m_SearchIndex)
				string[] modNames = BeinzPluginScript.FindCharactersByNameModNames(m_SearchIndex)

				int currentMod = 0
				bool shown = false;
				int actorIndex = pageAdd

				while ((loop < m_ActorsPerPage) && (actorIndex < m_EntriesFound))
					Actor current = m_ActorsFound[actorIndex]
					if ((shown == false) || (currentMod != modIndices[actorIndex]))
						shown = true
						currentMod = modIndices[actorIndex]
						AddTextOption(modNames[actorIndex], "", OPTION_FLAG_DISABLED)
					endIf

					m_IdTextFindActors[loop] = AddMenuOption("[" + BeinzPluginScript.IntToHexString(current.GetFormID()) + "]" + current.GetActorBase().GetName(), m_Actions[0], 0)
					loop += 1
					actorIndex += 1

					if (loop == pageHalf)
						SetCursorPosition(1)
						m_IdTextFoundPages = AddMenuOption("Page (100Actors/Page)", m_FoundPages[m_FoundPage], 0)
						AddTextOptionST("ClearCacheST", "", "Clear Cache", 0)
						AddHeaderOption("")
						shown = false
					EndIf
				EndWhile
			EndIf

			if ( loop < pageHalf)
				SetCursorPosition(1)
				m_IdTextFoundPages = AddMenuOption("Page (100Actors/Page)", m_FoundPages[m_FoundPage], 0)
				AddTextOptionST("ClearCacheST", "", "Clear Cache", 0)
				AddHeaderOption("")
			EndIf
		Else
			self.ShowMessage("Do Init First", false)
		EndIf
	else
		SetCursorFillMode(TOP_TO_BOTTOM)
		m_ActorCount = BeinzPluginScript.GetTotalActors()
		if (m_Inited)
			AddTextOptionST("InitSt", "Inited", "Re-init?")
		else
			AddTextOptionST("InitST", "Init - Do first please", "Do Init")
		endif

		SetCursorPosition(1)

		if (BeinzPluginMarkerLightOn.GetValueInt() == 0)
			hideVal = true
		else
			hideVal = false
		endif
		AddToggleOptionST("HideST", "Light Off at Marked Actor", hideVal, 0)
	endif

endevent

Event OnOptionSelect(int option)
	if (option == m_idTextTest)
		Actor a = Game.GetFormEx(0x9cbc9) as Actor
		ActorBase ab = a.GetActorBase()
		self.ShowMessage("Actor 0x9cbc9 : " + a.GetFormID() + " - ActorBase : " + ab.GetFormID() + " " + ab.GetName(), false)
	elseif (CurrentPage == Pages[MCMPage_Mods])
		int loop = 0
		while (loop < m_ModsPerPage)
			if (option == m_IdTextMods[loop])
				int pageAdd = m_ModsPerPage * m_ModsPage

				SelectMod(pageAdd + loop)

				self.ShowMessage("Selected Mod\n" + m_ModNames[loop], false)
				loop = m_ModsPerPage
			EndIf
			loop += 1
		EndWhile
	ElseIf (CurrentPage == Pages[MCMPage_Base])
		int loop = 0

		while (loop < m_ActorsPerPage)
			if (option == m_IdTextNPCs[loop])
				int pageAdd = m_ActorsPerPage * m_NPCPage
				int npcIndex = pageAdd + loop

				ActorBase actorb = BeinzPluginScript.GetModNPC(m_SelectedMod, npcIndex)
				Debug.Trace("AreYouThere: Cloning [" + BeinzPluginScript.IntToHexString(actorb.GetFormID()) +"]" + actorb.GetName())
				Game.GetPlayer().PlaceAtMe(actorb)

				loop = m_ActorsPerPage
			endIf

			loop += 1
		endwhile
	endif
EndEvent

event OnOptionMenuOpen(int option)
	if (m_IdTextModPages == option)
		SetMenuDialogOptions(m_ModPages)
		SetMenuDialogDefaultIndex(0)
		SetMenuDialogStartIndex(m_ModsPage)
	elseIf (m_IdTextActorsPages == option)
		SetMenuDialogOptions(m_ActorPages)
		SetMenuDialogDefaultIndex(0)
		SetMenuDialogStartIndex(m_ActorsPage)
	elseIf (m_IdTextNPCsPages == option)
		SetMenuDialogOptions(m_NPCPages)
		SetMenuDialogDefaultIndex(0)
		SetMenuDialogStartIndex(m_NPCPage)
	elseIf (m_IdTextFoundPages == option)
		SetMenuDialogOptions(m_FoundPages)
		SetMenuDialogDefaultIndex(0)
		SetMenuDialogStartIndex(m_FoundPage)

	elseIf (Pages[MCMPage_Acto] == CurrentPage)
		SetMenuDialogOptions(m_Actions)
		SetMenuDialogDefaultIndex(0)
		SetMenuDialogStartIndex(0)
	elseIf (Pages[MCMPage_Ligh] == CurrentPage) 
		if (m_IdTextMarkerPageSelect == option)
			SetMenuDialogOptions(m_MarkerPages)
			SetMenuDialogDefaultIndex(0)
			SetMenuDialogStartIndex(m_MarkerPage)

		else
			int index = 0
			while (index < m_MaxMarker)
				if (option == m_IdTextMarker[index])
					SetMenuDialogOptions(m_Choices)
					SetMenuDialogDefaultIndex(0)
					SetMenuDialogStartIndex(m_ChoiceStates)
					return
				endIf
					index += 1
			endWhile
		endIf
	elseIf (Pages[MCMPage_Find] == CurrentPage)
		SetMenuDialogOptions(m_Actions)
		SetMenuDialogDefaultIndex(0)
		SetMenuDialogStartIndex(0)
	endIf
endEvent

event OnOptionMenuAccept(int option, int index)
	if (m_IdTextModPages == option)
		if (m_ModsPage != index)
			m_ModsPage = index
			ForcePageReset()
		endIf
	elseIf (m_IdTextActorsPages == option)
		if (m_ActorsPage != index)
			m_ActorsPage = index
			ForcePageReset()
		endIf
	elseIf (m_IdTextNPCsPages == option)
		if (m_NpcPage != index)
			m_NPCPage = index
			ForcePageReset()
		endIf
	elseIf (m_IdTextFoundPages == option)
		if (m_FoundPage != index)
			m_FoundPage = index
			ForcePageReset()
		endif

	elseIf (Pages[MCMPage_Acto] == CurrentPage && index != 0)
		int loop = 0

		while (loop < m_ActorsPerPage)
			if (m_IdTextActors[loop] == option)
				int pageAdd = m_ActorsPerPage * m_ActorsPage
				m_ActorsIndex = pageAdd + loop

				DoAction(BeinzPluginScript.GetModActor(m_SelectedMod, m_ActorsIndex), index)

				loop = m_ActorsPerPage
			endIf

			loop += 1
		endWhile

	elseIf (Pages[MCMPage_Ligh] == CurrentPage)
		if (option == m_IdTextMarkerPageSelect)
			if (m_MarkerPage != index)
				m_MarkerPage = index
				ForcePageReset()
			endIf
		else
			int loop = 0
			while (loop < m_MaxMarker)
				if (option == m_IdTextMarker[loop])
					ReferenceAlias refAlias = GetNthAlias(loop + (m_MarkerPage * 16)) as ReferenceAlias

					m_ChoiceStates = index
					if (m_ChoiceStates == 1)
						refAlias.GetRef().MoveTo(Game.GetPlayer())
					elseif (m_ChoiceStates == 2)
						Game.GetPlayer().MoveTo(refAlias.GetRef())
					elseIf (m_ChoiceStates == 3)
						MyQuest.RemoveMapMarker(refAlias.GetRef(), refAlias.GetActorRef())
					elseIf (m_ChoiceStates == 4)
						Actor refActor = refAlias.GetActorRef() as Actor
						ActorBase refActorBase = refActor.GetBaseObject() as ActorBase

						if (refActorBase.isEssential())
							refActorBase.SetEssential(false)
						else
							refActorBase.SetEssential(true)
						endIf
					elseIf (m_ChoiceStates == 5)
						Actor refActor = refAlias.GetActorRef() as Actor

						if (refActor.IsEnabled())
							refActor.Disable()
						else
							refActor.Enable()
						endIf
					endIf

					m_ChoiceStates = 0
					SetMenuOptionValue(m_IdTextMarker[loop], m_Choices[m_ChoiceStates], 0)
					ForcePageReset()
					return
				endIf
				loop += 1
			endWhile 
		endIf

	elseIf ((Pages[MCMPage_Find] == CurrentPage) && (index != 0))
		int loop = 0
		while ((loop < m_ActorsPerPage) && (loop < m_EntriesFound))
			int pageAdd = m_ActorsPerPage * m_FoundPage
			int actorIndex = pageAdd + loop

			if (m_IdTextFindActors[loop] == option)
				DoAction(m_ActorsFound[actorIndex], index)

				SelectMod(BeinzPluginScript.GetModFromActor(m_ActorsFound[actorIndex]))

				m_ModsPage = m_SelectedMod / m_ModsPerPage
				SelectModPage(m_ModsPage)

				loop = m_ActorsPerPage
			endIf
			loop += 1
		endWhile
	endIf
endEvent



State InitST
	Event OnSelectST()
		SetOptionFlagsST(OPTION_FLAG_DISABLED)
		SetTextOptionValueST("Processing...")

		ClearSearchCache()

		m_Inited = BeinzPluginScript.InitMods()
		if (m_Inited)
			m_ActorCount = BeinzPluginScript.GetTotalActors()
			m_NPCCount = BeinzPluginScript.GetTotalNPCs()
			m_ModCount = BeinzPluginScript.GetTotalModCount()

			m_SelectedMod = -1
			if (m_ActorCount >= 65536)
				self.ShowMessage("Too many Actors (plz report to modder) : " + m_actorCount, false)
				Debug.trace("AreYouThere: Too many Actors (plz report to modder): " + m_actorCount, 2)
			else
				Debug.trace("AreYouThere: Total Actors: " + m_actorCount + "\nTotal Base NPCs: " + m_NPCCount + "\nTotal Mods: " + m_ModCount)
				self.ShowMessage("Total Actors : " + m_actorCount + "\nTotal Base NPCs : " + m_NPCCount + "\nTotal Mods : " + m_ModCount, false)
			endif

			m_ModPages = BeinzPluginScript.GenerateModPages()
			Debug.trace("Mod pages count: " + m_ModPages.Length)
		else
			self.ShowMessage("Something went wrong unable to initialize mod list (plz report to mod author)")
			Debug.trace("AreYouThere: Unable to InitMods returned false")
		endif

		ForcePageReset()
	EndEvent
EndState

State SearchST
	event OnInputAcceptST(string value)
		m_LastSearched = value
		Debug.Trace("AreYouThere: Looking For " + value)

		m_SearchIndex = BeinzPluginScript.FindCharactersByName(m_LastSearched)
		m_ActorsFound = BeinzPluginScript.FindCharactersByNameActors(m_SearchIndex)
		m_EntriesFound = m_ActorsFound.Length

		m_FoundPage = 0

		m_FoundPages = BeinzPluginScript.GenerateFoundPages(m_SearchIndex)
		m_FoundPageCount = m_FoundPages.Length

		self.SetInputOptionValueST(m_LastSearched)
		self.SetTextOptionValue(m_IdTextFound, m_EntriesFound)

		Debug.Trace("AreYouThere: Found: " + m_EntriesFound + " pages: " + m_FoundPageCount)

		ForcePageReset()
	EndEvent
EndState

State ClearCacheST
	Event OnSelectST()
		ClearSearchCache()

		self.SetTextOptionValue(m_IdTextFound, 0)
		self.SetTextOptionValueST("Cache cleaned")
		
		ForcePageReset()
	EndEvent
EndState


State HideST
	Event OnSelectST()
		hideVal = !hideVal
		self.SetToggleOptionValueST(hideVal, false, "")
		if (hideVal)
			BeinzPluginMarkerLightOn.SetValueInt(0)
		else
			BeinzPluginMarkerLightOn.SetValueInt(1)
		endif
		MyQuest.ReloadLight(true)
	EndEvent
EndState