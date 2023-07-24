#! /bash/sh 

CDI_NAME=GameEngine.cdi
GAME_NAME="Game Engine Test"
GAME_ELF=carGame
RELEASE="$(date +'%F')"

./mkdcdisc --author Aionmagan --cdda backGroundMusic.wav --cdda GDEmuCloneEnd.wav --name "${GAME_NAME}" --release ${RELEASE} -v 3 -N -e ${GAME_ELF} -o ${CDI_NAME}
