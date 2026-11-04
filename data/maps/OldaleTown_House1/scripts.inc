OldaleTown_House1_MapScripts::
	.byte 0

OldaleTown_House1_EventScript_Woman::
	msgbox OldaleTown_House1_Text_LeftPokemonGoesOutFirst, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_TradeGirl::
        lock
        faceplayer
        goto_if_set FLAG_ABSOL_NPC_TRADE_COMPLETED, OldaleTown_PokemonCenter_1F_EventScript_TradeCompleted
        setvar VAR_0x8008, INGAME_TRADE_ABSOL
        copyvar VAR_0x8004, VAR_0x8008
        specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
        copyvar VAR_0x8009, VAR_RESULT
        msgbox OldaleTown_PokemonCenter_1F_Text_YouWillTradeWontYou, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, OldaleTown_PokemonCenter_1F_EventScript_DeclineTrade
        special ChoosePartyMon
	waitstate
        copyvar VAR_0x800A, VAR_0x8004
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, OldaleTown_PokemonCenter_1F_EventScript_DeclineTrade
        copyvar VAR_0x8005, VAR_0x800A
        specialvar VAR_RESULT, GetTradeSpecies
        copyvar VAR_0x800B, VAR_RESULT
        goto_if_ne VAR_RESULT, VAR_0x8009, OldaleTown_PokemonCenter_1F_EventScript_NotRequestedMon
        copyvar VAR_0x8004, VAR_0x8008
        copyvar VAR_0x8005, VAR_0x800A
        special CreateInGameTradePokemon
        special DoInGameTradeScene
	waitstate
        bufferspeciesname STR_VAR_1, VAR_0x8009
        msgbox OldaleTown_PokemonCenter_1F_Text_MonYouTakeCare, MSGBOX_DEFAULT
        setflag FLAG_ABSOL_NPC_TRADE_COMPLETED
        release
        end

OldaleTown_PokemonCenter_1F_EventScript_DeclineTrade::
        msgbox OldaleTown_PokemonCenter_1F_Text_YouWontTradeMe, MSGBOX_DEFAULT
        release
        end

OldaleTown_PokemonCenter_1F_EventScript_NotRequestedMon::
        bufferspeciesname STR_VAR_1, VAR_0x8009
        msgbox OldaleTown_PokemonCenter_1F_Text_ThisIsntAMon, MSGBOX_DEFAULT
        release
        end

OldaleTown_PokemonCenter_1F_EventScript_TradeCompleted::
        msgbox OldaleTown_PokemonCenter_1F_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
        release
        end



OldaleTown_PokemonCenter_1F_Text_YouWillTradeWontYou:
        .string "Hey! Ich will unbedingt ein TRASLA!\n"
        .string "Möchtest du es gegen mein ABSOL\p"
        .string "tauschen?$"

OldaleTown_PokemonCenter_1F_Text_MonYouTakeCare:
        .string "Hihi! Super! Vielen Dank!\n"
        .string "Kümmere dich gut um ABSOL!$"

OldaleTown_PokemonCenter_1F_Text_YouWontTradeMe:
        .string "Du willst nicht tauschen?\n"
        .string "Wie schade!$"

OldaleTown_PokemonCenter_1F_Text_ThisIsntAMon:
        .string "Das ist kein TRASLA!\n"
        .string "Komm wieder, wenn du ein TRASLA\p"
        .string "hast!$"

OldaleTown_PokemonCenter_1F_Text_GoingToMakeVolbeatStrong:
        .string "Deinem TRASLA geht es gut!\n"
        .string "Ich hoffe du kümmerst dich auch\p"
        .string "gut um ABSOL!$"

OldaleTown_House1_Text_LeftPokemonGoesOutFirst:
	.ifdef ENGLISH
	.string "When a POKéMON battle starts, the one\n"
	.string "at the left of the list goes out first.\p"
	.string "So, when you get more POKéMON in your\n"
	.string "party, try switching around the order\l"
	.string "of your POKéMON.\p"
	.string "It could give you an advantage.$"
	.else
	.ifdef GERMAN
	.string "Das POKéMON auf der linken Seite der\n"
	.string "Liste tritt im Kampf als Erstes an.\p"
	.string "Hast du mehrere POKéMON in deinem Team,\n"
	.string "stelle sie so der Reihe nach auf, wie es\l"
	.string "für den Kampf am günstigsten ist.\p"
	.string "Das kann ein Vorteil für dich sein.$"
	.endif
	.endif

