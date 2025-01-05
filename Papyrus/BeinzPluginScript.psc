scriptName BeinzPluginScript Hidden

;Initialize mod lists
bool Function InitMods() global native

;Get installed mod count 
int Function GetTotalModCount() global native

;Get count of all actors in game 
int Function GetTotalActors() global native

;Get count of all actors bases in game
int Function GetTotalNPCs() global native

;Geting mod names in page (64 mods per page)
string[] Function GetModNames(int page) global native
;Geting mod indexes in page (64 mods per page)
int[] Function GetModIndexes(int page) global native

;Geting actor count in given page 
int[] Function GetModActorCounts(int page) global native

;Geting actor bases count in given page
int[] Function GetModNPCCounts(int page) global native

;Geting actor count in given mod
int Function GetModActorCount(int mod) global native
;Geting actor count in given mod
int Function GetModNPCCount(int mod) global native

;Geting actor from selected mod and at given index
Actor Function GetModActor(int modIndex, int actorIndex) global native
;Geting actor base from selected mod and at given index
ActorBase Function GetModNPC(int modIndex, int npcIndex) global native

;Geting selected actor id from selected mod at given index
int Function GetModActorId(int modIndex, int actorIndex) global native

;Geting selected actor base id from selected mod at given index
int Function GetModNPCId(int modIndex, int npcIndex) global native

;Generating mod pages stirng
string[] Function GenerateModPages() global native
;Generating actor pages strings of selected mod
string[] Function GenerateActorPageStrings(int mod) global native
;Generating actor bases pages strings of selected mod
string[] Function GenerateNPCPageStrings(int mod) global native

Actor[] Function GetActorsInPage(int modIndex, int index) global native
ActorBase[] Function GetNPCsInPage(int modIndex, int index) global native


;Getting pointer to found character list
int Function FindCharactersByName(string name) global native
;Getting characters from pointer
Actor[] Function FindCharactersByNameActors(int searchIndex) global native
;Getting 
string Function FindCharactersByNameModName(int searchIndex, int characterIndex) global native
;Getting
int[] Function FindCharactersByNameModIndices(int searchIndex) global native
;Getting
string[] Function FindCharactersByNameModNames(int searchIndex) global native

string[] Function GenerateFoundPages(int searchIndex) global native

string Function GetModName(int index) global native

Function ClearSearchCache() global native

string Function IntToHexString(int num) global native
string Function ModIndexToHexString(int index) global native

int Function GetModFromActor(Actor a) global native

Function WriteInfoLog(string msg) global native
Function WriteDebugLog(string msg) global native
Function WriteErrorLog(string msg) global native

Function WriteInfo(string msg) global
    WriteInfoLog(msg)
    Debug.Trace("AreYouThere: " + msg)
EndFunction

Function WriteDebug(string msg) global
    WriteDebugLog(msg)
    Debug.Trace("AreYouThere: " + msg)
EndFunction

Function WriteError(string msg) global
    WriteErrorLog(msg)
    Debug.Trace("AreYouThere: " + msg, 2)
EndFunction
    