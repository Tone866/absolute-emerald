.set LOCALID_NURSE, 1
.set LOCALID_GUARD_1, 3
.set LOCALID_GUARD_2, 4
.set LOCALID_GUARD_3, 5

EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_GUARD_1, 9, 2
	setobjectxyperm LOCALID_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_EventScript_Rematch::
        lock
        faceplayer
        goto_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_EventScript_SelectLvl
        msgbox EverGrandeCity_Text_NoBadges, MSGBOX_DEFAULT
        release
        end

EverGrandeCity_EventScript_SelectLvl::
        msgbox EverGrandeCity_Text_LvlText, MSGBOX_DEFAULT
        call_if_eq VAR_LIGA_REMATCH_MAX, 0, EverGrandeCity_EventScript_Lvl1
        call_if_eq VAR_LIGA_REMATCH_MAX, 1, EverGrandeCity_EventScript_Lvl2
        call_if_eq VAR_LIGA_REMATCH_MAX, 2, EverGrandeCity_EventScript_Lvl3
        call_if_eq VAR_LIGA_REMATCH_MAX, 3, EverGrandeCity_EventScript_Lvl4

EverGrandeCity_EventScript_Lvl1:
        multichoice 0, 0, MULTI_LIGA_LVL1, TRUE
        goto_if_eq VAR_RESULT, 0, EverGrandeCity_EventScript_SetLvl0
        goto_if_eq VAR_RESULT, 1, EverGrandeCity_EventScript_SetLvl1
        goto_if_eq VAR_RESULT, 2, EverGrandeCity_EventScript_Back
        end

EverGrandeCity_EventScript_Lvl2:
        multichoice 0, 0, MULTI_LIGA_LVL2, TRUE
        goto_if_eq VAR_RESULT, 0, EverGrandeCity_EventScript_SetLvl0
        goto_if_eq VAR_RESULT, 1, EverGrandeCity_EventScript_SetLvl1
        goto_if_eq VAR_RESULT, 2, EverGrandeCity_EventScript_SetLvl2
        goto_if_eq VAR_RESULT, 3, EverGrandeCity_EventScript_Back
        end

EverGrandeCity_EventScript_Lvl3:
        multichoice 0, 0, MULTI_LIGA_LVL3, TRUE
        goto_if_eq VAR_RESULT, 0, EverGrandeCity_EventScript_SetLvl0
        goto_if_eq VAR_RESULT, 1, EverGrandeCity_EventScript_SetLvl1
        goto_if_eq VAR_RESULT, 2, EverGrandeCity_EventScript_SetLvl2
        goto_if_eq VAR_RESULT, 3, EverGrandeCity_EventScript_SetLvl3
        goto_if_eq VAR_RESULT, 4, EverGrandeCity_EventScript_Back
        end

EverGrandeCity_EventScript_Lvl4:
        multichoice 0, 0, MULTI_LIGA_LVL4, TRUE
        goto_if_eq VAR_RESULT, 0, EverGrandeCity_EventScript_SetLvl0
        goto_if_eq VAR_RESULT, 1, EverGrandeCity_EventScript_SetLvl1
        goto_if_eq VAR_RESULT, 2, EverGrandeCity_EventScript_SetLvl2
        goto_if_eq VAR_RESULT, 3, EverGrandeCity_EventScript_SetLvl3
        goto_if_eq VAR_RESULT, 4, EverGrandeCity_EventScript_SetLvl4
        goto_if_eq VAR_RESULT, 5, EverGrandeCity_EventScript_Back
        end

EverGrandeCity_EventScript_Lvl5:
        multichoice 0, 0, MULTI_LIGA_LVL5, TRUE
        goto_if_eq VAR_RESULT, 0, EverGrandeCity_EventScript_SetLvl0
        goto_if_eq VAR_RESULT, 1, EverGrandeCity_EventScript_SetLvl1
        goto_if_eq VAR_RESULT, 2, EverGrandeCity_EventScript_SetLvl2
        goto_if_eq VAR_RESULT, 3, EverGrandeCity_EventScript_SetLvl3
        goto_if_eq VAR_RESULT, 4, EverGrandeCity_EventScript_SetLvl4
        goto_if_eq VAR_RESULT, 5, EverGrandeCity_EventScript_SetLvl5
        goto_if_eq VAR_RESULT, 6, EverGrandeCity_EventScript_Back
        end

EverGrandeCity_EventScript_SetLvl0:
        setvar VAR_LIGA_REMATCH, 0
	setflag FLAG_HIDE_CHAMPIONS_ROOM_TROY
        clearflag FLAG_HIDE_CHAMPIONS_ROOM_WASSILI
        goto EverGrandeCity_EventScript_End

EverGrandeCity_EventScript_SetLvl1:
        setvar VAR_LIGA_REMATCH, 1
	setflag FLAG_HIDE_CHAMPIONS_ROOM_TROY
        clearflag FLAG_HIDE_CHAMPIONS_ROOM_WASSILI
        goto EverGrandeCity_EventScript_End

EverGrandeCity_EventScript_SetLvl2:
        setvar VAR_LIGA_REMATCH, 2
	setflag FLAG_HIDE_CHAMPIONS_ROOM_TROY
        clearflag FLAG_HIDE_CHAMPIONS_ROOM_WASSILI
        goto EverGrandeCity_EventScript_End

EverGrandeCity_EventScript_SetLvl3:
        setvar VAR_LIGA_REMATCH, 3
	setflag FLAG_HIDE_CHAMPIONS_ROOM_TROY
        clearflag FLAG_HIDE_CHAMPIONS_ROOM_WASSILI
        goto EverGrandeCity_EventScript_End

EverGrandeCity_EventScript_SetLvl4:
        setvar VAR_LIGA_REMATCH, 4
	clearflag FLAG_HIDE_CHAMPIONS_ROOM_TROY
        setflag FLAG_HIDE_CHAMPIONS_ROOM_WASSILI
        goto EverGrandeCity_EventScript_End

EverGrandeCity_EventScript_SetLvl5:
        setvar VAR_LIGA_REMATCH, 5
        goto EverGrandeCity_EventScript_End

EverGrandeCity_EventScript_End:
        msgbox EverGrandeCity_Text_LevelSet, MSGBOX_DEFAULT
        release
        end

EverGrandeCity_EventScript_Back::
        msgbox EverGrandeCity_Text_Back, MSGBOX_DEFAULT
        release
        end


EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

EverGrandeCity_Text_LvlText:
        .string "Möchtest du die Liga zu einer\p"
        .string "Revanche herausfordern?\n"
        .string "Welches Level möchtest du?$"

EverGrandeCity_Text_NoBadges:
        .string "Wenn du die Liga besiegt hast, kannst du\p"
        .string "wiederkommen und die Liga\n"
        .string "zu einer Revanche herausfordern.$"

EverGrandeCity_Text_Back:
        .string "Ok, es bleibt beim aktuellen Level.$"

EverGrandeCity_Text_LevelSet:
        .string "Dein Level wurde gesetzt!\p"
        .string "Liga wurde zurückgesetzt!$"

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.ifdef ENGLISH
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"
	.else
	.ifdef GERMAN
	.string "Ab hier haben nur die TRAINER, die alle\n"
	.string "ORDEN der ARENen erhalten haben,\l"
	.string "Zutritt.\p"
	.string "TRAINER, lass uns sicherstellen, dass\n"
	.string "du auch alle ORDEN hast.$"
	.endif
	.endif

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.ifdef ENGLISH
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"
	.else
	.ifdef GERMAN
	.string "Du hast noch nicht alle ORDEN erhalten.\p"
	.string "Wenn du zur POKéMON LIGA willst,\n"
	.string "musst du alle ORDEN vorweisen können.$"
	.endif
	.endif

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.ifdef ENGLISH
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"
	.else
	.ifdef GERMAN
	.string "TRAINER! Glaube an dich und deine\n"
	.string "POKéMON und gehe weiter!$"
	.endif
	.endif

